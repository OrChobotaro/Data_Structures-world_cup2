#include "RankTree.h"
#include "worldcup23a2.h"
#include <stdio.h>



int main7(){

    AvlTree<int> tree;

    tree.insert(4);
    tree.insert(8);
    tree.insert(2);
    tree.insert(5);
    tree.insert(7);
    tree.insert(21);
    tree.insert(51);
    tree.insert(71);

    std::cout << countNodes(tree.getRoot());

    world_cup_t wc;

    TeamData team1(11);
    TeamData team2(12);
    TeamData team3(13);
    TeamData team4(14);
    TeamData team5(15);

    wc.m_teamTree->insert(team1);
    wc.m_teamTree->insert(team2);
    wc.m_teamTree->insert(team3);
    wc.m_teamTree->insert(team4);
    wc.m_teamTree->insert(team5);

    PlayerData* player1 = new PlayerData(1, permutation_t::neutral(), 3, 4, 5, true);
    PlayerData* player2 = new PlayerData(2, permutation_t::neutral(), 5, 7, 2, false);
    PlayerData* player3 = new PlayerData(3, permutation_t::neutral(), 1, 2, 2, true);


    wc.m_hashTable->insert(player1);
    wc.m_hashTable->insert(player2);
    wc.m_hashTable->insert(player3);


    Node<TeamData>* teamNode = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());



    return 0;
}
/*

#include "hashTable.h"


int main(){
    HashTable hash(10);
    int per_arr[5] = {1,2,3,4,5};

    permutation_t per(per_arr);
    PlayerData data(8, per, 2, 5, 5,true);

    hash.insert(&data);

    std::shared_ptr<LinkedList<HashPlayerData>> list = hash.getArr()[8];

    return list != nullptr && list->countNodes() == 1 && list->getStart()->getNext()->getData().getID() == 8;

}*/
