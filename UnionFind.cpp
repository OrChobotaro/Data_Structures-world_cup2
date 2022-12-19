#include "UnionFind.h"


Node<TeamData>* UnionFind::findTeamAux(PlayerData *player) {
    PlayerData* temp = player;
    PlayerData* reversedRoot = nullptr;
    while (temp->getUp()) {
        reversedRoot = temp;
        temp = temp->getUp();
    }
    temp = player;
    while (temp->getUp()) {
        temp->setUp(reversedRoot);
        temp = temp->getUp();
    }
    return reversedRoot->getPtrTeam();
}