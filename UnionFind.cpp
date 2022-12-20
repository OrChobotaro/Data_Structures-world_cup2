#include "UnionFind.h"

////// To check in the fatherFunc that player != nullptr
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


/*
PlayerData* UnionFind::makeSet(int playerID, const permutation_t &spirit, int gamesPlayed, int ability, int cards,
                               bool goalKeeper, Node<TeamData> *ptrTeam) {
    PlayerData* newPlayer = new PlayerData(playerID, spirit, gamesPlayed, ability, cards, goalKeeper);
    newPlayer->setPtrTeam(ptrTeam);
    ptrTeam->m_key.setPtrPlayerReverseRoot(newPlayer);
}*/



/*
Node<TeamData>* UnionFind::unionTeamsAux(Node<TeamData> *team1, Node<TeamData> *team2) {
    int numPlayersTeam1 = team1->getKey().getNumPlayers();
    int numPlayersTeam2 = team1->getKey().getNumPlayers();
}*/
