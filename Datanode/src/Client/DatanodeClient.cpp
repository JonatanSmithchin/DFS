#include<iostream>
#include<string>
#include<grpcpp/grpcpp.h>
#include "proto/DatanodeNamenode.grpc.pb.h"
//#include <netdb.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace DatanodeNamenode;

class Client {
public:
    Client(std::shared_ptr<Channel> channel)
            : stub_(DatanodeService::NewStub(channel)){}

    std::string regist(DatanodeRegister* r){
        RegisterDatanodeRequest request;
        request.set_allocated_registration(r);

        RegisterDatanodeResponse response;
        ClientContext context;

        Status status = stub_->registerDatanode(&context,request,&response);

        if (status.ok()){
            return response.registration().id().hostname();
        }else{
            std::cout << status.error_code() << ":" << status.error_message() << std::endl;
            return "RPC failed";
        }
    }


private:
    std::unique_ptr<DatanodeService::Stub> stub_;
};
