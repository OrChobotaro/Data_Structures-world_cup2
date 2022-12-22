
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

    wc.m_teamTree->insert(team1);
    wc.m_teamTree->insert(team2);

    PlayerData* player1 = new PlayerData(1, permutation_t::neutral(), 3, 4, 5, true);

    wc.m_hashTable->insert(player1);

    Node<TeamData>* teamNode11 = wc.findTeamInTeamTree(11, wc.m_teamTree->getRoot());
    Node<TeamData>* teamNode12 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());

    bool res7 = (teamNode11->getKey().getNumPlayers() == 0);
    bool res8 = (teamNode11->getKey().getNumGoalKeepers() == 0);
    bool res9 = (teamNode11->getKey().getTeamAbility() == 0);
    bool res1 = wc.unionPlayerToTeam(1, teamNode11);
    bool res2 = wc.unionPlayerToTeam(1, teamNode11);
    bool res3 = wc.unionPlayerToTeam(1, teamNode12);
    bool res4 = (teamNode11->getKey().getNumPlayers() == 1);
    bool res5 = (teamNode11->getKey().getNumGoalKeepers() == 1);
    bool res6 = (teamNode11->getKey().getTeamAbility() == 4);

    return res1 == true && res2 == false && res3 == false &&
           res4 == true && res5 == true && res6 == true &&
           res7 == true && res8 == true && res9 == true;

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

    wc.m_hashTable->insert(player1);
    wc.m_hashTable->insert(player2);
    wc.m_hashTable->insert(player3);
    wc.m_hashTable->insert(player4);
    wc.m_hashTable->insert(player5);
    wc.m_hashTable->insert(player6);

    Node<TeamData>* teamNode11 = wc.findTeamInTeamTree(11, wc.m_teamTree->getRoot());
    Node<TeamData>* teamNode12 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());
    Node<TeamData>* teamNode13 = wc.findTeamInTeamTree(13, wc.m_teamTree->getRoot());


    bool res1 = wc.unionPlayerToTeam(1, teamNode11);
    bool res2 = wc.unionPlayerToTeam(2, teamNode12);
    bool res3 = wc.unionPlayerToTeam(3, teamNode13);
    bool res4 = wc.unionPlayerToTeam(4, teamNode11);

    bool res9 = (teamNode11->getKey().getNumPlayers() == 2);
    bool res10 = (teamNode11->getKey().getNumGoalKeepers() == 1);
    bool res11 = (teamNode11->getKey().getTeamAbility() == 9);
    bool res12 = (player4->getCalcTotalGamesPlayed() == -20);

    bool res5 = wc.unionPlayerToTeam(4, teamNode11);

    bool res13 = (teamNode11->getKey().getNumPlayers() == 2);
    bool res14 = (teamNode11->getKey().getNumGoalKeepers() == 1);
    bool res15 = (teamNode11->getKey().getTeamAbility() == 9);
    bool res16 = (player4->getCalcTotalGamesPlayed() == -20);

    bool res6 = wc.unionPlayerToTeam(5, teamNode11);
    bool res7 = wc.unionPlayerToTeam(6, teamNode11);
    bool res8 = wc.unionPlayerToTeam(4, teamNode12);

    bool res17 = (teamNode11->getKey().getNumPlayers() == 4);
    bool res18 = (teamNode11->getKey().getNumGoalKeepers() == 1);
    bool res19 = (teamNode11->getKey().getTeamAbility() == 28);
    bool res20 = (player5->getCalcTotalGamesPlayed() == -20);
    bool res21 = (player6->getCalcTotalGamesPlayed() == -20);

    return res1 == true  &&  res2 == true  &&  res3 == true &&
           res4 == true  && res5 == false  && res6 == true && res7 == true  &&  res8 == false &&
           res9 == true  &&  res10 == true  &&  res11 == true  &&  res12 == true &&
           res13 == true  &&  res14 == true  &&  res15 == true  &&  res16 == true &&
           res17 == true  &&  res18 == true  &&  res19 == true  &&  res20 == true &&
           res21 == true;
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


    bool res1 = wc.unionPlayerToTeam(1, teamNode11);
    //team11 played 5 games tot
    player1->setCalcTotalGamesPlayed(5);
    bool res2 = wc.unionPlayerToTeam(2, teamNode11);

    bool res3 = wc.unionPlayerToTeam(3, teamNode12);
    //team12 played 7 games tot
    player3->setCalcTotalGamesPlayed(7);

    StatusType res4 = wc.buy_team(11, 12);

    bool res13 = (teamNode11->getKey().getNumPlayers() == 3);
    bool res14 = (teamNode11->getKey().getNumGoalKeepers() == 2);
    bool res15 = (teamNode11->getKey().getTeamAbility() == 13);

    bool res16 = (player2->getCalcTotalGamesPlayed() == -5);
    bool res17 = (player3->getCalcTotalGamesPlayed() == 2);

    //the unite team played 4 more games together (not suppose to affect)
    player1->setCalcTotalGamesPlayed(9);
    bool res18 = (player1->getCalcTotalGamesPlayed() == 9);
    bool res19 = (player2->getCalcTotalGamesPlayed() == -5);
    bool res20 = (player3->getCalcTotalGamesPlayed() == 2);

    //team12 not exist
    bool res5 = wc.m_teamTree->find(TeamData(12));


    bool res6 = wc.unionPlayerToTeam(4, teamNode13);
    bool res7 = wc.unionPlayerToTeam(5, teamNode13);

    //team13 played 4 games
    player4->setCalcTotalGamesPlayed(4);
    bool res21 = (player4->getCalcTotalGamesPlayed() == 4);
    bool res22 = (player5->getCalcTotalGamesPlayed() == 0);

    bool res8 = wc.unionPlayerToTeam(6, teamNode13);
    bool res9 = wc.unionPlayerToTeam(7, teamNode13);

    bool res23 = (player6->getCalcTotalGamesPlayed() == -4);
    bool res24 = (player7->getCalcTotalGamesPlayed() == -4);

    //team13 played 6 more games, 10 in total
    player4->setCalcTotalGamesPlayed(10);
    bool res25 = (player4->getCalcTotalGamesPlayed() == 10);
    bool res26 = (player5->getCalcTotalGamesPlayed() == 0);
    bool res27 = (player6->getCalcTotalGamesPlayed() == -4);
    bool res28 = (player7->getCalcTotalGamesPlayed() == -4);


    StatusType res10 = wc.buy_team(13, 11);



    //team11 not exist
    bool res11 = wc.m_teamTree->find(TeamData(11));

    bool res29 = (player4->getCalcTotalGamesPlayed() == 10);
    bool res30 = (player5->getCalcTotalGamesPlayed() == 0);
    bool res31 = (player6->getCalcTotalGamesPlayed() == -4);
    bool res32 = (player7->getCalcTotalGamesPlayed() == -4);
    bool res33 = (player1->getCalcTotalGamesPlayed() == -1);
    bool res34 = (player2->getCalcTotalGamesPlayed() == -5);
    bool res35 = (player3->getCalcTotalGamesPlayed() == 2);


    return res1 == true  &&  res2 == true  &&  res3 == true  &&  res4 == StatusType::SUCCESS  &&  res5 == false  &&
           res6 == true  &&  res7 == true  &&  res8 == true  &&  res9 == true  &&  res10 == StatusType::SUCCESS &&
           res11 == false &&
           res13 == true  &&  res14 == true  &&  res15 == true  &&  res16 == true &&
           res17 == true  &&  res18 == true  &&  res19 == true  &&  res20 == true &&
           res21 == true  &&  res22 == true  &&  res23 == true  &&  res24 == true &&
           res25 == true  &&  res26 == true  &&  res27 == true  &&  res28 == true &&
           res29 == true  &&  res30 == true  &&  res31 == true  &&  res32 == true &&
           res33 == true  &&  res34 == true  &&  res35 == true;
}



bool test_union_bought_team_is_bigger() {
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


    bool res1 = wc.unionPlayerToTeam(1, teamNode11);
    //team11 played 5 games tot
    player1->setCalcTotalGamesPlayed(5);
    bool res2 = wc.unionPlayerToTeam(2, teamNode11);

    bool res3 = wc.unionPlayerToTeam(3, teamNode12);
    //team12 played 7 games tot
    player3->setCalcTotalGamesPlayed(7);

    StatusType res4 = wc.buy_team(12, 11);

    bool res13 = (teamNode11->getKey().getNumPlayers() == 3);
    bool res14 = (teamNode11->getKey().getNumGoalKeepers() == 2);
    bool res15 = (teamNode11->getKey().getTeamAbility() == 13);

    bool res16 = (player2->getCalcTotalGamesPlayed() == -5);
    bool res17 = (player3->getCalcTotalGamesPlayed() == 2);

    //the unite team played 4 more games together (not suppose to affect)
    player1->setCalcTotalGamesPlayed(9);
    bool res18 = (player1->getCalcTotalGamesPlayed() == 9);
    bool res19 = (player2->getCalcTotalGamesPlayed() == -5);
    bool res20 = (player3->getCalcTotalGamesPlayed() == 2);

    //team12 not exist
    bool res5 = wc.m_teamTree->find(TeamData(12));


    bool res6 = wc.unionPlayerToTeam(4, teamNode13);
    bool res7 = wc.unionPlayerToTeam(5, teamNode13);

    //team13 played 4 games
    player4->setCalcTotalGamesPlayed(4);
    bool res21 = (player4->getCalcTotalGamesPlayed() == 4);
    bool res22 = (player5->getCalcTotalGamesPlayed() == 0);

    bool res8 = wc.unionPlayerToTeam(6, teamNode13);
    bool res9 = wc.unionPlayerToTeam(7, teamNode13);

    bool res23 = (player6->getCalcTotalGamesPlayed() == -4);
    bool res24 = (player7->getCalcTotalGamesPlayed() == -4);

    //team13 played 6 more games, 10 in total
    player4->setCalcTotalGamesPlayed(10);
    bool res25 = (player4->getCalcTotalGamesPlayed() == 10);
    bool res26 = (player5->getCalcTotalGamesPlayed() == 0);
    bool res27 = (player6->getCalcTotalGamesPlayed() == -4);
    bool res28 = (player7->getCalcTotalGamesPlayed() == -4);


    StatusType res10 = wc.buy_team(11, 13);

    //team11 not exist
    bool res11 = wc.m_teamTree->find(TeamData(11));

    bool res29 = (player4->getCalcTotalGamesPlayed() == 10);
    bool res30 = (player5->getCalcTotalGamesPlayed() == 0);
    bool res31 = (player6->getCalcTotalGamesPlayed() == -4);
    bool res32 = (player7->getCalcTotalGamesPlayed() == -4);
    bool res33 = (player1->getCalcTotalGamesPlayed() == -1);
    bool res34 = (player2->getCalcTotalGamesPlayed() == -5);
    bool res35 = (player3->getCalcTotalGamesPlayed() == 2);


    return res1 == true  &&  res2 == true  &&  res3 == true  &&  res4 == StatusType::SUCCESS  &&  res5 == false  &&
           res6 == true  &&  res7 == true  &&  res8 == true  &&  res9 == true  &&  res10 == StatusType::SUCCESS &&
           res11 == false &&
           res13 == true  &&  res14 == true  &&  res15 == true  &&  res16 == true &&
           res17 == true  &&  res18 == true  &&  res19 == true  &&  res20 == true &&
           res21 == true  &&  res22 == true  &&  res23 == true  &&  res24 == true &&
           res25 == true  &&  res26 == true  &&  res27 == true  &&  res28 == true &&
           res29 == true  &&  res30 == true  &&  res31 == true  &&  res32 == true &&
           res33 == true  &&  res34 == true  &&  res35 == true;
}


bool test_union_empty_teams() {
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

    wc.m_hashTable->insert(player1);
    wc.m_hashTable->insert(player2);
    wc.m_hashTable->insert(player3);
    wc.m_hashTable->insert(player4);


    Node<TeamData>* teamNode11 = wc.findTeamInTeamTree(11, wc.m_teamTree->getRoot());

    StatusType res1 = wc.buy_team(11, 12);

    bool res2 = (teamNode11->getKey().getNumPlayers() == 0);
    bool res3 = (teamNode11->getKey().getNumGoalKeepers() == 0);
    bool res4 = (teamNode11->getKey().getTeamAbility() == 0);
    bool res5 = (teamNode11->getKey().getTeamID() == 11);

    Node<TeamData>* res6 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());

    return res1 == StatusType::SUCCESS  &&  res2 == true  &&  res3 == true  &&  res4 == true  &&  res5 == true &&
            res6 == nullptr;
}


bool test_union_buyer_team_is_empty() {
    world_cup_t wc;

    TeamData team1(11);
    TeamData team2(12);
    TeamData team3(13);

    wc.m_teamTree->insert(team1);
    wc.m_teamTree->insert(team2);
    wc.m_teamTree->insert(team3);

    PlayerData *player1 = new PlayerData(1, permutation_t::neutral(), 3, 4, 5, true);
    PlayerData *player2 = new PlayerData(2, permutation_t::neutral(), 5, 7, 2, false);
    PlayerData *player3 = new PlayerData(3, permutation_t::neutral(), 1, 2, 2, true);
    PlayerData *player4 = new PlayerData(4, permutation_t::neutral(), 8, 5, 7, false);

    wc.m_hashTable->insert(player1);
    wc.m_hashTable->insert(player2);
    wc.m_hashTable->insert(player3);
    wc.m_hashTable->insert(player4);

    Node<TeamData> *teamNode11 = wc.findTeamInTeamTree(11, wc.m_teamTree->getRoot());
    Node<TeamData> *teamNode12 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());

    bool res1 = wc.unionPlayerToTeam(1, teamNode12);
    bool res2 = wc.unionPlayerToTeam(2, teamNode12);
    bool res3 = wc.unionPlayerToTeam(3, teamNode12);
    bool res4 = wc.unionPlayerToTeam(4, teamNode12);

    StatusType res5 = wc.buy_team(11, 12);

    bool res6 = (teamNode11->getKey().getNumPlayers() == 4);
    bool res7 = (teamNode11->getKey().getNumGoalKeepers() == 2);
    bool res8 = (teamNode11->getKey().getTeamAbility() == 18);
    bool res9 = (teamNode11->getKey().getTeamID() == 11);

    Node<TeamData>* res10 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());

    bool res11 = (teamNode11->getKey().getPtrPlayerReverseRoot() == player1);
    bool res12 = (player1->getPtrTeam() == teamNode11);

    return res1 == true  &&  res2 == true  &&  res3 == true  &&  res4 == true  &&  res5 == StatusType::SUCCESS &&
           res6 == true  &&  res7 == true  &&  res8 == true  &&  res9 == true  && res10 == nullptr  &&
           res11 == true  && res12 == true;

}



bool test_union_bought_team_is_empty() {
    world_cup_t wc;

    TeamData team1(11);
    TeamData team2(12);
    TeamData team3(13);

    wc.m_teamTree->insert(team1);
    wc.m_teamTree->insert(team2);
    wc.m_teamTree->insert(team3);

    PlayerData *player1 = new PlayerData(1, permutation_t::neutral(), 3, 4, 5, true);
    PlayerData *player2 = new PlayerData(2, permutation_t::neutral(), 5, 7, 2, false);
    PlayerData *player3 = new PlayerData(3, permutation_t::neutral(), 1, 2, 2, true);
    PlayerData *player4 = new PlayerData(4, permutation_t::neutral(), 8, 5, 7, false);

    wc.m_hashTable->insert(player1);
    wc.m_hashTable->insert(player2);
    wc.m_hashTable->insert(player3);
    wc.m_hashTable->insert(player4);

    Node<TeamData> *teamNode11 = wc.findTeamInTeamTree(11, wc.m_teamTree->getRoot());
    Node<TeamData> *teamNode12 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());

    bool res1 = wc.unionPlayerToTeam(1, teamNode11);
    bool res2 = wc.unionPlayerToTeam(2, teamNode11);
    bool res3 = wc.unionPlayerToTeam(3, teamNode11);
    bool res4 = wc.unionPlayerToTeam(4, teamNode11);

    StatusType res5 = wc.buy_team(11, 12);

    bool res6 = (teamNode11->getKey().getNumPlayers() == 4);
    bool res7 = (teamNode11->getKey().getNumGoalKeepers() == 2);
    bool res8 = (teamNode11->getKey().getTeamAbility() == 18);
    bool res9 = (teamNode11->getKey().getTeamID() == 11);

    Node<TeamData>* res10 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());

    bool res11 = (teamNode11->getKey().getPtrPlayerReverseRoot() == player1);
    bool res12 = (player1->getPtrTeam() == teamNode11);

    return res1 == true  &&  res2 == true  &&  res3 == true  &&  res4 == true  &&  res5 == StatusType::SUCCESS &&
           res6 == true  &&  res7 == true  &&  res8 == true  &&  res9 == true  && res10 == nullptr  &&
           res11 == true  && res12 == true;

}






/*bool test_complex_union() {
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
};*/




bool test_find_basic() {
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

    bool res1 = wc.unionPlayerToTeam(1, teamNode11);
    //team11 played 5 games tot
    player1->setCalcTotalGamesPlayed(5);
    bool res2 = wc.unionPlayerToTeam(2, teamNode11);

    bool res3 = wc.unionPlayerToTeam(3, teamNode12);
    //team12 played 7 games tot
    player3->setCalcTotalGamesPlayed(7);

    StatusType res4 = wc.buy_team(11, 12);

    bool res13 = (teamNode11->getKey().getNumPlayers() == 3);
    bool res14 = (teamNode11->getKey().getNumGoalKeepers() == 2);
    bool res15 = (teamNode11->getKey().getTeamAbility() == 13);

    bool res16 = (player2->getCalcTotalGamesPlayed() == -5);
    bool res17 = (player3->getCalcTotalGamesPlayed() == 2);

    //the unite team played 4 more games together (not suppose to affect)
    player1->setCalcTotalGamesPlayed(9);
    bool res18 = (player1->getCalcTotalGamesPlayed() == 9);
    bool res19 = (player2->getCalcTotalGamesPlayed() == -5);
    bool res20 = (player3->getCalcTotalGamesPlayed() == 2);

    //team12 not exist
    bool res5 = wc.m_teamTree->find(TeamData(12));


    bool res6 = wc.unionPlayerToTeam(4, teamNode13);
    bool res7 = wc.unionPlayerToTeam(5, teamNode13);

    //team13 played 4 games
    player4->setCalcTotalGamesPlayed(4);
    bool res21 = (player4->getCalcTotalGamesPlayed() == 4);
    bool res22 = (player5->getCalcTotalGamesPlayed() == 0);

    bool res8 = wc.unionPlayerToTeam(6, teamNode13);
    bool res9 = wc.unionPlayerToTeam(7, teamNode13);

    bool res23 = (player6->getCalcTotalGamesPlayed() == -4);
    bool res24 = (player7->getCalcTotalGamesPlayed() == -4);

    //team13 played 6 more games, 10 in total
    player4->setCalcTotalGamesPlayed(10);
    bool res25 = (player4->getCalcTotalGamesPlayed() == 10);
    bool res26 = (player5->getCalcTotalGamesPlayed() == 0);
    bool res27 = (player6->getCalcTotalGamesPlayed() == -4);
    bool res28 = (player7->getCalcTotalGamesPlayed() == -4);

    StatusType res10 = wc.buy_team(13, 11);

    //team11 not exist
    bool res11 = wc.m_teamTree->find(TeamData(11));

    bool res29 = (player4->getCalcTotalGamesPlayed() == 10);
    bool res30 = (player5->getCalcTotalGamesPlayed() == 0);
    bool res31 = (player6->getCalcTotalGamesPlayed() == -4);
    bool res32 = (player7->getCalcTotalGamesPlayed() == -4);
    bool res33 = (player1->getCalcTotalGamesPlayed() == -1);
    bool res34 = (player2->getCalcTotalGamesPlayed() == -5);
    bool res35 = (player3->getCalcTotalGamesPlayed() == 2);

    bool res12 = wc.findTeam(player2);

    bool res36 = (player4->getCalcTotalGamesPlayed() == 10);
    bool res37 = (player5->getCalcTotalGamesPlayed() == 0);
    bool res38 = (player6->getCalcTotalGamesPlayed() == -4);
    bool res39 = (player7->getCalcTotalGamesPlayed() == -4);
    bool res40 = (player1->getCalcTotalGamesPlayed() == -1);
    bool res41 = (player2->getCalcTotalGamesPlayed() == -6);
    bool res42 = (player3->getCalcTotalGamesPlayed() == 2);

    bool res43 = wc.findTeam(player3);

    bool res44 = (player1->getCalcTotalGamesPlayed() == -1);
    bool res45 = (player2->getCalcTotalGamesPlayed() == -6);
    bool res46 = (player3->getCalcTotalGamesPlayed() == 1);


    return res1 == true  &&  res2 == true  &&  res3 == true  &&  res4 == StatusType::SUCCESS  &&  res5 == false  &&
           res6 == true  &&  res7 == true  &&  res8 == true  &&  res9 == true  &&  res10 == StatusType::SUCCESS &&
           res11 == false &&  res12 == true &&
           res13 == true  &&  res14 == true  &&  res15 == true  &&  res16 == true &&
           res17 == true  &&  res18 == true  &&  res19 == true  &&  res20 == true &&
           res21 == true  &&  res22 == true  &&  res23 == true  &&  res24 == true &&
           res25 == true  &&  res26 == true  &&  res27 == true  &&  res28 == true &&
           res29 == true  &&  res30 == true  &&  res31 == true  &&  res32 == true &&
           res33 == true  &&  res34 == true  &&  res35 == true &&
           res36 == true  &&  res37 == true  &&  res38 == true  &&  res39 == true &&
           res40 == true  &&  res41 == true  &&  res42 == true  &&  res43 == true &&
           res44 == true  &&  res45 == true  &&  res46 == true;

}



bool test_find_root() {
    world_cup_t wc;

    TeamData team1(11);
    TeamData team2(12);
    TeamData team3(13);

    wc.m_teamTree->insert(team1);
    wc.m_teamTree->insert(team2);
    wc.m_teamTree->insert(team3);

    PlayerData *player1 = new PlayerData(1, permutation_t::neutral(), 3, 4, 5, true);
    PlayerData *player2 = new PlayerData(2, permutation_t::neutral(), 5, 7, 2, false);
    PlayerData *player3 = new PlayerData(3, permutation_t::neutral(), 1, 2, 2, true);
    PlayerData *player4 = new PlayerData(4, permutation_t::neutral(), 8, 5, 7, false);

    wc.m_hashTable->insert(player1);
    wc.m_hashTable->insert(player2);
    wc.m_hashTable->insert(player3);
    wc.m_hashTable->insert(player4);

    Node<TeamData> *teamNode11 = wc.findTeamInTeamTree(11, wc.m_teamTree->getRoot());
    Node<TeamData> *teamNode12 = wc.findTeamInTeamTree(12, wc.m_teamTree->getRoot());
    Node<TeamData> *teamNode13 = wc.findTeamInTeamTree(13, wc.m_teamTree->getRoot());

    bool res1 = wc.unionPlayerToTeam(1, teamNode12);
    bool res2 = wc.unionPlayerToTeam(2, teamNode12);

    //team12 played 6 games
    player1->setCalcTotalGamesPlayed(6);

    bool res3 = wc.unionPlayerToTeam(3, teamNode12);
    bool res4 = wc.unionPlayerToTeam(4, teamNode12);

    bool res5 = wc.findTeam(player1);

    bool res6 = (player1->getCalcTotalGamesPlayed() == 6);
    bool res7 = (player2->getCalcTotalGamesPlayed() == 0);
    bool res8 = (player3->getCalcTotalGamesPlayed() == -6);
    bool res9 = (player4->getCalcTotalGamesPlayed() == -6);

    return res1 == true  &&  res2 == true  &&  res3 == true  &&  res4 == true  &&  res5 == true  &&
           res6 == true  &&  res7 == true  &&  res8 == true  &&  res9 == true ;
}


bool test_find_nullptr() {
    world_cup_t wc;
    return !wc.findTeam(nullptr);
}




int main(){
    RUN_TEST(test_union_player_to_empty_team);
    RUN_TEST(test_union_player_to_team);
    RUN_TEST(test_union_buyer_team_is_bigger);
    RUN_TEST(test_union_bought_team_is_bigger);
    RUN_TEST(test_union_empty_teams);
    RUN_TEST(test_union_buyer_team_is_empty);
    RUN_TEST(test_union_bought_team_is_empty);
    RUN_TEST(test_find_basic);
    RUN_TEST(test_find_root);
    //RUN_TEST(test_find_nullptr);
    return 0;
}

