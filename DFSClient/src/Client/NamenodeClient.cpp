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
    request.set_clientname(CLIENT_NAME);

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
    request.set_clientname(CLIENT_NAME);

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

bool NamenodeClient::rename(const std::string& src,const std::string& dst){
    ClientNamenode::RenameRequest request;
    request.set_src(src);
    request.set_dst(dst);
    ClientContext context;

    ClientNamenode::RenameResponse response;
    auto status = m_stub->Rename(&context,request,&response);
    if (status.ok()){
        return response.result();
    } else{
        LOG(WARNING) << status.error_code() <<":"<<status.error_message();
        return false;
    }

}

bool NamenodeClient::deleteFile(const std::string& path){
    ClientNamenode::DeleteRequest request;
    request.set_src(path);
    ClientContext context;

    ClientNamenode::DeleteResponse response;
    auto status = m_stub->Delete(&context,request,&response);
    if (status.ok()){
        return response.result();
    } else{
        LOG(WARNING) << status.error_code() <<":"<<status.error_message();
        return false;
    }
}

bool NamenodeClient::mkdir(const std::string& path){
    ClientNamenode::mkdirRequest request;
    request.set_src(path);
    ClientContext context;

    ClientNamenode::mkdirResponse response;
    auto status = m_stub->mkdir(&context,request,&response);
    if (status.ok()){
        return response.issuccess();
    } else{
        LOG(WARNING) << status.error_code() <<":"<<status.error_message();
        return false;
    }
}

std::vector<FileStatus> NamenodeClient::listing(const std::string& path){
    ClientNamenode::GetListingRequest request;
    request.set_src(path);
    ClientContext context;

    ClientNamenode::GetListingResponse response;
    auto status = m_stub->Listing(&context,request,&response);
    if (status.ok()){
        std::vector<FileStatus> res;
        for (int i = 0; i < response.dirlist().partiallisting().size(); ++i) {
            res.push_back(response.dirlist().partiallisting(i));
        }
        return res;
    } else{
        LOG(WARNING) << status.error_code() <<":"<<status.error_message();
        return {};
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
