//
// Created by lxx18 on 2023/9/10.
//

#include <vector>
#include <fstream>
#include <filesystem>
#include <yaml-cpp/yaml.h>
#include "glog/logging.h"
#include "utils/FileUtils.h"

namespace FileUtils {

    YAML::Node node = YAML::LoadFile("../configs/ClientConfig.yaml");
    size_t BUFFER_SIZE = node["buffer_size"].as<size_t>();
    size_t BLOCK_SIZE = node["block_size"].as<size_t>();

    uint32_t checkSum(const unsigned char *buf, size_t len) {
        auto ptr = (uintptr_t) buf;
        typedef uint16_t  __attribute__((__may_alias__)) u16_p;
        auto *u16_buf = (const u16_p *) ptr;

        uint32_t sum = 0;
        while (len >= (sizeof(*u16_buf) * 4)) {
            sum += u16_buf[0];
            sum += u16_buf[1];
            sum += u16_buf[2];
            sum += u16_buf[3];
            len -= sizeof(*u16_buf) * 4;
            u16_buf += 4;
        }
        while (len >= sizeof(*u16_buf)) {
            sum += *u16_buf;
            len -= sizeof(*u16_buf);
            u16_buf += 1;
        }

        if (len == 1) {
            sum += *((const uint8_t *) u16_buf);
        }

        return (~sum) + 1;
    }

    void SplitFile(std::fstream *input, const std::string des_dir) {
        int blk_num = 0;

        size_t size = 0;
        input->seekg(0, std::ios::end);
        size = input->tellg();
        input->seekg(0, std::ios::beg);

        size_t count = size / BLOCK_SIZE;
        size_t last_size = size % BLOCK_SIZE;

        char *buff = new char[BUFFER_SIZE];
        for (size_t i = 0; i <= count; ++i) {
            //TODO: 命名数据块
            size_t cur_size = (i == count) ? last_size : BLOCK_SIZE;
            if (cur_size == 0) {
                break;
            }
            
            const std::string &fileName = des_dir + "/temp-" + std::to_string(blk_num++);
            std::fstream output(fileName, std::ios::out | std::ios::binary);

            if (!output.is_open()) {
                LOG(ERROR) << "output file open failed";
            }

            while (cur_size > 0) {
                size_t read_size = cur_size > BUFFER_SIZE ? BUFFER_SIZE : cur_size;
                input->read(buff, read_size);
                output.write(buff, read_size);
                cur_size -= read_size;
            }

            output.close();
        }
        delete[] buff;
    }

    void MergeFile(std::fstream *output, const std::vector<std::string>& files) {

        char *buff = new char[BUFFER_SIZE];
        for (const auto & file : files) {
            std::fstream input(file, std::ios::in | std::ios::binary);
            if (!input.is_open()) {
                LOG(ERROR) << "input file open failed";
            }

            input.seekg(0, std::ios::end);
            size_t size = input.tellg();
            input.seekg(0, std::ios::beg);

            while (size > 0) {
                size_t read_size = size > BUFFER_SIZE ? BUFFER_SIZE : size;
                input.read(buff, read_size);
                output->write(buff, read_size);
                size -= read_size;
            }
            input.close();
        }
        delete[]buff;
    }

    std::vector<std::string> getFiles(const std::string &dir,int offset) {
        if (!std::filesystem::exists(dir)){
            LOG(FATAL) << "Dir does not exist";
        }
        std::vector<std::string> files;
        std::filesystem::directory_entry entry(dir);
        if (entry.status().type() == std::filesystem::file_type::directory){
            std::filesystem::directory_iterator list(dir);
            for (auto &it:list){
                files.push_back(it.path().string());
            }
        }
        return files;
    }

    void removeFilesInDir(const std::string& dir){
        if (!std::filesystem::exists(dir)){
            LOG(FATAL) << "Dir does not exist";
        }
        std::filesystem::remove_all(dir);
        std::filesystem::create_directory(dir);
    }
}