#pragma once
#include"BlockIndexClashPoint.h"
#include"BlockIndexHash.h"
#include"BlockIndexRBTree.h"
#include <vector>
#include "proto/dfs.pb.h"
class BlockManager
{
private:
//    vector<BlockIndexHash*>* HashTable;//ʹ�ø�ָ���hash����в���;
    vector<BlockIndexHash*>* hashTable1;
//    vector<BlockIndexHash*> hashTable2;
    long long num;
    //BlockIndexRBTree��BlockIndexClashPoint������ʱ��ʹ��ָ���໥���ӡ�
    int hashTableSize, hashKey;
    int hashTableSize2, hashKey2;
    int getKey(string Name, int hashSize, int key);
//    bool clearHashTable(vector<BlockIndexHash*>* tablePoint);//�ú�����Ŀ�������һ��hash�������Ԫ�ز��ͷ��ڴ�
//    bool initHashTable(int HashTableSize, int HashKey);//��ʼ��hash��
public:
    bool create(string name);
    LocatedBlock* addBlock(int blockID, vector<DatanodeInfo*> datanodes, int size, string name);
    bool removeBlock(string Name);
    LocatedBlocks* getALLBlock(string name);
//    bool refrashBlock(int Datanode, string Name);
//    bool refrashHashTable();//�ú�����Ŀ�����Ż���ѯ�ٶȣ�����hash��
//    string getBlockALL(string name);
    BlockManager();
};

