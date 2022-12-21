#ifndef DATA_STRUCTURES_EX2_RANKTREE_H
#define DATA_STRUCTURES_EX2_RANKTREE_H

#include "UnionFindData.h"
#include "avlTree.h"

class RankTree : public AvlTree<AbilityDataTeam> {
public:
    RankTree();
    RankTree(const RankTree& rankTree) = delete;
    RankTree& operator=(const RankTree& rankTree) = delete;
    ~RankTree() override = default;

    int calcTotalNodesInSubTree(Node<AbilityDataTeam>* node);
    void updateHeights(Node<AbilityDataTeam> *node) override;

    Node<AbilityDataTeam>* findIndexAux(int index, Node<AbilityDataTeam>* node);
    Node<AbilityDataTeam>* findIndex(int index);

};


#endif //DATA_STRUCTURES_EX2_RANKTREE_H
