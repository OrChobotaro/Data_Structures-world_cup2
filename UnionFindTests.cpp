#include <iostream>
#include "wet2util.h"
#include "worldcup23a2.h"


using namespace std;

#define RUN_TEST(test) \
do { \
  cout << "     Running " << #test << "... "; \
  if (test()) { \
    cout << "[OK]"; \
  }                    \
    else { \
    cout << "[Error]"; \
  } \
  cout << endl; \
} while(0)




bool test_union_player_to_empty_team() {
    world_cup_t wc;

    TeamData team1(11);
    TeamData team2(12);
    TeamData team3(13);

    wc.m_teamTree->insert(team1);
    wc.m_teamTree->insert(team2);
    wc.m_teamTree->insert(team3);

    PlayerData* player1 = new PlayerData(1, permutation_t::neutral(), 3, 4, 5, true);
    PlayerData* player2 = new PlayerData(2, permutation_t::neutral(), 5, 7, 2, false);

    wc.m_hashTable->insert(player1);
    wc.m_hashTable->insert(player2);

    Node<TeamData>* teamNode11 = wc.findTeamInTeamTree(11, wc.m_teamTree->getRoot());
    Node<TeamData>* teamNode12 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());

    bool res1 = wc.unionPlayerToEmptyTeam(1, teamNode11);
    bool res2 = wc.unionPlayerToEmptyTeam(1, teamNode11);
    bool res3 = wc.unionPlayerToEmptyTeam(1, teamNode12);
    bool res4 = wc.unionPlayerToEmptyTeam(2, teamNode11);

    return res1 == true && res2 == false && res3 == false && res4 == false;

}



bool test_union_player_to_team() {
    world_cup_t wc;

    TeamData team1(11);
    TeamData team2(12);
    TeamData team3(13);

    wc.m_teamTree->insert(team1);
    wc.m_teamTree->insert(team2);
    wc.m_teamTree->insert(team3);

    PlayerData* player1 = new PlayerData(1, permutation_t::neutral(), 3, 4, 5, true);
    PlayerData* player2 = new PlayerData(2, permutation_t::neutral(), 5, 7, 2, false);
    PlayerData* player3 = new PlayerData(3, permutation_t::neutral(), 1, 2, 2, true);
    PlayerData* player4 = new PlayerData(4, permutation_t::neutral(), 8, 5, 7, false);
    PlayerData* player5 = new PlayerData(5, permutation_t::neutral(), 3, 11, 3, false);
    PlayerData* player6 = new PlayerData(6, permutation_t::neutral(), 9, 8, 4, false);

    player1->setCalcTotalGamesPlayed(20);
    int arr[5] = {5, 4, 2, 1, 3};
    player1->setCalcPartialSpirit(arr);

    wc.m_hashTable->insert(player1);
    wc.m_hashTable->insert(player2);
    wc.m_hashTable->insert(player3);
    wc.m_hashTable->insert(player4);
    wc.m_hashTable->insert(player5);
    wc.m_hashTable->insert(player6);

    Node<TeamData>* teamNode11 = wc.findTeamInTeamTree(11, wc.m_teamTree->getRoot());
    Node<TeamData>* teamNode12 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());
    Node<TeamData>* teamNode13 = wc.findTeamInTeamTree(13, wc.m_teamTree->getRoot());

    bool res1 = wc.unionPlayerToEmptyTeam(1, teamNode11);
    bool res2 = wc.unionPlayerToEmptyTeam(2, teamNode12);
    bool res3 = wc.unionPlayerToEmptyTeam(3, teamNode13);
    bool res4 = wc.unionPlayerToTeam(4, teamNode11);
    bool res5 = wc.unionPlayerToTeam(4, teamNode11);
    bool res6 = wc.unionPlayerToTeam(5, teamNode11);
    bool res7 = wc.unionPlayerToTeam(6, teamNode11);
    bool res8 = wc.unionPlayerToTeam(4, teamNode12);

    return res1 == true  &&  res2 == true  &&  res3 == true &&
            res4 == true  && res5 == false  && res6 == true && res7 == true  &&  res8 == false;
}



bool test_union_buyer_team_is_bigger() {
    world_cup_t wc;

    TeamData team1(11);
    TeamData team2(12);
    TeamData team3(13);
    TeamData team4(14);
    TeamData team5(15);
    TeamData team6(16);

    wc.m_teamTree->insert(team1);
    wc.m_teamTree->insert(team2);
    wc.m_teamTree->insert(team3);
    wc.m_teamTree->insert(team4);
    wc.m_teamTree->insert(team5);
    wc.m_teamTree->insert(team6);

    PlayerData* player1 = new PlayerData(1, permutation_t::neutral(), 3, 4, 5, true);
    PlayerData* player2 = new PlayerData(2, permutation_t::neutral(), 5, 7, 2, false);
    PlayerData* player3 = new PlayerData(3, permutation_t::neutral(), 1, 2, 2, true);
    PlayerData* player4 = new PlayerData(4, permutation_t::neutral(), 8, 5, 7, false);
    PlayerData* player5 = new PlayerData(5, permutation_t::neutral(), 3, 11, 3, false);
    PlayerData* player6 = new PlayerData(6, permutation_t::neutral(), 9, 8, 4, false);
    PlayerData* player7 = new PlayerData(7, permutation_t::neutral(), 2, 19, 8, false);
    PlayerData* player8 = new PlayerData(8, permutation_t::neutral(), 3, 5, 7, true);
    PlayerData* player9 = new PlayerData(9, permutation_t::neutral(), 6, 2, 4, false);

    wc.m_hashTable->insert(player1);
    wc.m_hashTable->insert(player2);
    wc.m_hashTable->insert(player3);
    wc.m_hashTable->insert(player4);
    wc.m_hashTable->insert(player5);
    wc.m_hashTable->insert(player6);
    wc.m_hashTable->insert(player7);
    wc.m_hashTable->insert(player8);
    wc.m_hashTable->insert(player9);

    Node<TeamData>* teamNode11 = wc.findTeamInTeamTree(11, wc.m_teamTree->getRoot());
    Node<TeamData>* teamNode12 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());
    Node<TeamData>* teamNode13 = wc.findTeamInTeamTree(13, wc.m_teamTree->getRoot());
    Node<TeamData>* teamNode14 = wc.findTeamInTeamTree(14, wc.m_teamTree->getRoot());


    bool res1 = wc.unionPlayerToEmptyTeam(1, teamNode11);
    player1->setCalcTotalGamesPlayed(5);
    bool res2 = wc.unionPlayerToTeam(2, teamNode11);
    bool res3 = wc.unionPlayerToEmptyTeam(3, teamNode12);
    player3->setCalcTotalGamesPlayed(7);
    bool res4 = wc.unionBigBuyerTeamToSmallTeam(teamNode11, teamNode12);
    player1->setCalcTotalGamesPlayed(3);

    bool res5 = wc.m_teamTree->find(teamNode12->getKey());
    bool res6 = wc.unionPlayerToEmptyTeam(4, teamNode13);
    bool res7 = wc.unionPlayerToTeam(5, teamNode13);
    player4->setCalcTotalGamesPlayed(4);
    bool res8 = wc.unionPlayerToTeam(6, teamNode13);
    bool res9 = wc.unionPlayerToTeam(7, teamNode13);
    player4->setCalcTotalGamesPlayed(9);
    bool res10 = wc.unionBigBuyerTeamToSmallTeam(teamNode13, teamNode11);
    bool res11 = wc.m_teamTree->find(teamNode11->getKey());
    bool res12 = wc.m_teamTree->find(teamNode11->getKey());

    return res1 == true  &&  res2 == true  &&  res3 == true  &&  res4 == true  &&  res5 == false  &&
            res6 == true  &&  res7 == true  &&  res8 == true  &&  res9 == true  &&  res10 == true  &&
            res11 == false  &&  res12 == false;
}




bool test_complex_union() {
        world_cup_t wc;

        TeamData team1(11);
        TeamData team2(12);
        TeamData team3(13);
        TeamData team4(14);
        TeamData team5(15);
        TeamData team6(16);
        TeamData team7(17);
        TeamData team8(18);

        wc.m_teamTree->insert(team1);
        wc.m_teamTree->insert(team2);
        wc.m_teamTree->insert(team3);
        wc.m_teamTree->insert(team4);
        wc.m_teamTree->insert(team5);
        wc.m_teamTree->insert(team6);
        wc.m_teamTree->insert(team7);
        wc.m_teamTree->insert(team8);

        PlayerData* player1 = new PlayerData(1, permutation_t::neutral(), 3, 4, 5, true);
        PlayerData* player2 = new PlayerData(2, permutation_t::neutral(), 5, 7, 2, false);
        PlayerData* player3 = new PlayerData(3, permutation_t::neutral(), 1, 2, 2, true);
        PlayerData* player4 = new PlayerData(4, permutation_t::neutral(), 8, 5, 7, false);
        PlayerData* player5 = new PlayerData(5, permutation_t::neutral(), 3, 11, 3, false);
        PlayerData* player6 = new PlayerData(6, permutation_t::neutral(), 9, 8, 4, false);

        wc.m_hashTable->insert(player1);
        wc.m_hashTable->insert(player2);
        wc.m_hashTable->insert(player3);
        wc.m_hashTable->insert(player4);
        wc.m_hashTable->insert(player5);
        wc.m_hashTable->insert(player6);

        Node<TeamData>* teamNode11 = wc.findTeamInTeamTree(11, wc.m_teamTree->getRoot());
        Node<TeamData>* teamNode12 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());
        Node<TeamData>* teamNode13 = wc.findTeamInTeamTree(13, wc.m_teamTree->getRoot());
        Node<TeamData>* teamNode14 = wc.findTeamInTeamTree(14, wc.m_teamTree->getRoot());
        return true;
};




int main(){
    RUN_TEST(test_union_player_to_empty_team);
    RUN_TEST(test_union_player_to_team);
    RUN_TEST(test_union_buyer_team_is_bigger);
    return 0;
}