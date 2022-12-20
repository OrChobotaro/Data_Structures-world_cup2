#include <iostream>
#include "wet2util.h"
#include "hashTable.h"
#include "RankTree.h"


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



bool test_insert_RR() {
    RankTree rankTree;
    for (int i=1; i < 6; i++) {
        rankTree.insert(AbilityDataTeam(i, i));
    }
    return rankTree.getRoot()->getKey().getTotalNodesInSubTrees() == 5 &&
            rankTree.getRoot()->getRight()->getKey().getTotalNodesInSubTrees() == 3 &&
            rankTree.getRoot()->getRight()->getRight()->getKey().getTotalNodesInSubTrees() == 1 &&
            rankTree.getRoot()->getRight()->getLeft()->getKey().getTotalNodesInSubTrees() == 1 &&
            rankTree.getRoot()->getLeft()->getKey().getTotalNodesInSubTrees() == 1;
}


bool test_insert_LL() {
    RankTree rankTree;
    for (int i=5; i > 0; i--) {
        rankTree.insert(AbilityDataTeam(i, i));
    }
    return rankTree.getRoot()->getKey().getTotalNodesInSubTrees() == 5 &&
           rankTree.getRoot()->getLeft()->getKey().getTotalNodesInSubTrees() == 3 &&
           rankTree.getRoot()->getLeft()->getLeft()->getKey().getTotalNodesInSubTrees() == 1 &&
           rankTree.getRoot()->getLeft()->getRight()->getKey().getTotalNodesInSubTrees() == 1 &&
           rankTree.getRoot()->getRight()->getKey().getTotalNodesInSubTrees() == 1;
}


bool test_insert_Many_Nodes() {
    RankTree rankTree;
    for (int i=1; i<101; i++) {
        rankTree.insert(AbilityDataTeam(i, i));
    }
    return rankTree.getRoot()->getKey().getTotalNodesInSubTrees() == 100;
}


bool test_insert_incorrect_AbilityDataTeam() {
    RankTree rankTree;
    for (int i = 1; i < 15; i++) {
        rankTree.insert(AbilityDataTeam(i, i));
    }
    AbilityDataTeam Team15(-1, -1);
    Team15.setTotalNodesInSubTrees(-1);
    rankTree.insert(Team15);
    return rankTree.getRoot()->getKey().getTotalNodesInSubTrees() == 15;
}


bool test_insert_same_ability() {
    RankTree rankTree;
    for (int i = 1; i < 15; i++) {
        rankTree.insert(AbilityDataTeam(i, i));
    }
    AbilityDataTeam Team15(15, 15);
    Team15.setTotalNodesInSubTrees(-1);
    rankTree.insert(Team15);
    rankTree.insert(Team15);
    return rankTree.getRoot()->getKey().getTotalNodesInSubTrees() == 15;
}



bool test_insert_in_different_order() {
    RankTree rankTree;
    AbilityDataTeam Team1(1, 13);
    AbilityDataTeam Team2(2, 18);
    AbilityDataTeam Team3(3, 11);
    AbilityDataTeam Team4(4, 27);
    AbilityDataTeam Team5(5, 15);
    AbilityDataTeam Team6(6, 34);
    AbilityDataTeam Team7(7, 40);
    AbilityDataTeam Team8(8, 16);
    AbilityDataTeam Team9(9, 17);
    AbilityDataTeam Team10(10, 10);

    rankTree.insert(Team1);
    rankTree.insert(Team2);
    rankTree.insert(Team3);
    rankTree.insert(Team4);
    rankTree.insert(Team5);
    rankTree.insert(Team6);
    rankTree.insert(Team7);
    rankTree.insert(Team8);
    rankTree.insert(Team9);
    rankTree.insert(Team10);

    return rankTree.getRoot()->getRight()->getRight()->getKey().getTotalNodesInSubTrees() == 1 &&
            rankTree.getRoot()->getRight()->getKey().getTotalNodesInSubTrees() == 3 &&
            rankTree.getRoot()->getRight()->getLeft()->getKey().getTotalNodesInSubTrees() == 1 &&
            rankTree.getRoot()->getLeft()->getLeft()->getLeft()->getKey().getTotalNodesInSubTrees() == 1 &&
            rankTree.getRoot()->getLeft()->getLeft()->getKey().getTotalNodesInSubTrees() == 2 &&
            rankTree.getRoot()->getLeft()->getKey().getTotalNodesInSubTrees() == 6 &&
            rankTree.getRoot()->getLeft()->getRight()->getLeft()->getKey().getTotalNodesInSubTrees() == 1 &&
            rankTree.getRoot()->getLeft()->getRight()->getRight()->getKey().getTotalNodesInSubTrees() == 1 &&
            rankTree.getRoot()->getLeft()->getRight()->getKey().getTotalNodesInSubTrees() == 3 &&
            rankTree.getRoot()->getKey().getTotalNodesInSubTrees() == 10;
}


bool test_basic_find1() {
    RankTree rankTree;
    AbilityDataTeam Team1(1, 13);
    AbilityDataTeam Team2(2, 18);
    AbilityDataTeam Team3(3, 11);
    AbilityDataTeam Team4(4, 27);
    AbilityDataTeam Team5(5, 15);
    AbilityDataTeam Team6(6, 34);
    AbilityDataTeam Team7(7, 40);
    AbilityDataTeam Team8(8, 16);
    AbilityDataTeam Team9(9, 17);
    AbilityDataTeam Team10(10, 10);

    rankTree.insert(Team1);
    rankTree.insert(Team2);
    rankTree.insert(Team3);
    rankTree.insert(Team4);
    rankTree.insert(Team5);
    rankTree.insert(Team6);
    rankTree.insert(Team7);
    rankTree.insert(Team8);
    rankTree.insert(Team9);
    rankTree.insert(Team10);
    
    Node<AbilityDataTeam>* Find_0 = rankTree.findIndex(0);
    Node<AbilityDataTeam>* Find_1 = rankTree.findIndex(1);
    Node<AbilityDataTeam>* Find_2 = rankTree.findIndex(2);
    Node<AbilityDataTeam>* Find_3 = rankTree.findIndex(3);
    Node<AbilityDataTeam>* Find_4 = rankTree.findIndex(4);
    Node<AbilityDataTeam>* Find_5 = rankTree.findIndex(5);
    Node<AbilityDataTeam>* Find_6 = rankTree.findIndex(6);
    Node<AbilityDataTeam>* Find_7 = rankTree.findIndex(7);
    Node<AbilityDataTeam>* Find_8 = rankTree.findIndex(8);
    Node<AbilityDataTeam>* Find_9 = rankTree.findIndex(9);

    return Find_0->getKey().getTeamAbility() == 10 &&
            Find_1->getKey().getTeamAbility() == 11 &&
            Find_2->getKey().getTeamAbility() == 13 &&
            Find_3->getKey().getTeamAbility() == 15 &&
            Find_4->getKey().getTeamAbility() == 16 &&
            Find_5->getKey().getTeamAbility() == 17 &&
            Find_6->getKey().getTeamAbility() == 18 &&
            Find_7->getKey().getTeamAbility() == 27 &&
            Find_8->getKey().getTeamAbility() == 34 &&
            Find_9->getKey().getTeamAbility() == 40;
}



bool test_basic_find2() {
    RankTree rankTree;
    AbilityDataTeam Team1(1, 50);
    AbilityDataTeam Team2(2, 110);
    AbilityDataTeam Team3(3, 130);
    AbilityDataTeam Team4(4, 95);
    AbilityDataTeam Team5(5, 55);
    AbilityDataTeam Team6(6, 40);
    AbilityDataTeam Team7(7, 180);
    AbilityDataTeam Team8(8, 105);
    AbilityDataTeam Team9(9, 70);
    AbilityDataTeam Team10(10, 81);
    AbilityDataTeam Team11(11, 200);
    AbilityDataTeam Team12(12, 60);
    AbilityDataTeam Team13(13, 100);
    AbilityDataTeam Team14(14, 93);
    AbilityDataTeam Team15(15, 140);
    AbilityDataTeam Team16(16, 80);
    AbilityDataTeam Team17(17, 165);
    AbilityDataTeam Team18(18, 90);

    rankTree.insert(Team1);
    rankTree.insert(Team2);
    rankTree.insert(Team3);
    rankTree.insert(Team4);
    rankTree.insert(Team5);
    rankTree.insert(Team6);
    rankTree.insert(Team7);
    rankTree.insert(Team8);
    rankTree.insert(Team9);
    rankTree.insert(Team10);
    rankTree.insert(Team11);
    rankTree.insert(Team12);
    rankTree.insert(Team13);
    rankTree.insert(Team14);
    rankTree.insert(Team15);
    rankTree.insert(Team16);
    rankTree.insert(Team17);
    rankTree.insert(Team18);

    Node<AbilityDataTeam>* Find_0 = rankTree.findIndex(0);
    Node<AbilityDataTeam>* Find_1 = rankTree.findIndex(1);
    Node<AbilityDataTeam>* Find_2 = rankTree.findIndex(2);
    Node<AbilityDataTeam>* Find_3 = rankTree.findIndex(3);
    Node<AbilityDataTeam>* Find_4 = rankTree.findIndex(4);
    Node<AbilityDataTeam>* Find_5 = rankTree.findIndex(5);
    Node<AbilityDataTeam>* Find_6 = rankTree.findIndex(6);
    Node<AbilityDataTeam>* Find_7 = rankTree.findIndex(7);
    Node<AbilityDataTeam>* Find_8 = rankTree.findIndex(8);
    Node<AbilityDataTeam>* Find_9 = rankTree.findIndex(9);
    Node<AbilityDataTeam>* Find_10 = rankTree.findIndex(10);
    Node<AbilityDataTeam>* Find_11 = rankTree.findIndex(11);
    Node<AbilityDataTeam>* Find_12 = rankTree.findIndex(12);
    Node<AbilityDataTeam>* Find_13 = rankTree.findIndex(13);
    Node<AbilityDataTeam>* Find_14 = rankTree.findIndex(14);
    Node<AbilityDataTeam>* Find_15 = rankTree.findIndex(15);
    Node<AbilityDataTeam>* Find_16 = rankTree.findIndex(16);
    Node<AbilityDataTeam>* Find_17 = rankTree.findIndex(17);
    Node<AbilityDataTeam>* Find_18 = rankTree.findIndex(18);


    return Find_0->getKey().getTeamAbility() == 40 &&
           Find_1->getKey().getTeamAbility() == 50 &&
           Find_2->getKey().getTeamAbility() == 55 &&
           Find_3->getKey().getTeamAbility() == 60 &&
           Find_4->getKey().getTeamAbility() == 70 &&
           Find_5->getKey().getTeamAbility() == 80 &&
           Find_6->getKey().getTeamAbility() == 81 &&
           Find_7->getKey().getTeamAbility() == 90 &&
           Find_8->getKey().getTeamAbility() == 93 &&
           Find_9->getKey().getTeamAbility() == 95 &&
           Find_10->getKey().getTeamAbility() == 100 &&
           Find_11->getKey().getTeamAbility() == 105 &&
           Find_12->getKey().getTeamAbility() == 110 &&
           Find_13->getKey().getTeamAbility() == 130 &&
           Find_14->getKey().getTeamAbility() == 140 &&
           Find_15->getKey().getTeamAbility() == 165 &&
           Find_16->getKey().getTeamAbility() == 180 &&
           Find_17->getKey().getTeamAbility() == 200 &&
           Find_18 == nullptr &&
           rankTree.findIndex(-1) == nullptr;
           ;
}


bool test_find_edge_cases() {
    RankTree rankTree;
    AbilityDataTeam Team1(1, 13);
    AbilityDataTeam Team2(2, 18);
    AbilityDataTeam Team3(3, 11);
    AbilityDataTeam Team4(4, 27);
    AbilityDataTeam Team5(5, 15);
    AbilityDataTeam Team6(6, 34);
    AbilityDataTeam Team7(7, 40);
    AbilityDataTeam Team8(8, 16);
    AbilityDataTeam Team9(9, 17);
    AbilityDataTeam Team10(10, 10);

    rankTree.insert(Team1);
    rankTree.insert(Team2);
    rankTree.insert(Team3);
    rankTree.insert(Team4);
    rankTree.insert(Team5);
    rankTree.insert(Team6);
    rankTree.insert(Team7);
    rankTree.insert(Team8);
    rankTree.insert(Team9);
    rankTree.insert(Team10);

    Node<AbilityDataTeam>* FindLessZero1 = rankTree.findIndex(-1);
    Node<AbilityDataTeam>* FindLessZero2 = rankTree.findIndex(-10);
    Node<AbilityDataTeam>* FindLessZero3 = rankTree.findIndex(-59);
    Node<AbilityDataTeam>* FindBigger1 = rankTree.findIndex(10);
    Node<AbilityDataTeam>* FindBigger2 = rankTree.findIndex(25);
    Node<AbilityDataTeam>* FindBigger3 = rankTree.findIndex(100);

    return !FindLessZero1 && !FindLessZero2 && !FindLessZero3 &&
            !FindBigger1 && !FindBigger2 && !FindBigger3;
}





int main(){
    RUN_TEST(test_insert_RR);
    RUN_TEST(test_insert_LL);
    RUN_TEST(test_insert_Many_Nodes);
    RUN_TEST(test_insert_incorrect_AbilityDataTeam);
    RUN_TEST(test_insert_same_ability);
    RUN_TEST(test_insert_in_different_order);
    RUN_TEST(test_basic_find1);
    RUN_TEST(test_basic_find2);
    RUN_TEST(test_find_edge_cases);
    return 0;
}









