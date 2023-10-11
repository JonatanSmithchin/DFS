//
// Created by lxx18 on 2023/9/10.
//

#include <grpcpp/grpcpp.h>
#include <iostream>
#include <string>
#include <vector>
#include "glog/logging.h"
#include "proto/ClientDatanode.pb.h"
#include "Client/DatanodeClient.h"

#include "boost/tokenizer.hpp"
#include "DFSClient/DFSClient.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace ClientDatanode;
using namespace std;
using namespace boost;

void showHelp();
void Banner();
int main(int argc,char** argv){


    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "Starting DFSClient";
    NamenodeClient namenodeClient(grpc::CreateChannel(
            "localhost:8501",grpc::InsecureChannelCredentials()));
    DatanodeClient datanodeClientclient(grpc::CreateChannel(
            "localhost:8501",grpc::InsecureChannelCredentials()
            ));
    DFSClient client(&namenodeClient);



//    client.uploadBlock("/mnt/d/cpp-project/DFS/DFSClient/tests/utils/honkai3.jpg");
std::string cmd;
while(1){
    getline(cin,cmd);
    Banner();
    showHelp();
    if(cmd.length()==0){
        continue;

    }else if(cmd=="help"){
        showHelp();

    }
    else{
//        定义分词器，分割符号为逗号，空格
//        定义分词器: 定义分割符号为[逗号,空格]
        boost::char_separator<char> sep(", --");
        typedef boost::tokenizer<boost::char_separator<char>> CustonTokenizer;
        CustonTokenizer tok(cmd, sep);

        // 将分词结果放入vector链表
        std::vector<std::string> vecSegTag;
        for (CustonTokenizer::iterator beg = tok.begin(); beg != tok.end(); ++beg)
        {
            vecSegTag.push_back(*beg);
        }

//        判断
        if (vecSegTag.size() == 2 && vecSegTag[0] == "mkdir")
        {
            client.mkdir(vecSegTag[1].c_str());
        }
        else if (vecSegTag.size() == 2 && vecSegTag[0] == "deleteNode"){
            client.deleteNode(vecSegTag[1].c_str());
        }
        else if (vecSegTag.size() == 3 && vecSegTag[0] == "rename"){
            client.rename(vecSegTag[1].c_str(),vecSegTag[2].c_str());
        }
        else if (vecSegTag.size() == 2 && vecSegTag[0] == "listing"){
            client.listing(vecSegTag[1].c_str());
        }
        else
       if(vecSegTag.size() == 3 && vecSegTag[0] == "uploadFile"){
            client.uploadFile(vecSegTag[1].c_str(),vecSegTag[2].c_str());
        }
        else if(vecSegTag.size() == 3 && vecSegTag[0] == "downloadFile"){
            client.downloadFile(vecSegTag[1].c_str(),vecSegTag[2].c_str());
        }
        else{
            ::fprintf(stderr, "Error: Unknown command\n");
            showHelp();
        }

    }
}

    return 0;
}

void showHelp(){
    ::fprintf(stderr, "Usage:\n"
            "  tprDFS [OPTION]...\n"
            "\n"
            "Options:\n"
            "  --help  显示帮助信息 \n"
            "  --mkdir [path] DFS中的新建路径\n"
            "  --deleteNode [path] DFS中要删除的路径    \n"
            "  --rename [src] [dst]     \n"
            "  --listing [path]   \n"
            "  --uploadFile [dst] [filepath] \n"
            "  --downloadFile [dst] [filepath]  \n");
}
void Banner(){
    ::fprintf(stderr, "   _              ____  _____ ____  \n"
                                    " | |_ _ __  _ __|  _ \\|  ___/ ___| \n"
                                    " | __| '_ \\| '__| | | | |_  \\___ \\ \n"
                                    " | |_| |_) | |  | |_| |  _|  ___) |\n"
                                    "  \\__| .__/|_|  |____/|_|   |____/ \n"
                                    "     |_|                                                     \n");
}
