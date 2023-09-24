#pragma once
#include"BlockIndex.h"
#include <string>
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
    BlockIndexClashPoint(LocatedBlocks* blockMessage, string Name);
};

