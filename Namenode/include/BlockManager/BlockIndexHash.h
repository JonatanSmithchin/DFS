#pragma once
#include "BlockIndexRBTree.h"
#include "BlockIndex.h"
class BlockIndexHash:BlockIndex
{
private:
    BlockIndexRBTree* son;
    string name;
public:
    bool insert(string name, int xx, LocatedBlocks* blockMessage);
    bool remove(int xx, string name);
    bool checkRBTreeRoot();
    bool createRBTreeRoot(string name, int xx, LocatedBlocks* blockMessage);//������������ڵ�
    LocatedBlocks* inquireALL(int xx, string name);
    const LocatedBlock* inquire(int xx, string name, uint64_t blockID);
    queue<pair<uint64_t, int> > checkBackups();
    BlockIndexHash(LocatedBlocks* blockMessage);
    BlockIndexHash();

    bool insertBackups(int xx, string name, uint64_t blockid, pair<string, string> backupsDatanodeid);
};

