//
// Created by lxx18 on 2023/9/10.
//

#ifndef DFSCLIENT_FILEUTILS_H
#define DFSCLIENT_FILEUTILS_H

#include <string>
#include <vector>
namespace FileUtils {
    constexpr size_t BUFFER_SIZE = 1024 * 1024;
    constexpr size_t BLOCK_SIZE = 64 * 1024 * 1024;
    const std::string TEMP_PREFIX = "/mnt/d/test/temp/temp-";

    std::vector<std::string> getFiles(const std::string& dir);

    uint32_t checkSum(const unsigned char *buf, size_t len);

    void SplitFile(std::fstream *input);

    void MergeFile(std::fstream *output, const std::vector<std::string>& files);
}


#endif //DFSCLIENT_FILEUTILS_H
