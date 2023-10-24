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
    bool create(const string& name);
    LocatedBlock* addBlock(size_t blockID, const vector<DatanodeInfo*>& datanodes, int size,const string& name);
    bool removeBlock(string Name);
    LocatedBlocks* getALLBlock(string name);
    const LocatedBlock* getBlock(string name, uint64_t blockID);
    queue<pair<uint64_t, int> > checkBackups();
//    bool refrashBlock(int Datanode, string Name);
//    bool refrashHashTable();//�ú�����Ŀ�����Ż���ѯ�ٶȣ�����hash��
//    string getBlockALL(string name);
    BlockManager();

    bool addBackups(queue<pair<string, pair<uint64_t, pair<string, string>>>> backups);
};

