#include "BlockManager/BlockIndexHash.h"
#include <string>
BlockIndexHash::BlockIndexHash(LocatedBlocks* blockMessage) :BlockIndex(blockMessage) {
	son = NULL;
}
BlockIndexHash::BlockIndexHash() :BlockIndex() {
	son = NULL;
}
bool BlockIndexHash::insert(string name, int xx, LocatedBlocks* blockMessage) {
    if(this->BlockMessage == nullptr) {
		this->BlockMessage = blockMessage;
        this->name = name;
        return true;
    }
	else {
		if (this->name == name) {
			LocatedBlock* m = this->BlockMessage->add_blocks();
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
		if (checkRBTreeRoot()) {
			return this->son->insert(&(this->son), xx, name, blockMessage);
		}
		else {
			return createRBTreeRoot(name, xx, blockMessage);
		}
	}
}
bool BlockIndexHash::checkRBTreeRoot() {
	if (this->son == NULL) return false;
	return true;
}
bool BlockIndexHash::createRBTreeRoot(string name, int xx,LocatedBlocks* blockMessage) {
	this->son = new BlockIndexRBTree;
	this->son->insert(&(this->son), xx, name, blockMessage);
	return true;
}
bool BlockIndexHash::remove(int xx, string name) {
	if (this->name == name) {
		if (checkRBTreeRoot()) {
			LSMessage tmp = this->son->GetLeftSon();
			if (tmp.name.empty()) {
				this->son = NULL;
				this->BlockMessage = nullptr;
				this->name = "";
				return true;
			}
			else {
				this->name = tmp.name;
				this->BlockMessage = tmp.BlockMessage;
				return this->son->remove(&(this->son), tmp.key, tmp.name);
			}
		}
		else {
			this->BlockMessage = nullptr;
			this->name = "";
			return true;
		}
	}
	else {
		return this->son->remove(&(this->son), xx, name);
	}
}
LocatedBlocks* BlockIndexHash::inquireALL(int xx, string name) {
    if (this->name == name) {
        return this->BlockMessage;
    }
    else {
        return this->son->inquireALL(&(this->son), xx, name);
    }
}
const LocatedBlock* BlockIndexHash::inquire(int xx, string name, uint64_t blockID) {
    if (this->name == name) {
        for (int i = 0; i < this->BlockMessage->blocks_size(); i++) {
            if (this->BlockMessage->blocks(i).block().blockid()) {
                return &(this->BlockMessage->blocks(i));
            }
        }
        return nullptr;
    }
    else {
        return this->son->inquire(&(this->son), xx, name, blockID);
    }
}

queue<pair<uint64_t, int> > BlockIndexHash::checkBackups() {
    queue<pair<uint64_t, int> > q;
    if (this->BlockMessage == nullptr) return q;
    for (int i = 0; i < this->BlockMessage->blocks_size(); i++) {
        if (this->BlockMessage->blocks(i).locs_size() < 3) {
            pair<uint64_t, int> a(this->BlockMessage->blocks(i).block().blockid(), this->BlockMessage->blocks(i).locs_size() - 1);
            q.push(a);
        }
    }
    queue<pair<uint64_t, int> > q1;
    if (this->checkRBTreeRoot()) {
        q1 = this->son->checkBackups(this->son);
        for (; q1.size() > 0; q1.pop()) {
            q.push(q1.front());
        }
    }
    return q;
}

bool BlockIndexHash::insertBackups(int xx, string name, uint64_t blockid, pair<string, string> backupsDatanodeid) {
    if (this->name == name) {
        for (int i = 0; i < this->BlockMessage->blocks_size(); i++) {
            if (this->BlockMessage->blocks(i).block().blockid() == blockid) {
                if (backupsDatanodeid.first != "") {
                    auto block = this->BlockMessage->blocks(i);
                    auto D = block.add_locs();
                    DatanodeID* Did;
                    Did = new DatanodeID;
                    Did->set_datanodeuuid(backupsDatanodeid.first);
                    D->set_allocated_id(Did);
                }
                if (backupsDatanodeid.second != "") {
                    auto block = this->BlockMessage->blocks(i);
                    auto D = block.add_locs();
                    DatanodeID* Did;
                    Did = new DatanodeID;
                    Did->set_datanodeuuid(backupsDatanodeid.second);
                    D->set_allocated_id(Did);
                }
                break;
            }
        }
        return true;
    }
    else {
        return this->son->insertBackups(&(this->son), xx, name, blockid, backupsDatanodeid);
    }
}
