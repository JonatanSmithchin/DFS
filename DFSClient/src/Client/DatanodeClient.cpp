//
// Created by lxx18 on 2023/9/10.
//
#include <fstream>
#include <random>
#include "Client/DatanodeClient.h"
#include "proto/ClientDatanode.pb.h"
#include "utils/FileUtils.h"

DatanodeClient::DatanodeClient(std::shared_ptr<grpc::Channel> channel):
    m_stub(FileService::NewStub(channel)){
}

void DatanodeClient::uploadBlock(const std::string& file,uint64_t blockId,std::vector<std::string> ipAddrs) {
    transferBlockRequest request;
    transferBlockResponse response;
    // char data[CHUNK_SIZE];
    std::vector<char> data(CHUNK_SIZE);
    ClientContext context;

    std::ifstream infile;

    infile.open(file,std::ifstream::in | std::ifstream::binary);
    std::unique_ptr<grpc::ClientWriter<transferBlockRequest>> writer(m_stub->transferBlock(&context,&response));
    request.add_ipaddrs(ipAddrs[0]);
    request.add_ipaddrs(ipAddrs[1]);
    while (!infile.eof()){

        infile.read(data.data(),CHUNK_SIZE);

        long size = infile.gcount();
        request.set_content(data.data(),data.size());
        request.set_size(size);
        request.set_blockid(blockId);
        request.set_checksum(FileUtils::checkSum((const unsigned char*)data.data(),size));

        if (!writer->Write(request)){
            break;
        }
    }
    writer->WritesDone();
    Status status  = writer->Finish();
    if (status.ok()){
        std::cout << "Upload blocks finished" << std::endl;
    } else{
        std::cout << status.error_code() << ": " << status.error_message();
    }
}

void DatanodeClient::downloadBlock(const std::string& file,const google::protobuf::uint64& block_id) {
    downloadBlockRequest request;
    downloadBlockResponse response;
    ClientContext context;

    std::ofstream outfile;
    outfile.open(file,std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);
        
    request.add_blockid(block_id);

    std::unique_ptr<grpc::ClientReader<downloadBlockResponse>> reader(m_stub->downloadBlock(&context,request));

    while (reader->Read(&response)) {
        outfile.write(response.content().c_str(),response.content().size());
        //std::cout << "read from datanode: " << response.content().size();
    }

    Status status  = reader->Finish();
    if (status.ok()){
        std::cout << "Download block finished\n";
    } else{
        std::cout << status.error_code() << ": " << status.error_message();
    }
}
