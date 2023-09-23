//
// Created by lxx18 on 2023/8/25.
//

#ifndef NAMENODE_FSPERMISSION_H
#define NAMENODE_FSPERMISSION_H
enum class FsAction{
    NONE,
    EXECUTE
};

class FsPermission {
private:
    FsAction userAction;
    FsAction groupAction;
    FsAction otherAction;
public:
    FsAction userAct();

    FsAction groupAct();

    FsAction otherAct();
};

#endif //NAMENODE_FSPERMISSION_H
