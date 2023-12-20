#include <iostream>
#include "glog/logging.h"
#include "Server/RPCServer.h"
#include "DatanodeManager/HeartBeatMonitor.h"
#include "DatanodeManager/DatanodeManager.h"
#include "CacheManager/CacheMonitor.h"

int main(int argc, char** argv){
    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "Starting NameNode";

    auto cacheManager = new CacheManager(5);
    auto blockManager = new BlockManager();
    auto datanodeManager = new DatanodeManager(blockManager);

    auto cacheMonitor = new CacheMonitor(cacheManager,datanodeManager);
    auto heartBeatMonitor = new HeartBeatMonitor(datanodeManager);
    heartBeatMonitor->run();
    cacheMonitor->run();

    auto root = new INodeDir();
    root->setFullPathName("/");
    auto nameSystem = new NameSystem(root,datanodeManager,blockManager,cacheManager);

    ClientServiceImpl ClientService(nameSystem);
    DatanodeServiceImpl DatanodeService(datanodeManager);

    RPCServer server(nameSystem, &ClientService, &DatanodeService);

    server.RunServer();
    return 0;
}