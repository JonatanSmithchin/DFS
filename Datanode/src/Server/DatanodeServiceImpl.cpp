//
// Created by cyt on 2023/9/28.
//

#include <fstream>
#include <filesystem>
#include "Server/DatanodeServiceImpl.h"
#include "utils/checkSum.h"

DatanodeServiceImpl::~DatanodeServiceImpl() {
    
}

::grpc::Status DatanodeServiceImpl:: copyBlock(::grpc::ServerContext* context,
                                              ::grpc::ServerReader< ::Datanode::copyBlockRequest>* reader,
                                              ::Datanode::copyBlockResponse* response) {
    Datanode::copyBlockRequest request;
    reader->Read(&request);

    const std::string& replica_dir = m_work_dir + "replica/";

    if (!std::filesystem::exists(replica_dir)){
        std::filesystem::create_directory(replica_dir);
    }
    const std::string& filename = replica_dir + std::to_string(request.blockid());

    if (std::filesystem::exists(filename)){
        return grpc::Status::OK;
    }

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

DatanodeServiceImpl::DatanodeServiceImpl(const std::string& work_dir):m_work_dir(work_dir) {

}


