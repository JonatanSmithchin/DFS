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

    FileUtils::SplitFile(&input);
    //申请创建文件
    if(!m_namenodeClient->create(dst)){
        return;
    }

    //获取已经分割的所有暂存数据块
    //TODO: 配置暂存文件路径
    auto blocks = FileUtils::getFiles("/mnt/d/test/temp");
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

DFSClient::DFSClient(NamenodeClient *namenodeClient):m_namenodeClient(namenodeClient) {

}


