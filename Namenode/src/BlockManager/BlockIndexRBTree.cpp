#include "BlockManager/BlockIndexRBTree.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;
BlockIndexRBTree::BlockIndexRBTree() :BlockIndex() {
	rson = NULL;
	lson = NULL;
	fa = NULL;
	son = NULL;
	key = -1;
	RB = true;
	TF = false;
}
BlockIndexRBTree::BlockIndexRBTree(LocatedBlocks* nul) :BlockIndex(nul) {
	rson = NULL;
	lson = NULL;
	fa = NULL;
	son = NULL;
	key = -1;
	RB = true;
	TF = false;
}
BlockIndexRBTree::BlockIndexRBTree(bool b, LocatedBlocks* nul) :BlockIndex(nul) {
	rson = NULL;
	lson = NULL;
	fa = NULL;
	son = NULL;
	key = 0;
	RB = true;
	TF = b;
}
BlockIndexRBTree::BlockIndexRBTree(BlockIndexRBTree* Fa, int Key, LocatedBlocks* blockMessage) :BlockIndex(blockMessage) {
	rson = NULL;
	lson = NULL;
	fa = Fa;
	son = NULL;
	key = Key;
	RB = true;
	TF = true;
}
void BlockIndexRBTree::left_turn(BlockIndexRBTree** b) {
	BlockIndexRBTree* a = *b;
	BlockIndexRBTree* rs = a->rson;
	a->rson = rs->lson;
	a->rson->fa = a;
	rs->lson = a;
	rs->fa = a->fa;
	if (a->fa->lson == a) a->fa->lson = rs;
	else a->fa->rson = rs;
	a->fa = rs;
}
void BlockIndexRBTree::right_turn(BlockIndexRBTree** b) {
	BlockIndexRBTree* a = *b;
	BlockIndexRBTree* ls = a->lson;
	a->lson = ls->rson;
	a->lson->fa = a;
	ls->rson = a;
	ls->fa = a->fa;
	if (a->fa->lson == a) a->fa->lson = ls;
	else a->fa->rson = ls;
	a->fa = ls;
}
BlockIndexRBTree* BlockIndexRBTree::MakeNULLSon() {
	LocatedBlocks* nul;
	nul = new LocatedBlocks;
	BlockIndexRBTree *l;
	l = new BlockIndexRBTree(nul);
	return l;
}
BlockIndexRBTree* BlockIndexRBTree::brother(BlockIndexRBTree** a) {
	BlockIndexRBTree* t = *a;
	if (t->fa->lson == t) {
		return t->fa->rson;
	}
	else return t->fa->lson;
}
void BlockIndexRBTree::incheck(BlockIndexRBTree** root, BlockIndexRBTree** a) {
	BlockIndexRBTree* temp = *a;
	if (temp == (*root)->lson) {
		temp->RB = black;
		return;
	}
	if (temp->fa->RB == red) {
		if (temp->fa == (*root)->lson) {
			temp->fa->RB = black;
			return;
		}
		if (brother(&(temp->fa))->RB == red) {
			temp->fa->fa->RB = red;
			temp->fa->RB = black;
			brother(&(temp->fa))->RB = black;
			if (temp->fa->fa == (*root)->lson) temp->fa->fa->RB = black;
			else incheck(root, &(temp->fa->fa));
		}
		else if (brother(&(temp->fa))->RB == black) {
			if (temp->fa->fa->lson == temp->fa && temp->fa->lson == temp) {
				temp->fa->RB = black;
				temp->fa->fa->RB = red;
				right_turn(&(temp->fa->fa));
			}
			else if (temp->fa->fa->lson == temp->fa && temp->fa->lson != temp) {
				left_turn(&(temp->fa));
				incheck(root, &(temp->lson));
			}
			else if (temp->fa->fa->lson != temp->fa && temp->fa->lson != temp) {
				temp->fa->RB = black;
				temp->fa->fa->RB = red;
				left_turn(&(temp->fa->fa));
			}
			else if (temp->fa->fa->lson != temp->fa && temp->fa->lson == temp) {
				right_turn(&(temp->fa));
				incheck(root, &(temp->rson));
			}
		}
	}

}
bool BlockIndexRBTree::insert(BlockIndexRBTree** root, int x, string Name, LocatedBlocks* blockMessage) {
	BlockIndexRBTree* tmp;
	tmp = new BlockIndexRBTree(NULL, x, blockMessage);
	tmp->name = Name;
	tmp->RB = red;
	tmp->lson = MakeNULLSon();
	tmp->rson = MakeNULLSon();
	tmp->lson->fa = tmp;
	tmp->rson->fa = tmp;
	if ((*root)->lson == NULL) {
		tmp->RB = black;
		tmp->fa = *root;
		tmp->fa->lson = tmp;
		return true;
	}
	BlockIndexRBTree* t = (*root)->lson;
	while (t) {
		if (t->key > tmp->key) {
			if (t->lson->TF == false) {
				free(t->lson);
				t->lson = tmp;
				tmp->fa = t;
				t = NULL;
				incheck(root, &tmp);
			}
			else t = t->lson;
		}
		else {
			if (t->key == tmp->key) {
				if (t->name == tmp->name) {
					LocatedBlock* m = t->BlockMessage->add_blocks();
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
				if (checkCPHead()) {
					return t->son->insert(son, tmp->BlockMessage, tmp->name);
				}
				else {
					return t->createCPHead(tmp->name, tmp->BlockMessage);
				}
			}
			if (t->rson->TF == false) {
				free(t->rson);
				t->rson = tmp;
				tmp->fa = t;
				t = NULL;
				incheck(root, &tmp);
			}
			else t = t->rson;
		}
	}
	return true;
}
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
BlockIndexRBTree* BlockIndexRBTree::FindMidOrderSuccessorNode(BlockIndexRBTree** a) {
	BlockIndexRBTree* temp = *a;
	temp = temp->rson;
	while (temp->lson->TF != false) {
		temp = temp->lson;
	}
	return temp;
}
void BlockIndexRBTree::movecheck(BlockIndexRBTree** root, BlockIndexRBTree** a) {
	BlockIndexRBTree* temp = *a;
	if (temp == (*root)->lson) return;
	if (brother(&temp)->RB == red) {
		temp->fa->RB = red;
		brother(&temp)->RB = black;
		if (temp->fa->lson == temp) {
			left_turn(&(temp->fa));
			left_turn(&(temp->fa));
		}
		else {
			right_turn(&(temp->fa));
			right_turn(&(temp->fa));
		}
	}
	else {
		if (brother(&temp)->lson->RB == black && brother(&temp)->rson->RB == black) {
			if (temp->fa->RB == red) {
				temp->fa->RB = black;
				brother(&temp)->RB = red;
			}
			else {
				brother(&temp)->RB = red;
				movecheck(root, &(temp->fa));
			}
		}
		else {
			if (temp->fa->lson == temp && brother(&temp)->rson->RB == black) {
				BlockIndexRBTree* bro = brother(&temp);
				bro->RB = red;
				bro->lson->RB = black;
				right_turn(&bro);
			}
			else if (temp->fa->rson == temp && brother(&temp)->lson->RB == black) {
				BlockIndexRBTree* bro = brother(&temp);
				bro->RB = red;
				bro->rson->RB = black;
				left_turn(&bro);
			}
			if (temp->fa->lson == temp && brother(&temp)->rson->RB == red) {
				brother(&temp)->RB = temp->fa->RB;
				temp->fa->RB = black;
				brother(&temp)->rson->RB = black;
				left_turn(&(temp->fa));
			}
			else if (temp->fa->rson == temp && brother(&temp)->lson->RB == red) {
				brother(&temp)->RB = temp->fa->RB;
				temp->fa->RB = black;
				brother(&temp)->lson->RB = black;
				right_turn(&(temp->fa));
			}
		}
	}
}
bool BlockIndexRBTree::remove(BlockIndexRBTree** root, int x, string Name) {
	BlockIndexRBTree* temp = (*root)->lson;
	while (temp->key != x) {
		if (temp->key > x) {
			if (!temp->lson->TF) return false;
			else temp = temp->lson;
		}
		else {
			if (temp->rson->TF == false) return false;
			else temp = temp->rson;
		}
	}
	if (!(temp->name == Name)) {
		if (temp->checkCPHead()) {
			return temp->son->remove(this->son, Name);
		}
		else return false;
	}
	if (temp->checkCPHead()) {
		LocatedBlocks* a = temp->son->inquireALL(temp->son, temp->son->name);
		temp->name = temp->son->name;
		temp->BlockMessage = a;
		temp->son->remove(temp->son, temp->son->name);
		return true;
	}
	BlockIndexRBTree* t;
	if (temp->lson->TF != false && temp->rson->TF != false) {
		t = FindMidOrderSuccessorNode(&temp);
		swap(t->key, temp->key);
		temp = t;
	}
	///
	if (temp->lson->TF != false || temp->rson->TF != false) {
		temp->RB = red;
		if (temp->lson->TF != false) {
			temp->lson->RB = black;
			right_turn(&temp);
		}
		else {
			temp->rson->RB = black;
			left_turn(&temp);
		}
	}
	else if (temp->RB == black) {
		if (temp->fa->RB == red) {
			if (temp->fa->lson == temp) {
				left_turn(&(temp->fa));
			}
			else right_turn(&(temp->fa));
		}
		else {
			if (brother(&temp)->RB == red) {
				brother(&temp)->RB = black;
				temp->fa->RB = red;
				if (temp->fa->lson == temp) {
					left_turn(&(temp->fa));
					left_turn(&(temp->fa));
				}
				else {
					right_turn(&(temp->fa));
					right_turn(&(temp->fa));
				}
			}
			else {
				if (brother(&temp)->lson->TF != false || brother(&temp)->rson->TF != false) {
					BlockIndexRBTree* bro = brother(&temp);
					if (temp->fa->lson == temp && bro->rson->TF == false) {
						bro->lson->RB = black;
						bro->RB = red;
						right_turn(&bro);
					}
					else if (temp->fa->rson == temp && bro->lson->TF == false) {
						bro->rson->RB = black;
						bro->RB = red;
						left_turn(&bro);
					}
					if (temp->fa->lson == temp && brother(&temp)->rson->TF != false) {
						brother(&temp)->rson->RB = black;
						left_turn(&(temp->fa));
					}
					else if (temp->fa->rson == temp && brother(&temp)->lson->TF != false) {
						brother(&temp)->lson->RB = black;
						left_turn(&(temp->fa));
					}
				}
				else {
					brother(&temp)->RB = red;
					movecheck(root, &(temp->fa));
				}
			}
		}
	}
	if (temp->fa->lson == temp) {
		temp->fa->lson = MakeNULLSon();
		temp->fa->lson->fa = temp->fa;
	}
	else {
		temp->fa->rson = MakeNULLSon();
		temp->fa->rson->fa = temp->fa;
	}
	delete temp->lson;
	delete temp->rson;
	delete temp;
	return true;
}
bool BlockIndexRBTree::checkCPHead() {
	if (this->son) return true;
	else return false;
}
bool BlockIndexRBTree::createCPHead(string Name, LocatedBlocks* blockMessage) {
	BlockIndexClashPoint a(blockMessage, Name);
	this->son = &a;
	return true;
}
LocatedBlocks* BlockIndexRBTree::inquireALL(BlockIndexRBTree** root, int x, string name) {
    BlockIndexRBTree* temp = (*root)->lson;
    int cnt = 0;
    while (++cnt) {
        if (temp->key > x) {
            if (temp->lson->TF != false) {
                temp = temp->lson;
                continue;
            }
            else return nullptr;
        }
        if (temp->key < x) {
            if (temp->rson->TF != false) {
                temp = temp->rson;
                continue;
            }
            else return nullptr;
        }
        if (temp->key == x) {
            if (temp->name == name) {
                return temp->BlockMessage;
            }
            else {
                if (temp->checkCPHead()) {
                    return temp->son->inquireALL(temp->son, name);
                }
                else {
                    return nullptr;
                }
            }
        }
    }
}
const LocatedBlock* BlockIndexRBTree::inquire(BlockIndexRBTree** root, int x, string name, uint64_t blockID) {
    BlockIndexRBTree* temp = (*root)->lson;
    int cnt = 0;
    while (++cnt) {
        if (temp->key > x) {
            if (temp->lson->TF != false) {
                temp = temp->lson;
                continue;
            }
            else return nullptr;
        }
        if (temp->key < x) {
            if (temp->rson->TF != false) {
                temp = temp->rson;
                continue;
            }
            else return nullptr;
        }
        if (temp->key == x) {
            if (temp->name == name) {
                for (int i = 0; i < temp->BlockMessage->blocks_size(); i++) {
                    if (temp->BlockMessage->blocks(i).block().blockid()) {
                        return &(temp->BlockMessage->blocks(i));
                    }
                }
                return nullptr;
            }
            else {
                if (temp->checkCPHead()) {
                    return temp->son->inquire(temp->son, name, blockID);
                }
                else {
                    return nullptr;
                }
            }
        }
    }
}
LSMessage BlockIndexRBTree::GetLeftSon() {
	LSMessage a;
	if (this->lson->TF == false) {
		return a;
	}
	else {
		a.BlockMessage = this->lson->BlockMessage;
		a.name = this->lson->name;
		a.key = this->lson->key;
		return a;
	}
}

queue<pair<uint64_t, int> > BlockIndexRBTree::checkBackups(BlockIndexRBTree* root) {
    return checkBackups1(root->lson);
}
queue<pair<uint64_t, int> > BlockIndexRBTree::checkBackups1(BlockIndexRBTree* temp) {

    queue<pair<uint64_t, int> > q;
    for (int i = 0; i < temp->BlockMessage->blocks_size(); i++) {
        if (temp->BlockMessage->blocks(i).locs_size() < 3) {
            pair<uint64_t, int> a(temp->BlockMessage->blocks(i).block().blockid(), temp->BlockMessage->blocks(i).locs_size() - 1);
            q.push(a);
        }
    }
    queue<pair<uint64_t, int> > q1;
    if (checkCPHead()) {
        q1 = temp->son->checkBackups(temp->son);
        for (; q1.size() > 0; q1.pop()) {
            q.push(q1.front());
        }
    }
    if (temp->lson->TF) {
        q1 = checkBackups1(temp->lson);
        for (; q1.size() > 0; q1.pop()) {
            q.push(q1.front());
        }
    }
    if (temp->rson->TF) {
        q1 = checkBackups1(temp->rson);
        for (; q1.size() > 0; q1.pop()) {
            q.push(q1.front());
        }
    }
    return q;
}

bool BlockIndexRBTree::insertBackups(BlockIndexRBTree** root, int x, string name, uint64_t blockid, pair<string, string> backupsDatanodeid) {
    BlockIndexRBTree* temp = (*root)->lson;
    int cnt = 0;
    while (++cnt) {
        if (temp->key > x) {
            if (temp->lson->TF != false) {
                temp = temp->lson;
                continue;
            }
            else return false;
        }
        if (temp->key < x) {
            if (temp->rson->TF != false) {
                temp = temp->rson;
                continue;
            }
            else return false;
        }
        if (temp->key == x) {
            if (temp->name == name) {
                for (int i = 0; i < temp->BlockMessage->blocks_size(); i++) {
                    if (temp->BlockMessage->blocks(i).block().blockid() == blockid) {
                        if (backupsDatanodeid.first != "") {
                            auto block = temp->BlockMessage->blocks(i);
                            auto D = block.add_locs();
                            DatanodeID* Did;
                            Did = new DatanodeID;
                            Did->set_datanodeuuid(backupsDatanodeid.first);
                            D->set_allocated_id(Did);
                        }
                        if (backupsDatanodeid.second != "") {
                            auto block = temp->BlockMessage->blocks(i);
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
                if (temp->checkCPHead()) {
                    return temp->son->insertBackups(temp->son, name, blockid, backupsDatanodeid);
                }
                else {
                    return false;
                }
            }
        }
    }
}