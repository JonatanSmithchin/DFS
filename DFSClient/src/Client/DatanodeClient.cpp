//
// Created by lxx18 on 2023/9/10.
//
#include <fstream>
#include <random>
#include "Client/DatanodeClient.h"
#include "proto/ClientDatanode.pb.h"
#include "utils/checkSum.h"

DatanodeClient::DatanodeClient(std::shared_ptr<grpc::Channel> channel): m_stub(FileService::NewStub(channel)) {

}

void DatanodeClient::upload(const std::string& file) {
    transferBlockRequest request;
    transferBlockResponse response;
    char data[BLOCK_SIZE];
    ClientContext context;

    std::default_random_engine e;
    e.seed(time(0));

    std::ifstream infile;

    infile.open(file,std::ifstream::in | std::ifstream::binary);
    std::unique_ptr<grpc::ClientWriter<transferBlockRequest>> writer(m_stub->transferBlock(&context,&response));
    while (!infile.eof()){

        infile.read(data,BLOCK_SIZE);

        long size = infile.gcount();
        request.set_content(data,size);
        request.set_size(size);
        request.set_blockid(e());
        request.set_checksum(checkSum((const unsigned char*)data,size));

        if (!writer->Write(request)){
            break;
        }
    }
    writer->WritesDone();
    Status status  = writer->Finish();
    if (status.ok()){
        std::cout << "Transfer blocks finished";
    } else{
        std::cout << status.error_code() << status.error_message();
    }
}
