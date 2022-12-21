#ifndef DATA_STRUCTURES_EX1_NODE_H
#define DATA_STRUCTURES_EX1_NODE_H



int max(int a, int b);


template<class T>
class Node {
public:
    Node() = delete;
    Node(const T& key);
    Node(const Node& otherNode) = default;
    Node& operator=(const Node& otherNode) = delete;
    ~Node() = default;

    T& getKey();
    Node<T>* getParent() const;
    Node<T>* getLeft() const;
    Node<T>* getRight() const;
    int getHeight() const;


    void setParent(Node<T>* newParent);
    void setRight(Node<T>* newRight);
    void setLeft(Node<T>* newLeft);
    void setHeight(int height);
    void setKey(T newKey);


    void switchCloseNodes(Node<T>* node2);
    bool isLeftNew(Node<T>* parent);
    void switchNodes(Node<T>* nodeToSwitchWith);
    bool isLeaf();
    int calcHeight();
    void switchNodesRegular(Node<T>* node2);




    T m_key;
private:
    Node<T>* m_right;
    Node<T>* m_left;
    Node<T>* m_parent;
    int m_height;

};





template<class T>
Node<T>::Node(const T& key):
    m_key(key), m_right(nullptr), m_left(nullptr), m_parent(nullptr), m_height(0){}


template<class T>
T& Node<T>::getKey(){
        return m_key;
}

template<class T>
void Node<T>::setParent(Node<T>* newParent){
    m_parent = newParent;
}

template<class T>
void Node<T>::setRight(Node<T>* newRight){
    m_right = newRight;
}


template<class T>
void Node<T>::setHeight(int height) {
     m_height = height;
}


template<class T>
void Node<T>::setLeft(Node<T>* newLeft){
    m_left = newLeft;
}


template<class T>
Node<T>* Node<T>::getParent() const{
    return m_parent;
}


template<class T>
Node<T>* Node<T>::getLeft() const{
    return m_left;
}


template<class T>
Node<T>* Node<T>::getRight() const{
    return m_right;
}

template<class T>
int Node<T>::getHeight() const {
    return m_height;
}



template<class T>
void Node<T>::setKey(T newKey){
    m_key = newKey;
}

template<class T>
bool Node<T>::isLeaf(){
    if (!this->getLeft() && !this->getRight()) {
        return true;
    }
    return false;
}





template<class T>
void Node<T>::switchNodes(Node<T>* nodeToSwitchWith){
    if (!nodeToSwitchWith) {
        return;
    }
    if (nodeToSwitchWith->getRight() == this || nodeToSwitchWith->getLeft() == this) {
        nodeToSwitchWith->switchCloseNodes(this);
    }
    else if (this->getRight() == nodeToSwitchWith || this->getLeft() == nodeToSwitchWith) {
        this->switchCloseNodes(nodeToSwitchWith);
    }
    else {
        switchNodesRegular(nodeToSwitchWith);
    }


}



template<class T>
int Node<T>::calcHeight(){
    Node<T>* node = this;
    int heightRight = 0;
    int heightLeft = 0;
    if (node->getRight()) {
        heightRight = (node->getRight())->getHeight();
    }
    if (node->getLeft()) {
        heightLeft = (node->getLeft())->getHeight();
    }
    return max(heightLeft, heightRight);
}


//node1 - parent
 //node2 - son
template<class T>
void Node<T>::switchCloseNodes(Node<T>* node2){
    Node<T>* node1Left = this->getLeft();
    Node<T>* node1Right = this->getRight();
    Node<T>* node1Parent = this->getParent();
    Node<T>* node2Left = node2->getLeft();
    Node<T>* node2Right = node2->getRight();

    Node<T>* node1;

    node1 = this;


    if(node1->getRight() == node2 || node1->getLeft() == node2){
        bool isLeft;
        bool isLeft2;

        node2->setParent(node1Parent);
        isLeft = node1->isLeftNew(node1Parent);
         if(node1Parent){
             if(isLeft){
                 node1Parent->setLeft(node2);
             }
             else {
                 node1Parent->setRight(node2);
             }
         }


         isLeft2 = node2->isLeftNew(node1);

         if(isLeft2){
             node2->setLeft(node1);
             node1->setParent((node2));
             node2->setRight(node1Right);
             if(node1Right){
                 node1Right->setParent(node2);
             }
         }
         else {
             node2->setRight(node1);
             node1->setParent(node2);
             node2->setLeft(node1Left);
             if(node1Left){
                 node1Left->setParent(node2);
             }
         }

        node1->setRight(node2Right);

         if(node2Right){
             node2Right->setParent(node1);
         }
        node1->setLeft(node2Left);
         if(node2Left){
             node2Left->setParent(node1);
         }
    }

    // change heights
    int height1 = this->getHeight();
    int height2 = node2->getHeight();

    node1->setHeight(height2);
    node2->setHeight(height1);
}


template<class T>
bool Node<T>::isLeftNew(Node<T>* parent){
    bool isLeft = false;
    if(!parent){
        return false;
    }
    if(parent->getLeft() == this){
        isLeft = true;
    }
    return isLeft;
}


template<class T>
void Node<T>::switchNodesRegular(Node<T>* node2) {
    Node<T>* parentNode1 = m_parent;
    Node<T>* rightSon1 = m_right;
    Node<T>* leftSon1 = m_left;
    bool isNode1Left = this->isLeftNew(m_parent);
    int heightNode1 = m_height;

    Node<T>* parentNode2 = node2->getParent();
    Node<T>* rightSon2 = node2->getRight();
    Node<T>* leftSon2 = node2->getLeft();
    bool isNode2Left = node2->isLeftNew(parentNode2);
    int heightNode2 = node2->getHeight();

    setParent(parentNode2);
    if (parentNode2) {
        if (isNode2Left) {
            parentNode2->setLeft(this);
        }
        else {
            parentNode2->setRight(this);
        }
    }

    setRight(rightSon2);
    if (rightSon2) {
        rightSon2->setParent(this);
    }

    setLeft(leftSon2);
    if (leftSon2) {
        leftSon2->setParent(this);
    }

    setHeight(heightNode2);


    node2->setParent(parentNode1);
    if (parentNode1) {
        if (isNode1Left) {
            parentNode1->setLeft(node2);
        }
        else {
            parentNode1->setRight(node2);
        }
    }

    node2->setRight(rightSon1);
    if (rightSon1) {
        rightSon1->setParent(node2);
    }

    node2->setLeft(leftSon1);
    if (leftSon1) {
        leftSon1->setParent(node2);
    }

    node2->setHeight(heightNode1);
}




#endif //DATA_STRUCTURES_EX1_NODE_H
