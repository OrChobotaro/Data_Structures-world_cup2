#include "HashPlayerData.h"

HashPlayerData::HashPlayerData(int playerID, PlayerData* ptrPlayerUFNode) : m_playerID(playerID), m_ptrPlayerUFNode(ptrPlayerUFNode){}


int HashPlayerData::getID() const {
    return m_playerID;
}


PlayerData* HashPlayerData::getPtr() const{
    return m_ptrPlayerUFNode;
}
