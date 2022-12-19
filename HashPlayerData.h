#ifndef DATA_STRUCTURES_EX2_HASHPLAYERDATA_H
#define DATA_STRUCTURES_EX2_HASHPLAYERDATA_H

#include "UnionFindData.h"

class HashPlayerData {

private:
    int m_playerID;
    // pointer to player's pointer in the reversed tree
    PlayerData* m_ptrPlayerData;
};


#endif //DATA_STRUCTURES_EX2_HASHPLAYERDATA_H
