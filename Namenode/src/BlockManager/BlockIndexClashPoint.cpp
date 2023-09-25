#include "BlockIndexClashPoint.h"
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
    LocatedBlocks* fail;
    fail = new LocatedBlocks;
    return fail;
}
