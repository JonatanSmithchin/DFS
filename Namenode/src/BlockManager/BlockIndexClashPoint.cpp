#include "BlockManager/BlockIndexClashPoint.h"
#include <cstring>
#include <string>
#include <ctime>
BlockIndexClashPoint::BlockIndexClashPoint(LocatedBlocks* blockMessage, string Name) :BlockIndex(blockMessage) {
    name = Name;
    next = NULL;
}
bool BlockIndexClashPoint::insert(BlockIndexClashPoint* Head,LocatedBlocks* blockMessage, string Name) {
    BlockIndexClashPoint* a = new BlockIndexClashPoint(blockMessage, Name);
    BlockIndexClashPoint* temp = Head;
    if (temp->name == Name) {
        LocatedBlock* m = temp->BlockMessage->add_blocks();
        Block* B;
        B = new Block;
        B->set_blockid(blockMessage->blocks(0).block().blockid());
        B->set_generationstamp(time(nullptr));
        B->set_size(blockMessage->blocks(0).block().size());
        m->set_allocated_block(B);
        for (int i = 0; i < blockMessage->blocks(0).locs_size(); i++) {
            DatanodeInfo* D = m->add_locs();
            DatanodeID* Did;
            Did = new DatanodeID;
            Did->set_datanodeuuid(blockMessage->blocks(0).locs(i).id().datanodeuuid());
            D->set_allocated_id(Did);
        }
        return true;
    }
    while (temp->next) {
        if (temp->next->name == Name) {
            LocatedBlock* m = temp->next->BlockMessage->add_blocks();
            Block* B;
            B = new Block;
            B->set_blockid(blockMessage->blocks(0).block().blockid());
            B->set_generationstamp(time(nullptr));
            B->set_size(blockMessage->blocks(0).block().size());
            m->set_allocated_block(B);
            for (int i = 0; i < blockMessage->blocks(0).locs_size(); i++) {
                DatanodeInfo* D = m->add_locs();
                DatanodeID* Did;
                Did = new DatanodeID;
                Did->set_datanodeuuid(blockMessage->blocks(0).locs(i).id().datanodeuuid());
                D->set_allocated_id(Did);
            }
            return true;
        }
        temp = temp->next;
    }
    temp->next = a;
    return true;
}
bool BlockIndexClashPoint::remove(BlockIndexClashPoint* Head, string Name) {
    if (Head->name == Name) {
        Head->name = Head->next->name;
        Head->BlockMessage = Head->next->BlockMessage;
        BlockIndexClashPoint* a = Head->next;
        Head->next = Head->next->next;
        delete a;
        return true;
    }
    if (Head->next == NULL) return false;
    BlockIndexClashPoint* x = Head;
    while (!(x->next->name == Name)) {
        x = x->next;
        if (x->next == NULL) return false;
    }
    if (x->next->name == Name) {
        BlockIndexClashPoint* a = x->next;
        x->next = x->next->next;
        delete a;
        return true;
    }
    else return false;
}
LocatedBlocks* BlockIndexClashPoint::inquireALL(BlockIndexClashPoint* Head, string name) {
    if (Head->name == name) {
        return Head->BlockMessage;
    }
    BlockIndexClashPoint* n = Head;
    while (n->next) {
        if (n->next->name == name) {
            return n->next->BlockMessage;
        }
        n = n->next;
    }
    return nullptr;
}
const LocatedBlock* BlockIndexClashPoint::inquire(BlockIndexClashPoint* Head, string name, uint64_t blockID) {
    if (Head->name == name) {
        for (int i = 0; i < Head->BlockMessage->blocks_size(); i++) {
            if (Head->BlockMessage->blocks(i).block().blockid()) {
                return &(Head->BlockMessage->blocks(i));
            }
        }
        return nullptr;
    }
    BlockIndexClashPoint* n = Head;
    while (n->next) {
        if (n->next->name == name) {
            for (int i = 0; i < n->next->BlockMessage->blocks_size(); i++) {
                if (n->next->BlockMessage->blocks(i).block().blockid()) {
                    return &(n->next->BlockMessage->blocks(i));
                }
            }
            return nullptr;
        }
        n = n->next;
    }
    return nullptr;
}

queue<pair<uint64_t, int> > BlockIndexClashPoint::checkBackups(BlockIndexClashPoint* Head) {
    queue<pair<uint64_t, int> > q;
    for (int i = 0; i < Head->BlockMessage->blocks_size(); i++) {
        if (Head->BlockMessage->blocks(i).locs_size() < 3) {
            pair<uint64_t, int> a(Head->BlockMessage->blocks(i).block().blockid(), Head->BlockMessage->blocks(i).locs_size() - 1);
            q.push(a);
        }
    }
    BlockIndexClashPoint* n = Head;
    while (n->next) {
        for (int i = 0; i < n->next->BlockMessage->blocks_size(); i++) {
            if (n->next->BlockMessage->blocks(i).locs_size() < 3) {
                pair<uint64_t, int> a(n->next->BlockMessage->blocks(i).block().blockid(), n->next->BlockMessage->blocks(i).locs_size() - 1);
                q.push(a);
            }
        }
    }
    return q;
}

bool BlockIndexClashPoint::insertBackups(BlockIndexClashPoint* Head, string name, uint64_t blockid, pair<string, string> backupsDatanodeid) {
    if (Head->name == name) {
        for (int i = 0; i < Head->BlockMessage->blocks_size(); i++) {
            if (Head->BlockMessage->blocks(i).block().blockid() == blockid) {
                if (backupsDatanodeid.first != "") {
                    auto block = Head->BlockMessage->blocks(i);
                    DatanodeInfo* D = block.add_locs();
                    DatanodeID* Did;
                    Did = new DatanodeID;
                    Did->set_datanodeuuid(backupsDatanodeid.first);
                    D->set_allocated_id(Did);
                }
                if (backupsDatanodeid.second != "") {
                    auto block = Head->BlockMessage->blocks(i);
                    DatanodeInfo* D = block.add_locs();
                    DatanodeID* Did;
                    Did = new DatanodeID;
                    Did->set_datanodeuuid(backupsDatanodeid.second);
                    D->set_allocated_id(Did);
                }
            }
        }
        return true;
    }
    BlockIndexClashPoint* n = Head;
    while (n->next) {
        if (n->next->name == name) {
            for (int i = 0; i < n->next->BlockMessage->blocks_size(); i++) {
                if (n->next->BlockMessage->blocks(i).block().blockid() == blockid) {
                    if (backupsDatanodeid.first != "") {
                        auto block = n->next->BlockMessage->blocks(i);
                        DatanodeInfo* D = block.add_locs();
                        DatanodeID* Did;
                        Did = new DatanodeID;
                        Did->set_datanodeuuid(backupsDatanodeid.first);
                        D->set_allocated_id(Did);
                    }
                    if (backupsDatanodeid.second != "") {
                        auto block = n->next->BlockMessage->blocks(i);
                        DatanodeInfo* D = block.add_locs();
                        DatanodeID* Did;
                        Did = new DatanodeID;
                        Did->set_datanodeuuid(backupsDatanodeid.second);
                        D->set_allocated_id(Did);
                    }
                }
            }
            return true;
        }
        n = n->next;
    }
    return false;
}
