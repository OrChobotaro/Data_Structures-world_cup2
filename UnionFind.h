#ifndef DATA_STRUCTURES_EX2_UNIONFIND_H
#define DATA_STRUCTURES_EX2_UNIONFIND_H

#include "hashTable.h"
#include "avlTree.h"
#include "UnionFindData.h"


class UnionFind {
    Node<TeamData>* findTeamAux(PlayerData* player);
private:
    std::shared_ptr<AvlTree<TeamData>>* m_TeamTree;
};


#endif //DATA_STRUCTURES_EX2_UNIONFIND_H
