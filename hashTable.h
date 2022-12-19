#ifndef DATA_STRUCTURES_EX2_HASHTABLE_H
#define DATA_STRUCTURES_EX2_HASHTABLE_H

#include "LinkedList.h"
#include "HashPlayerData.h"
#include "UnionFindData.h"

class HashTable {
public:

    HashTable() = delete;
    HashTable(int size);
    HashTable(HashTable& otherTable) = delete;
    HashTable& operator=(HashTable& otherTable) = delete;
    ~HashTable();

    void insert(PlayerData* playerToInsert);
    void rehash();
    void deleteArr(LinkedList<HashPlayerData>** arr);


private:
    LinkedList<HashPlayerData>** m_arr;
    int m_arrLength;
    int m_capacity;
};












#endif //DATA_STRUCTURES_EX2_HASHTABLE_H
