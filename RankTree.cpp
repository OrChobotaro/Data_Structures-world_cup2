#include "RankTree.h"

RankTree::RankTree() : AvlTree<AbilityDataTeam>() {}



////////MakeSure that fatherFunc checks node != NULL
int RankTree::calcTotalNodesInSubTree(Node<AbilityDataTeam>* node) {
    int totalNodes = 1;
    if (node->getLeft()) {
        totalNodes += node->getLeft()->getKey().getTotalNodesInSubTrees();
    }
    if (node->getRight()) {
        totalNodes += node->getRight()->getKey().getTotalNodesInSubTrees();
    }
    return totalNodes;
}



void RankTree::updateHeights(Node<AbilityDataTeam> *node) {
    AvlTree<AbilityDataTeam>::updateHeights(node);
    while (node) {
        if (node->isLeaf()) {
            node->m_key.setTotalNodesInSubTrees(1);
            node = node->getParent();
            continue;
        }
        int totalNodes = calcTotalNodesInSubTree(node);
        node->m_key.setTotalNodesInSubTrees(totalNodes);
        node = node->getParent();
    }
}


Node<AbilityDataTeam>* RankTree::findIndex(int index) {
    int totalNodesInTree = getRoot()->getKey().getTotalNodesInSubTrees();
    if (index >= totalNodesInTree || index < 0) {
        return nullptr;
    }
    Node<AbilityDataTeam>* node = findIndexAux(index + 1, getRoot());
/*    Node<AbilityDataTeam>* rightSon = node->getRight();
    Node<AbilityDataTeam>* parent = node->getParent();
    if (rightSon && parent) {
        if (rightSon < parent) {
            return rightSon;
        }
        else {
            return parent;
        }
    }
    else if (rightSon) {
        return rightSon;
    }
    else if (parent) {
        return parent;
    }
    return nullptr;*/
    return node;
}



Node<AbilityDataTeam>* RankTree::findIndexAux(int index, Node<AbilityDataTeam>* node) {
    if (!node) {
        return nullptr;
    }
    int nodesInLeftSubTree = 0;
    Node<AbilityDataTeam>* leftSon = node->getLeft();
    if (leftSon) {
        nodesInLeftSubTree = leftSon->getKey().getTotalNodesInSubTrees();
    }
    if (nodesInLeftSubTree == index-1) {
        return node;
    }
    else if (nodesInLeftSubTree > index - 1) {
        return findIndexAux(index, leftSon);
    }
    else {
        return findIndexAux(index-nodesInLeftSubTree-1, node->getRight());
    }
}
