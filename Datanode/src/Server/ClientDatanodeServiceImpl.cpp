//
// Created by lxx18 on 2023/9/9.
//

#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <yaml-cpp/yaml.h>
#include "Server/ClientDatanodeServiceImpl.h"
#include "utils/checkSum.h"

ClientDatanodeServiceImpl::~ClientDatanodeServiceImpl() {

}

class Args{
public:
    std::vector<std::string> ipAddrs;
    uint64_t blockId;
    Args(std::vector<std::string> addrs,uint64_t id);
};

Args::Args(std::vector<std::string> addrs, uint64_t id):ipAddrs(addrs),blockId(id) {

}

DatanodeClient* getDatanode(const std::string &ipAddr) {
    YAML::Node node = YAML::LoadFile("../configs/DatanodeConfig.yaml");
    const std::string& work_dir = node["work_dir"].as<std::string>();
    auto client = new DatanodeClient(grpc::CreateChannel(
            ipAddr,grpc::InsecureChannelCredentials()
    ),work_dir);

    return client;
}

void* backup(Args args) {
    // 找datanode 传输

    auto datanode1=getDatanode(args.ipAddrs[0]);
    auto datanode2=getDatanode(args.ipAddrs[1]);

    datanode1->copyBlock(args.blockId);
    datanode2->copyBlock(args.blockId);
    return nullptr;
}

grpc::Status ClientDatanodeServiceImpl::transferBlock(::grpc::ServerContext *context,
                                                      ::grpc::ServerReader<::ClientDatanode::transferBlockRequest> *reader,
                                                      ::ClientDatanode::transferBlockResponse *response) {

    ClientDatanode::transferBlockRequest request;
    //第一次先获取blockid创建对应文件
    reader->Read(&request);
    std::cout << "receive block " << request.blockid() << "\n";
    const std::string& filename = m_work_dir + std::to_string(request.blockid());
    std::ofstream outfile;
    outfile.open(filename,std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);

    do{

        auto data = request.content().c_str();
        auto size = request.size();

        if(request.checksum() != checkSum((const unsigned char* )data,size)){
            return grpc::Status::CANCELLED;
        }

        outfile.write(data,size);
    }while (reader->Read(&request));

    outfile.close();

    std::vector<std::string> ipAddrs;
    std::cout << request.ipaddrs().size();
    for (int i = 0; i < request.ipaddrs().size(); ++i) {
        std::cout << request.ipaddrs(i) << std::endl;
        ipAddrs.push_back(request.ipaddrs(i));
    }
//    args.blockId=request.blockid();

    // 创建子线程来完成block备份工作（datanode之间
    std::thread th(backup,Args(ipAddrs,request.blockid()));
    if(th.joinable()) {
        th.detach();
    } else{
        std::cout << "error";
    }

    return grpc::Status::OK;
}

grpc::Status ClientDatanodeServiceImpl::downloadBlock(::grpc::ServerContext *context,
                                                      const ::ClientDatanode::downloadBlockRequest *request,
                                                      ::grpc::ServerWriter<::ClientDatanode::downloadBlockResponse> *writer) {
    ClientDatanode::downloadBlockResponse response;
    char data[CHUNK_SIZE];
    std::istream* istream;
    if (m_cache->hit(request->blockid(0))){
        auto value = m_cache->get(request->blockid(0));
        auto ss = new std::stringstream(value);
        istream = ss;
    } else{
        auto infile = new std::ifstream;
        std::string file = m_work_dir + std::to_string(request->blockid(0));
        infile->open(file,std::ifstream::in|std::ifstream::binary);
        istream = infile;
    }

    while (!istream->eof()){
        istream->read(data,CHUNK_SIZE);

        long size = istream->gcount();
        std::cout << "send content to client: " << size;
        response.set_content(data,size);
        response.set_checksum(checkSum((const unsigned char*)data, size));
        // response.set_size(size);

        writer->Write(response);
    }
    delete istream;
    return grpc::Status::OK;
}

ClientDatanodeServiceImpl::ClientDatanodeServiceImpl(const std::string& work_dir,Cache* cache):m_work_dir(work_dir),m_cache(cache) {

}
