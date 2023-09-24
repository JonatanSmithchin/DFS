#pragma once
#include"BlockIndexClashPoint.h"
#include"BlockIndexHash.h"
#include"BlockIndexRBTree.h"
#include <vector>
#include "proto/dfs.pb.h"
class BlockManager
{
private:
//    vector<BlockIndexHash*>* HashTable;//使用该指针对hash表进行操作;
    vector<BlockIndexHash*>* hashTable1;
//    vector<BlockIndexHash*> hashTable2;
    long long num;
    //BlockIndexRBTree和BlockIndexClashPoint当创建时再使用指针相互连接。
    int hashTableSize, hashKey;
    int hashTableSize2, hashKey2;
    int getKey(string Name, int hashSize, int key);
//    bool clearHashTable(vector<BlockIndexHash*>* tablePoint);//该函数的目的是清除一个hash表的所有元素并释放内存
//    bool initHashTable(int HashTableSize, int HashKey);//初始化hash表
public:
    bool create(string name);
    LocatedBlock* addBlock(int blockID, vector<DatanodeInfo*> datanodes, int size, string name);
    bool removeBlock(string Name);
    LocatedBlocks* getALLBlock(string name);
//    bool refrashBlock(int Datanode, string Name);
//    bool refrashHashTable();//该函数的目的是优化查询速度，扩大hash表
//    string getBlockALL(string name);
    BlockManager();
};

