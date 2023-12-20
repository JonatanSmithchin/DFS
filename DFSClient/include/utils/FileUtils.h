//
// Created by lxx18 on 2023/9/10.
//

#ifndef DFSCLIENT_FILEUTILS_H
#define DFSCLIENT_FILEUTILS_H

#include <string>
#include <vector>
namespace FileUtils {
    // constexpr size_t BUFFER_SIZE = 1024 * 1024;
    // constexpr size_t BLOCK_SIZE = 64 * 1024 * 1024;

    std::vector<std::string> getFiles(const std::string& dir,int offset);

    uint32_t checkSum(const unsigned char *buf, size_t len);

    void SplitFile(std::fstream *input, const std::string des_dir);

    void MergeFile(std::fstream *output, const std::vector<std::string>& files);

    void removeFilesInDir(const std::string& dir);
}


#endif //DFSCLIENT_FILEUTILS_H
