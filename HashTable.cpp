#include "HashTable.h"

HashTable::HashTable(int size): m_arrLength(size), m_capacity(0){

    // allocate initial arr
    m_arr = new LinkedList<HashPlayerData>*[size];

    // init array
    for(int i=0; i<size; i++){
        m_arr[i] = nullptr;
    }
}


