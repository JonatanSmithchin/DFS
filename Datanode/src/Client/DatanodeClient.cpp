//
// Created by cyt on 2023/10/13.
//

#include <thread>
#include <fstream>
#include <glog/logging.h>
#include "Client/DatanodeClient.h"
#include "utils/net_utils.h"
#include "proto/dfs.grpc.pb.h"
#include "utils/checkSum.h"

void DatanodeClient::copyBlock(uint64_t blockId) {
    copyBlockRequest request;
    copyBlockResponse response;

    ClientContext context;

    // 从 block 中取出信息
    const std::string& file = m_work_dir + std::to_string(blockId);
    std::cout << "read from " << file;
    std::ifstream infile;

    infile.open(file,std::ifstream::in | std::ifstream::binary);
    // char data[CHUNK_SIZE];
    std::vector<char> data(CHUNK_SIZE);

    std::unique_ptr<grpc::ClientWriter<copyBlockRequest>> writer(m_stub->copyBlock(&context,&response));
    while (!infile.eof()){

        infile.read(data.data(),CHUNK_SIZE);

        long size = infile.gcount();
        std::cout << "read from " << file;
        std::cout << "send content" << size << std::endl;
        // request.set_content(data,size);
        request.set_content(data.data(),data.size());
        request.set_size(size);
        request.set_blockid(blockId);
        request.set_checksum(checkSum((const unsigned char*)data.data(),size));

        if (!writer->Write(request)){
            break;
        }
    }
    writer->WritesDone();
    Status status  = writer->Finish();
    if (status.ok()){
        std::cout << "copy blocks finished" << std::endl;
    } else{
        std::cout << status.error_code() << ": " << status.error_message();
    }
    infile.close();
}
