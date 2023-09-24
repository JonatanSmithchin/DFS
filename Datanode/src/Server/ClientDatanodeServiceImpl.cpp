//
// Created by lxx18 on 2023/9/9.
//

#include <fstream>
#include "Server/ClientDatanodeServiceImpl.h"
#include "utils/checkSum.h"

ClientDatanodeServiceImpl::~ClientDatanodeServiceImpl() {

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
    return grpc::Status::OK;
}

grpc::Status ClientDatanodeServiceImpl::downloadBlock(::grpc::ServerContext *context,
                                                      const ::ClientDatanode::downloadBlockRequest *request,
                                                      ::grpc::ServerWriter<::ClientDatanode::downloadBlockResponse> *writer) {
    ClientDatanode::downloadBlockResponse response;
    char data[CHUNK_SIZE];
    std::ifstream infile;
    auto file = "/mnt/d/test/rcv/"+std::to_string(request->blockid());
    infile.open(file,std::ifstream::in|std::ifstream::binary);

    while (!infile.eof()){
        infile.read(data,CHUNK_SIZE);

        long size = infile.gcount();

        response.set_content(data,size);
        response.set_checksum(checkSum((const unsigned char*)data, size));
        response.set_size(size);

        writer->Write(response);
    }

    return grpc::Status::OK;
}

ClientDatanodeServiceImpl::ClientDatanodeServiceImpl(const std::string& work_dir):m_work_dir(work_dir) {

}
