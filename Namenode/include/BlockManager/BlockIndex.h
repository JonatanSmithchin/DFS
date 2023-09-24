#pragma once
#include <iostream>
#include <cstring>
#include "proto/dfs.pb.h"

using namespace std;
class BlockIndex
{
protected:
    LocatedBlocks* BlockMessage;
public:
    BlockIndex(LocatedBlocks* blockMessage);
    BlockIndex();
};

