#ifndef DATA_STRUCTURES_EX2_HASHTABLE_H
#define DATA_STRUCTURES_EX2_HASHTABLE_H

#include "LinkedList.h"
#include "HashPlayerData.h"
#include "UnionFindData.h"

class HashTable {
public:

    HashTable() = delete;
    HashTable(int size);
    HashTable(const HashTable& otherTable) = delete;
    HashTable& operator=(const HashTable& otherTable) = delete;
    ~HashTable();

    void rehash();
    void insert(PlayerData* playerToInsert);
    void rehashAux(std::shared_ptr<LinkedList<HashPlayerData>>* newArr, int newLength);
    void deleteArr(std::shared_ptr<LinkedList<HashPlayerData>>* arr, int size) const;
    PlayerData* find(int playerID);


    std::shared_ptr<LinkedList<HashPlayerData>>* getArr() const;
    int getLength();
    int getCapacity();

    int countPlayers();

private:
    std::shared_ptr<LinkedList<HashPlayerData>>* m_arr;
    int m_arrLength;
    int m_capacity;
    double m_perToRehash;
};












#endif //DATA_STRUCTURES_EX2_HASHTABLE_H
