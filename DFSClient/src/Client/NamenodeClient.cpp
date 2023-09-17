//
// Created by lxx18 on 2023/9/11.
//

#include "glog/logging.h"
#include "Client/NamenodeClient.h"
#include "proto/ClientNamenode.pb.h"

NamenodeClient::NamenodeClient(std::shared_ptr<grpc::Channel> channel):m_stub(ClientService::NewStub(channel)) {}

bool NamenodeClient::create(const std::string &path) {
    ClientNamenode::CreateRequest request;
    request.set_src(path);
    request.set_clientname("liuxiao");

    ClientContext context;

    ClientNamenode::CreateResponse response;
    auto status = m_stub->Create(&context,request,&response);
    if (status.ok()){
        return true;
    } else{
        LOG(WARNING) << "cannot create file" << status.error_code();
        return false;
    }
}

LocatedBlock *NamenodeClient::append(const std::string &path) {
    ClientNamenode::AppendRequest request;
    request.set_src(path);
    request.set_clientname("liuxiao");

    ClientContext context;

    ClientNamenode::AppendResponse response;
    auto status = m_stub->Append(&context,request,&response);
    if (status.ok()){
        auto block = new LocatedBlock;
        block->CopyFrom(response.block());
        return block;
    } else{
        return nullptr;
    }
}

LocatedBlocks *NamenodeClient::locate(const std::string& path) {
    ClientNamenode::GetFileBlockLocationsRequest request;
    request.set_src(path);
    
    ClientContext context;

    ClientNamenode::GetFileBlockLocationsResponse response;
    auto status = m_stub->GetFileBlockLocations(&context,request,&response);
    if (status.ok()){
        auto file_blocks = new LocatedBlocks;
        file_blocks->CopyFrom(response.locations());
        return file_blocks;
    } else{
        return nullptr;
    }
}
