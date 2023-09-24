#include "BlockManager/BlockIndexHash.h"
#include <string>
BlockIndexHash::BlockIndexHash(LocatedBlocks* blockMessage) :BlockIndex(blockMessage) {
	son = NULL;
}
BlockIndexHash::BlockIndexHash():BlockIndex() {
    son = NULL;
}
bool BlockIndexHash::insert(string name, int xx, LocatedBlocks* blockMessage) {
    if(this->BlockMessage == nullptr) {
        this->BlockMessage = blockMessage;
        this->name = name;
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
	LocatedBlocks* nul;
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
			this->BlockMessage = nul;
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
