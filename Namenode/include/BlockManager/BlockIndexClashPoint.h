#pragma once
#include"BlockIndex.h"
#include <string>
#include <queue>

using namespace std;
class BlockIndexClashPoint:BlockIndex
{
public:
    string name;
private:
    BlockIndexClashPoint* next;
public:
    bool insert(BlockIndexClashPoint* Head, LocatedBlocks* blockMessage, string name);
    bool remove(BlockIndexClashPoint* Head, string name);
    LocatedBlocks* inquireALL(BlockIndexClashPoint* Head, string name);
    const LocatedBlock* inquire(BlockIndexClashPoint* Head, string name, uint64_t blockID);
    queue<pair<uint64_t, int> > checkBackups(BlockIndexClashPoint* Head);
    BlockIndexClashPoint(LocatedBlocks* blockMessage, string Name);

    bool
    insertBackups(BlockIndexClashPoint *Head, string name, uint64_t blockid, pair<string, string> backupsDatanodeid);
};

