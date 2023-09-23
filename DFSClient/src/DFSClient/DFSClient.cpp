//
// Created by lxx18 on 2023/9/11.
//

#include "DFSClient/DFSClient.h"
#include "utils/FileUtils.h"
#include <grpcpp/grpcpp.h>
#include <fstream>
#include <filesystem>

DatanodeClient *DFSClient::getDatanode(const std::string &ipAddr) {

    auto client = new DatanodeClient(grpc::CreateChannel(
            ipAddr,grpc::InsecureChannelCredentials()
    ));

    return client;
}

void DFSClient::uploadFile(const std::string& dst,const std::string &file) {
    std::fstream input(file,std::ios::in|std::ios::binary);

    FileUtils::SplitFile(&input,UPLOAD_TEMP_FILE_DIR);
    //申请创建文件
    if(!m_namenodeClient->create(dst)){
        return;
    }

    //获取已经分割的所有暂存数据块
    auto blocks = FileUtils::getFiles(UPLOAD_TEMP_FILE_DIR);
    //添加数据块
    for (const auto& blk:blocks){
        auto block = m_namenodeClient->append(dst);
        //TODO: 还要选择一个datanode
        auto ipAddr = block->locs(0).id().ipaddr() + ":" + std::to_string(block->locs(0).id().xferport());
        auto datanode = getDatanode(ipAddr);
        datanode->uploadBlock(blk,block->block().blockid());
        delete datanode;
    }

}

struct temp_file{
    google::protobuf::uint64 offset;
    std::string file_name;
    temp_file(int o,std::string& f):offset(o),file_name(f){}

    bool operator<(const temp_file& other) const {
        return offset < other.offset;
    }
};

void DFSClient::downloadFile(const std::string& dst,const std::string &file) {
    std::vector<google::protobuf::uint64> block_ids;
    // 向namenode请求文件位置
    LocatedBlocks *file_blocks = m_namenodeClient->locate(file);

    std::set<temp_file> temp_files; // 借用set为文件块排序
    std::vector<std::string> files; // 排序后的文件块

    for (int i = 0; i < file_blocks->blocks_size(); ++i) {
        const LocatedBlock& file_block = file_blocks->blocks(i);
        google::protobuf::uint64 block_id = file_block.block().blockid();

        // 下载文件块并放入set
        std::string temp = DOWNLOAD_TEMP_FILE_DIR + "temp-" + std::to_string(i); 
        m_datanodeClient->downloadBlock(temp,block_id);
        temp_file f(file_block.offset(),temp);
        temp_files.insert(f);
    }
    for (const temp_file& f : temp_files) {
        files.push_back(f.file_name);
    }
    
    std::fstream output(dst,std::ios::binary);
    FileUtils::MergeFile(&output,files);
}

DFSClient::DFSClient(NamenodeClient *namenodeClient):m_namenodeClient(namenodeClient) {

}


