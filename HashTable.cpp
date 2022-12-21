#include "hashTable.h"


HashTable::HashTable(int size): m_arrLength(size), m_capacity(0), m_perToRehash(0.75){

    // allocate initial arr
    m_arr = new std::shared_ptr<LinkedList<HashPlayerData>>[size];

    // init array
    for(int i=0; i<size; i++){
        m_arr[i] = nullptr;
    }
}

HashTable::~HashTable() {
    deleteArr(m_arr, m_arrLength);
}


void HashTable::insert(PlayerData* playerToInsert){  // todo: change func to bool?

    // if existed, don't add

    if(playerToInsert->getPlayerID() <= 0){
        return;
    }

    int id = playerToInsert->getPlayerID();
    int cell = -1;

    // creating Hash data object
    HashPlayerData obj(id, playerToInsert);
    HashPlayerData nullObj(-1, nullptr);

    // creating list node
    LinkedListNode<HashPlayerData>* newNode = new LinkedListNode<HashPlayerData>(obj);

    //applying modulo func to find the right cell
    cell = id % m_arrLength;

    // checks:
    if(m_arr[cell] == nullptr){
        // if list in the cell not exists - create list
        std::shared_ptr<LinkedList<HashPlayerData>> newList(new LinkedList<HashPlayerData>(nullObj));

        m_arr[cell] = newList;
        // adding to capacity counter
        m_capacity++;

    }
    std::shared_ptr<LinkedList<HashPlayerData>> list = m_arr[cell];
    LinkedListNode<HashPlayerData>* startDummy = list->getStart();

    // insert node to the start of the list
    list->insertAfter(startDummy, newNode);
//        LinkedListNode<HashPlayerData>* secondNode = startDummy->getNext();
//        startDummy->setNext(newNode);
//        newNode->setNext(secondNode);
//        secondNode->setPrevious(newNode);
//        newNode->setPrevious(startDummy);

    // check if rehash needed

    if(m_capacity >= m_perToRehash*m_arrLength){
        rehash();
    }

}


void HashTable::deleteArr(std::shared_ptr<LinkedList<HashPlayerData>>* arr, int size) const{
    for(int i=0; i<size; i++){
        if(arr[i] == nullptr){
            continue;
        } else {
            arr[i]->clearList();
        }
    }

    delete[] arr;
}


void HashTable::rehash() {

    int newLength = m_arrLength * 2;

    std::shared_ptr<LinkedList<HashPlayerData>> *newArr;

    // allocating new array and initialize it.
    try{
        newArr = new std::shared_ptr<LinkedList<HashPlayerData>>[newLength];
        for (int i = 0; i < newLength; i++) {
            newArr[i] = nullptr;
        }

        rehashAux(newArr, newLength);
    } catch (std::bad_alloc& e){
        throw;
    }

    std::shared_ptr<LinkedList<HashPlayerData>> *tempArr = m_arr;
    m_arr = newArr;
    deleteArr(tempArr, m_arrLength);
    m_arrLength = newLength;
}

void HashTable::rehashAux(std::shared_ptr<LinkedList<HashPlayerData>> *newArr, int newLength) {
    int newCapacity = 0;
    int newCell = -1;
    int currPlayerId = -1;
    HashPlayerData nullObj(-1, nullptr);

    // iterating on old array
    for (int i = 0; i < m_arrLength; i++) {
        std::shared_ptr<LinkedList<HashPlayerData>> list = m_arr[i];
        if(list == nullptr){
            continue;
        }
        LinkedListNode<HashPlayerData> *temp = list->getStart()->getNext();
        //iterating on list in the i cell
        while (temp != list->getEnd()) {
            // saving next node on the list
            LinkedListNode<HashPlayerData> *nextTemp = temp->getNext();

            // finding the new cell in the bigger array
            currPlayerId = temp->getData().getID();
            newCell = currPlayerId % newLength;

            if (newArr[newCell] == nullptr) {
                // if list in the cell not exists - create list
                try{
                    std::shared_ptr<LinkedList<HashPlayerData>> newList(new LinkedList<HashPlayerData>(nullObj));
                    newArr[newCell] = newList;
                    newCapacity++;
                } catch (std::bad_alloc& e){
                    //todo: reverse all?
                    throw;
                }
            }

            // moving temp to new list
            newArr[newCell]->insertAfter(newArr[newCell]->getStart(), temp);

            temp = nextTemp;
        }
        // connecting start to end for deletion
        list->getStart()->setNext(temp);
        temp->setPrevious(list->getStart());
    }
    m_capacity = newCapacity;
}


int HashTable::countPlayers(){
    int counter = 0;

    for(int i = 0; i < m_arrLength; i++){
        if(m_arr[i] != nullptr){
            counter+=m_arr[i]->countNodes();
        }
    }
    return counter;
}


PlayerData* HashTable::find(int playerID){

    int cell = playerID % m_arrLength;
    std::shared_ptr<LinkedList<HashPlayerData>> list = m_arr[cell];
    if(list == nullptr){
        return nullptr;
    }
    LinkedListNode<HashPlayerData> *temp = list->getStart()->getNext();

    while(temp->getData().getID() != playerID && temp != list->getEnd()){
        temp = temp->getNext();
    }
    if(temp != list->getEnd()){
        return temp->getData().getPtr();
    } else {
        return nullptr;
    }
}


std::shared_ptr<LinkedList<HashPlayerData>>* HashTable::getArr() const{
    return m_arr;
}

int HashTable::getCapacity() {
    return m_capacity;
}

int HashTable::getLength() {
    return m_arrLength;
}
