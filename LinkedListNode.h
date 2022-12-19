#ifndef DATA_STRUCTURES_EX1_LINKEDLISTNODE_H
#define DATA_STRUCTURES_EX1_LINKEDLISTNODE_H

#include "Node.h"



template<class T>
class LinkedListNode{
public:

    LinkedListNode() = delete;

    LinkedListNode(const T& data);
    LinkedListNode(const LinkedListNode& otherNode) = default;

    LinkedListNode& operator=(const LinkedListNode& otherNode) = default;
    ~LinkedListNode() = default;

    LinkedListNode<T>* getNext() const;
    LinkedListNode<T>* getPrevious() const;
    T getData() const;


    void setNext(LinkedListNode<T>* next);
    void setPrevious(LinkedListNode<T>* previous);
    void setData(const T& newData);

    T m_data;

private:
    LinkedListNode<T>* m_next;
    LinkedListNode<T>* m_previous;
//    Node<T>* m_ptrToRankTree;
    Node<int>* m_ptrPlayer;

};


template<class T>
LinkedListNode<T>::LinkedListNode(const T& data): m_data(data), m_next(nullptr), m_previous(nullptr){}



template<class T>
LinkedListNode<T>* LinkedListNode<T>::getNext() const{
    return m_next;
}

template<class T>
LinkedListNode<T>* LinkedListNode<T>::getPrevious() const {
    return m_previous;
}

template<class T>
T LinkedListNode<T>::getData() const{
    return m_data;
}

template<class T>
void LinkedListNode<T>::setNext(LinkedListNode<T>* next){
    m_next = next;
}

template<class T>
void LinkedListNode<T>::setPrevious(LinkedListNode<T>* previous){
    m_previous = previous;
}

template<class T>
void LinkedListNode<T>::setData(const T& newData){
    m_data = newData;
}



#endif //DATA_STRUCTURES_EX1_LINKEDLISTNODE_H
