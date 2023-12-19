#include <iostream>
#include "glog/logging.h"
#include "Server/RPCServer.h"
#include "DatanodeManager/HeartBeatMonitor.h"
#include "DatanodeManager/DatanodeManager.h"

int main(int argc, char** argv){
    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "Starting NameNode";

    auto blockManager = new BlockManager();

    auto datanodeManager = new DatanodeManager(blockManager);
    auto heartBeatMonitor = new HeartBeatMonitor(datanodeManager);
    heartBeatMonitor->run();

    auto root = new INodeDir();
    root->setFullPathName("/");
    auto nameSystem = new NameSystem(root,datanodeManager,blockManager);

    ClientServiceImpl ClientService(nameSystem);
    DatanodeServiceImpl DatanodeService(datanodeManager);

    RPCServer server(nameSystem, &ClientService, &DatanodeService);

    server.RunServer();
    return 0;
}