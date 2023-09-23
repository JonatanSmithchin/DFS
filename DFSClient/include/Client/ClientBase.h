//
// Created by cyt on 2023/9/22.
//

#ifndef DFSCLIENT_CLIENTBASE_H
#define DFSCLIENT_CLIENTBASE_H

#include <yaml-cpp/yaml.h>
#include <string>

class ClientBase {
public:
    std::string UPLOAD_TEMP_FILE_DIR;
    std::string DOWNLOAD_TEMP_FILE_DIR;
    std::string CLIENT_NAME;
    int CHUNK_SIZE;
    ClientBase(){
        // 相对于工作目录，即build目录
        YAML::Node node = YAML::LoadFile("../configs/ClientConfig.yaml");

        UPLOAD_TEMP_FILE_DIR = node["upload_temp_file_dir"].as<std::string>();
        DOWNLOAD_TEMP_FILE_DIR = node["download_temp_file_dir"].as<std::string>();
        CLIENT_NAME = node["client_name"].as<std::string>();
        CHUNK_SIZE = node["chunk_size"].as<int>();
    }
};


#endif //DFSCLIENT_CLIENTBASE_H
