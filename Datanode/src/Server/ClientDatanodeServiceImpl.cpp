//
// Created by lxx18 on 2023/9/9.
//

#include <fstream>
#include <pthread.h>
#include <vector>
#include <string>
#include "Server/ClientDatanodeServiceImpl.h"
#include "utils/checkSum.h"

ClientDatanodeServiceImpl::~ClientDatanodeServiceImpl() {

}

struct Args{
    std::vector<std::string> ipAddrs;
    uint64_t blockId;
};

DatanodeClient* getDatanode(const std::string &ipAddr) {
    std::string s="/mnt/d/test/rcv/";
    auto client = new DatanodeClient(grpc::CreateChannel(
            ipAddr,grpc::InsecureChannelCredentials()
    ),s);

    return client;
}

void * backup(void * arg) {
    // 找datanode 传输
    Args* args=(Args *)arg;

    auto datanode1=getDatanode(args->ipAddrs[0]);
    auto datanode2=getDatanode(args->ipAddrs[1]);

    datanode1->copyBlock(args->blockId);
    datanode2->copyBlock(args->blockId);
    return NULL;
}

grpc::Status ClientDatanodeServiceImpl::transferBlock(::grpc::ServerContext *context,
                                                      ::grpc::ServerReader<::ClientDatanode::transferBlockRequest> *reader,
                                                      ::ClientDatanode::transferBlockResponse *response) {

    ClientDatanode::transferBlockRequest request;
    //第一次先获取blockid创建对应文件
    reader->Read(&request);

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

    Args args;
    for (int i = 0; i < request.ipaddrs_size(); ++i) {
        args.ipAddrs.push_back(request.ipaddrs(i));
    }
    args.blockId=request.blockid();

    // 创建子线程来完成block备份工作（datanode之间
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, backup, (void *)&args);
    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error1 : %s\n", errstr); // 好像应该用LOG？？
    }

    ret = pthread_detach(tid); // 设置线程分离
    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error2 : %s\n", errstr);
    }

    return grpc::Status::OK;
}

grpc::Status ClientDatanodeServiceImpl::downloadBlock(::grpc::ServerContext *context,
                                                      const ::ClientDatanode::downloadBlockRequest *request,
                                                      ::grpc::ServerWriter<::ClientDatanode::downloadBlockResponse> *writer) {
    ClientDatanode::downloadBlockResponse response;
    char data[CHUNK_SIZE];
    std::ifstream infile;
    std::string file = "/mnt/d/test/rcv/"+std::to_string(request->blockid(0));
    infile.open(file,std::ifstream::in|std::ifstream::binary);

    while (!infile.eof()){
        infile.read(data,CHUNK_SIZE);

        long size = infile.gcount();

        response.set_content(data,size);
        response.set_checksum(checkSum((const unsigned char*)data, size));
        // response.set_size(size);

        writer->Write(response);
    }

    return grpc::Status::OK;
}

ClientDatanodeServiceImpl::ClientDatanodeServiceImpl(const std::string& work_dir):m_work_dir(work_dir) {

}
