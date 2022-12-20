/*
#ifndef DATA_STRUCTURES_EX2_UNIONFIND_H
#define DATA_STRUCTURES_EX2_UNIONFIND_H

#include "hashTable.h"
#include "avlTree.h"
#include "UnionFindData.h"


class UnionFind {

*/
/*    PlayerData* makeSet(int playerID, const permutation_t& spirit, int gamesPlayed, int ability, int cards,
                        bool goalKeeper, Node<TeamData>* ptrTeam);*//*

    Node<TeamData>* findTeamAux(PlayerData* player);
    Node<TeamData>* unionTeamsAux(Node<TeamData>* team1, Node<TeamData>* team2);

private:
    std::shared_ptr<AvlTree<TeamData>>* m_TeamTree;
};


#endif //DATA_STRUCTURES_EX2_UNIONFIND_H
*/
