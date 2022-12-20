#ifndef DATA_STRUCTURES_EX2_HASHPLAYERDATA_H
#define DATA_STRUCTURES_EX2_HASHPLAYERDATA_H

#include "UnionFindData.h"

class HashPlayerData {
public:
    HashPlayerData(int playerID, PlayerData* ptrPlayerUFNode);
    HashPlayerData(const HashPlayerData& otherData) = default;
    HashPlayerData& operator=(const HashPlayerData& otherData) = default;
    ~HashPlayerData() = default;

    int getID() const;
    PlayerData* getPtr() const;


private:
    int m_playerID;
    // pointer to player's pointer in the reversed tree
    PlayerData* m_ptrPlayerUFNode;
};


#endif //DATA_STRUCTURES_EX2_HASHPLAYERDATA_H
