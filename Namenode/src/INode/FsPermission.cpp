//
// Created by lxx18 on 2023/8/25.
//
#include "INode/FsPermission.h"

FsAction FsPermission::userAct() {
    return FsAction::NONE;
}

FsAction FsPermission::groupAct() {
    return FsAction::NONE;
}

FsAction FsPermission::otherAct() {
    return FsAction::NONE;
}
