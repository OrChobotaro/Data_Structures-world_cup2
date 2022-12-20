#ifndef DATA_STRUCTURES_EX1_LINKEDLIST_H
#define DATA_STRUCTURES_EX1_LINKEDLIST_H

#include "LinkedListNode.h"
#include "wet2util.h"


template<class T>
class LinkedList{
public:

    LinkedList();

    LinkedList(const T& nullParam);

    LinkedList(const LinkedList<T>& otherList) = default;
    LinkedList<T>& operator=(const LinkedList& otherList) = default;

    LinkedListNode<T>* getStart();
    LinkedListNode<T>* getEnd();

    void setStart(LinkedListNode<T>* node) ;
    void setEnd(LinkedListNode<T>* node) ;

    LinkedListNode<T>* newLinkedListNode(const T& data);

    StatusType insertBefore(LinkedListNode<T> *nodeToInsertBefore, LinkedListNode<T>* nodeToInsert);
    StatusType insertAfter(LinkedListNode<T> *nodeToInsertAfter, LinkedListNode<T>* nodeToInsert);
    StatusType deleteNode(LinkedListNode<T>* nodeToRemove);

//    StatusType uniteListsNew(LinkedList<T>* List2, LinkedList<T>* newList);
    void clearList(LinkedListNode<T>* start, LinkedListNode<T>* end);
    void clearList();

    int countNodes();
    ~LinkedList();


private:
    LinkedListNode<T>* m_start;
    LinkedListNode<T>* m_end;

};

template<class T>
int LinkedList<T>::countNodes(){
    LinkedListNode<T>* node = this->m_start->getNext();
    int counter = 0;
    while(node->getNext()){
        counter++;
        node = node->getNext();
    }
    return counter;
}

template<class T>
StatusType uniteLists(LinkedListNode<T>* startList1, LinkedListNode<T>* startList2,
                      LinkedListNode<T>* newStart, LinkedListNode<T>* newEnd);


template<class T>
LinkedList<T>::LinkedList() {
    m_start = nullptr;
    m_end = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(const T& nullParam) {
    m_start = newLinkedListNode(nullParam);
    m_end = newLinkedListNode(nullParam);

    m_start->setNext(m_end);
    m_end->setPrevious(m_start);
}

//template<class T>
//LinkedList<T>& LinkedList<T>::operator=(const LinkedList& otherList){
//    m_start = otherList.m_start;
//    m_end = otherList.m_end;
//}

template<class T>
LinkedList<T>::~LinkedList() {
    clearList();
}

template<class T>
LinkedListNode<T>* LinkedList<T>::getStart() {
    return m_start;
}

template<class T>
LinkedListNode<T>* LinkedList<T>::getEnd() {
    return m_end;
}

template<class T>
void LinkedList<T>::setStart(LinkedListNode<T>* node) {
    m_start = node;
}

template<class T>
void LinkedList<T>::setEnd(LinkedListNode<T>* node) {
    m_end = node;
}


template<class T>
LinkedListNode<T>* LinkedList<T>::newLinkedListNode(const T& data){
    return new LinkedListNode<T>(data);
}


template<class T>
void LinkedList<T>::clearList(LinkedListNode<T>* start, LinkedListNode<T>* end){
    LinkedListNode<T>* temp;
    while (start != end){
        temp = start;
        start = start->getNext();
        delete temp;
    }
    delete start;
}


template<class T>
void LinkedList<T>::clearList(){
    if(m_start != nullptr || m_end != nullptr){
        LinkedListNode<T>* temp;
        LinkedListNode<T>* start = m_start;
        LinkedListNode<T>* end = m_end;
        while (start != end){
            temp = start;
            start = start->getNext();
            delete temp;
        }
        delete start;
        this->m_start = nullptr;
        this->m_end = nullptr;
    }
}


template<class T>
StatusType LinkedList<T>::insertBefore(LinkedListNode<T> *nodeToInsertBefore, LinkedListNode<T>* nodeToInsert) {
    //assert(node);
    //assert(data);
    //assert(ptrSave);

    LinkedListNode<T>* previousNode = nodeToInsertBefore->getPrevious();
//    LinkedListNode<T>* newNodeMiddle;

//    try{
//        newNodeMiddle = newLinkedListNode(data);
//    }
//    catch (std::bad_alloc& e){
//        return StatusType::ALLOCATION_ERROR;
//    }

    previousNode->setNext(nodeToInsert);
    nodeToInsert->setPrevious(previousNode);
    nodeToInsert->setNext(nodeToInsertBefore);
    nodeToInsertBefore->setPrevious(nodeToInsert);

//    *ptrSave = newNodeMiddle;

    return StatusType::SUCCESS;
}

template<class T>
StatusType LinkedList<T>::insertAfter(LinkedListNode<T> *nodeToInsertAfter, LinkedListNode<T>* nodeToInsert) {

    //assert(node);
    //assert(data);
    //assert(ptrSave);


    LinkedListNode<T>* nextNode = nodeToInsertAfter->getNext();
//    LinkedListNode<T>* newNodeMiddle;
//    try{
//        newNodeMiddle = newLinkedListNode(data);
//
//    } catch (std::bad_alloc& e){
//        return StatusType::ALLOCATION_ERROR;
//    }

    nodeToInsertAfter->setNext(nodeToInsert);
    nodeToInsert->setPrevious(nodeToInsertAfter);
    nodeToInsert->setNext(nextNode);
    nextNode->setPrevious(nodeToInsert);

//    *ptrSave = newNodeMiddle;

    return StatusType::SUCCESS;
}

template<class T>
StatusType LinkedList<T>::deleteNode(LinkedListNode<T>* nodeToRemove){
    assert(nodeToRemove);

    if(!nodeToRemove){
        // check what to return if fails
        return StatusType::FAILURE;
    }

    LinkedListNode<T>* prevNode = nodeToRemove->getPrevious();
    LinkedListNode<T>* nextNode = nodeToRemove->getNext();


    prevNode->setNext(nextNode);
    nextNode->setPrevious(prevNode);

    nodeToRemove->setNext(nullptr);
    nodeToRemove->setPrevious(nullptr);

    delete nodeToRemove;

    return StatusType::SUCCESS;

}


template<class T>
StatusType uniteLists(LinkedListNode<T>* startList1, LinkedListNode<T>* startList2,
                      LinkedListNode<T>* newStart, LinkedListNode<T>* newEnd){
    assert(startList1);
    assert(startList2);
    assert(newStart);
    assert(newEnd);

    if(!newStart || !newEnd){
        return StatusType::FAILURE;
    }


    LinkedListNode<T>* currNode1 = startList1->getNext();
    LinkedListNode<T>* currNode2 = startList2->getNext();
    LinkedListNode<T>* currNewNode = newStart;

    startList1->setNext(nullptr);
    startList2->setNext(nullptr);


    while(currNode1->getNext() && currNode2->getNext()){
        if(currNode1->getData() < currNode2->getData()){
            currNewNode->setNext(currNode1);
            currNode1->setPrevious(currNewNode);
            currNewNode = currNewNode->getNext();
            currNode1 = currNode1->getNext();

        }
        else{
            currNewNode->setNext(currNode2);
            currNode2->setPrevious(currNewNode);
            currNewNode = currNewNode->getNext();
            currNode2 = currNode2->getNext();
        }
    }

    if(currNode1->getNext()){
        while(currNode1->getNext()){
            currNewNode->setNext(currNode1);
            currNewNode = currNewNode->getNext();
            currNode1 = currNode1->getNext();
        }


    }
    else if(currNode2->getNext()){
        while(currNode2->getNext()){
            currNewNode->setNext(currNode2);
            currNewNode = currNewNode->getNext();
            currNode2 = currNode2->getNext();
        }
    }


    startList1->setNext(currNode1);
    LinkedListNode<T>* endNode1 = currNode1;
    endNode1->setPrevious(startList1);

    LinkedListNode<T>* endNode2 = currNode2;
    startList2->setNext(endNode2);
    endNode2->setPrevious(startList2);

    currNewNode->setNext(newEnd);
    newEnd->setPrevious(currNewNode);


    return StatusType::SUCCESS;

}






#endif //DATA_STRUCTURES_EX1_LINKEDLIST_H
