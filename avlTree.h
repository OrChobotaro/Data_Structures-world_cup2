#ifndef DATA_STRUCTURES_EX1_AvlTree_H
#define DATA_STRUCTURES_EX1_AvlTree_H

#include <iostream>
#include "Node.h"
#include "wet2util.h"
#include <exception>
#include <assert.h>




template<class T>
void updateHeights(Node<T>* node);


template<class T>
class AvlTree{
public:
    AvlTree();
    AvlTree(const AvlTree<T>& otherTree) = default;
    AvlTree<T>& operator=(const AvlTree<T>& otherTree) = default;
    ~AvlTree();

    StatusType insert(const T& key);
    StatusType insertToBinaryTree (Node<T>* node, const T& key);

    StatusType remove (const T& key);
    Node<T>* removeFromBinaryTree (Node<T>* node);
    void removeNodeAux(Node<T>* node);
    void removeAvlTree(Node<T>* node);

    Node<T>* findParentBeforeInsert(const T& key);



    Node<T>* getRoot() const;

    void setRoot(Node<T>* node);


    Node<T>* balanceTree(Node<T>* lastAddedNode);
    int calcBalance(Node<T>* node);


    Node<T>* find(const T& key) const;
    Node<T>* findFollowNode(Node<T>* node);


    Node<T>* LL(Node<T>* unbalancedNode);
    Node<T>* RR(Node<T>* unbalancedNode);
    Node<T>* LR(Node<T>* unbalancedNode);
    Node<T>* RL(Node<T>* unbalancedNode);


    Node<T>* newNode(const T& key); //todo: לבדוק אם צריך לקבל גם אב

    int getHeight();

private:
    Node<T>* m_root;


};



template<class T>
AvlTree<T>::AvlTree(): m_root(nullptr){}

template<class T>
AvlTree<T>::~AvlTree(){
    if (m_root) {
        removeAvlTree(m_root);
        delete m_root;
    }

}


template<class T>
void AvlTree<T>::removeAvlTree(Node<T> *node) {
    if (node->isLeaf()) {
        return;
    }
    if (node->getRight()) {
        removeAvlTree(node->getRight());
        delete node->getRight();
        node->setRight(nullptr);
    }
    if (node->getLeft()) {
        removeAvlTree(node->getLeft());

        delete node->getLeft();
        node->setLeft(nullptr);
    }
}



template<class T>
Node<T>* AvlTree<T>::newNode(const T& key) {
    return new Node<T>(key);
}

template<class T>
Node<T>* AvlTree<T>::getRoot() const {
    return m_root;
}


template<class T>
StatusType AvlTree<T>::insert(const T& key){

    try {
        Node<T>* node = newNode(key);
        StatusType result = insertToBinaryTree(node, key);
        if (result == StatusType::FAILURE) {
            delete node;
            return StatusType::FAILURE;
        }
        updateHeights(node);
        balanceTree(node);
    }
    catch (std::bad_alloc& error) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


template <class T>
StatusType AvlTree<T>::insertToBinaryTree (Node<T>* node, const T& key) {
    if(m_root == nullptr){
        m_root = node;
        return StatusType::SUCCESS;
    }

    Node<T>* temp = m_root;
    Node<T>* tempParent = nullptr;
    bool isLeft;

    while(temp != nullptr){
        tempParent = temp;
        if(key < temp->getKey()){
            temp = temp->getLeft();
            isLeft = true;
        }
        else if(key > temp->getKey()){
            temp = temp->getRight();
            isLeft = false;
        }
        else{
            return StatusType::FAILURE;
        }
    }

    node->setParent(tempParent);
    if(isLeft){
        tempParent->setLeft(node);
    }
    else{
        tempParent->setRight(node);
    }
    return StatusType::SUCCESS;
}






template<class T>
void updateHeights(Node<T> *node) {

    while(node) {
        if (node->isLeaf()) {
            node->setHeight(0);
            node = node->getParent();
            continue;
        }
        int maxHeight = node->calcHeight();
        node->setHeight(maxHeight+1);
        node = node->getParent();
    }
}





template<class T>
Node<T>* AvlTree<T>::balanceTree(Node<T>* lastAddedNode){
    assert(lastAddedNode);
    Node<T>* node = lastAddedNode;

    while(node){
        if(node->isLeaf()){
            node = node->getParent();
            continue;
        }

        int currentNodeBalance = calcBalance(node);


        int leftBalance = calcBalance(node->getLeft());


        int rightBalance = calcBalance(node->getRight());

        if(currentNodeBalance == 2){
            if(leftBalance == 0 || leftBalance == 1){
                return LL(node);
            }
            else if(leftBalance == -1){
                return LR(node);
            }
        }
        else if(currentNodeBalance == -2){
            if(rightBalance == 0 || rightBalance == -1){
                return RR(node);
            }
            else if(rightBalance == 1){
                return RL(node);
            }
        }
        node = node->getParent();
    }
    return nullptr;
}



template<class T>
StatusType AvlTree<T>::remove(const T &key) {
    Node<T>* node = find(key);
    if(!node){
        return StatusType::FAILURE;
    }
    try{
        Node<T>* parent = removeFromBinaryTree(node);
        Node<T>* nodeToBalance = parent;
        while(nodeToBalance){
            nodeToBalance = balanceTree(nodeToBalance);
        }

    }
    catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}



template<class T>
Node<T>* AvlTree<T>::removeFromBinaryTree(Node<T> *node) {
    Node<T>* followingNode = nullptr;
    Node<T>* parent = node->getParent();

    try{
        if (node->getLeft() && node->getRight()){
            followingNode = findFollowNode(node);
            parent = followingNode->getParent();
            node->switchNodes(followingNode);
            if(this->getRoot() == node){
                this->setRoot(followingNode);
            } else if(this->getRoot() == followingNode){
                this->setRoot(node);
            }
            parent = node->getParent();
            removeNodeAux(node);
        }
        else{
            removeNodeAux(node);
        }

    }
    catch (std::bad_alloc& e) {

        throw std::bad_alloc();
    }
    if (parent) {
        updateHeights(parent);
    }
    return parent;
}



// remove node when has one or less sons.
template<class T>
void AvlTree<T>::removeNodeAux(Node<T> *node) {
    Node<T>* parent = node->getParent();
    if (node->isLeaf() && parent) {
        if (node->isLeftNew(parent)) {
            parent->setLeft(nullptr);
        }
        else {
            parent->setRight(nullptr);
        }

        node->setParent(nullptr);
        delete node;
        return;
    }

    Node<T>* left = node->getLeft();
    Node<T>* right = node->getRight();
    bool isRemoveNodeLeftSon;
    if(parent){
        isRemoveNodeLeftSon = node->isLeftNew(parent);
        if (isRemoveNodeLeftSon) {
            if(left){
                parent->setLeft(left);
                left->setParent(parent);
                node->setLeft(nullptr);
            }
            else {
                parent->setLeft(right);
                right->setParent(parent);
                node->setRight(nullptr);
            }
        }
        else {
            if(left){
                parent->setRight(left);
                left->setParent(parent);
                node->setLeft(nullptr);
            }
            else {
                parent->setRight(right);
                right->setParent(parent);
                node->setRight(nullptr);
            }
        }
    }

    else{
        if(left){
            m_root = left;
            left->setParent(nullptr);
        }
        else if(right){
            m_root = right;
            right->setParent(nullptr);
        }
        else {
            m_root = nullptr;
        }
    }
    node->setParent(nullptr);


    delete node;
}


template<class T>
int AvlTree<T>::calcBalance(Node<T>* node){
    if(!node){
        return 0;
    }

    int heightLeft = -1;
    int heightRight = -1;

    if(node->getRight()){
        heightRight = (node->getRight())->getHeight();
    }
    if(node->getLeft()){
        heightLeft = (node->getLeft())->getHeight();
    }

    return (heightLeft - heightRight);
}


template<class T>
Node<T>* AvlTree<T>::LL(Node<T>* unbalancedNode){

    Node<T>* nodeA = unbalancedNode->getLeft();
    Node<T>* nodeARight = nodeA->getRight();
    Node<T>* parentOfUnbalancedNode = unbalancedNode->getParent();

    //Ar from right of A to left of B
    unbalancedNode->setLeft(nodeARight);
    if(nodeARight){
        nodeARight->setParent(unbalancedNode);
    }

    // A parent of B an B left of A
    unbalancedNode->setParent(nodeA);
    nodeA->setRight(unbalancedNode);

    // B parent is A parent
    nodeA->setParent(parentOfUnbalancedNode);
    if(parentOfUnbalancedNode){
        if(parentOfUnbalancedNode->getLeft() == unbalancedNode){
            parentOfUnbalancedNode->setLeft(nodeA);
        }
        else {
            parentOfUnbalancedNode->setRight(nodeA);
        }
    } else {
        m_root = nodeA;
    }

    updateHeights(unbalancedNode);
    return nodeA;
}

template<class T>
Node<T>* AvlTree<T>::RR(Node<T>* unbalancedNode){

    // A right of B
    Node<T>* nodeA = unbalancedNode->getRight();
    // AL
    Node<T>* nodeALeft = nodeA->getLeft();
    Node<T>* parentOfUnbalancedNode = unbalancedNode->getParent();

    // AL -> Right B
    unbalancedNode->setRight(nodeALeft);
    if(nodeALeft){

        nodeALeft->setParent(unbalancedNode);
    }

    // A -> Parent B
    unbalancedNode->setParent(nodeA);
    nodeA->setLeft(unbalancedNode);

    if(parentOfUnbalancedNode){
        if(parentOfUnbalancedNode->getLeft() == unbalancedNode){
            parentOfUnbalancedNode->setLeft(nodeA);
        }
        else {
            parentOfUnbalancedNode->setRight(nodeA);
        }
    } else {
        m_root = nodeA;
    }

    nodeA->setParent(parentOfUnbalancedNode);

    updateHeights(unbalancedNode);
    return nodeA;
}

template<class T>
Node<T>* AvlTree<T>::LR(Node<T>* unbalancedNode){
    Node<T>* nodeB = unbalancedNode->getLeft();
    RR(nodeB);
    return LL(unbalancedNode);
}

template<class T>
Node<T>* AvlTree<T>::RL(Node<T>* unbalancedNode){
    Node<T>* nodeB = unbalancedNode->getRight();
    LL(nodeB);
    return RR(unbalancedNode);
}

template<class T>
Node<T>* AvlTree<T>::find(const T& key) const {
    Node<T>* temp = m_root;
    while (temp != nullptr) {
        if (key < temp->getKey()) {
            temp = temp->getLeft();
        }
        else if (key > temp->getKey()) {
            temp = temp->getRight();
        }
        else {
            return temp;
        }
    }

    return nullptr;
}

template<class T>
Node<T>* AvlTree<T>::findFollowNode(Node<T>* node){
    Node<T>* temp = node;
    Node<T>* followingNode = temp;
    temp = temp->getRight();
    while(temp){
        followingNode = temp;
        temp = temp->getLeft();
    }
    return followingNode;
}


template<class T>
void AvlTree<T>::setRoot(Node<T> *node) {
    m_root = node;
}

template<class T>
int AvlTree<T>::getHeight(){
    if(m_root == nullptr){
        return -1;
    }
    return m_root->getHeight();
}

template<class T>
int numOfNodes(Node<T>* curr) {
    if (!curr)
        return 0;
    return 1+ numOfNodes(curr->getLeft()) + numOfNodes(curr->getRight());
}



template<class T>
Node<T>* AvlTree<T>::findParentBeforeInsert(const T &key) {
    Node<T>* temp = m_root;
    Node<T>* parent = nullptr;
    while (temp != nullptr) {
        parent = temp;
        if (key < temp->getKey()) {
            temp = temp->getLeft();
        }
        else if (key > temp->getKey()) {
            temp = temp->getRight();
        }
        else {
            return nullptr;
        }
    }
    return parent;
}






#endif //DATA_STRUCTURES_EX1_AvlTree_H

