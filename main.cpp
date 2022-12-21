/*
#include "RankTree.h"
#include "worldcup23a2.h"
#include <stdio.h>


int main(){
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

    wc.unionPlayerToEmptyTeam(1, teamNode);
    wc.unionPlayerToTeam(2, teamNode);
    wc.unionPlayerToTeam(3, teamNode);


    return 0;
}
*/
