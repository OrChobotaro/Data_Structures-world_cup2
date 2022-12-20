
#include "RankTree.h"
#include <stdio.h>


int main(){
    RankTree rankTree;
    AbilityDataTeam player1(1, 13);
    AbilityDataTeam player2(2, 18);
    AbilityDataTeam player3(3, 11);
    AbilityDataTeam player4(4, 27);
    AbilityDataTeam player5(5, 15);
    AbilityDataTeam player6(6, 34);
    AbilityDataTeam player7(7, 40);
    AbilityDataTeam player8(8, 16);
    AbilityDataTeam player9(9, 17);
    AbilityDataTeam player10(10, 10);

    rankTree.insert(player1);
    rankTree.insert(player2);
    rankTree.insert(player3);
    rankTree.insert(player4);
    rankTree.insert(player5);
    rankTree.insert(player6);
    rankTree.insert(player7);
    rankTree.insert(player8);
    rankTree.insert(player9);
    rankTree.insert(player10);

    Node<AbilityDataTeam>* node = rankTree.findIndex(10);
    if (node) {
        std::cout << node->getKey().getTeamID() << std::endl;
        std::cout << node->getKey().getTeamAbility() << std::endl;
    }
    else {
        std::cout << "index not valid" << std::endl;
    }

    return 0;
}
