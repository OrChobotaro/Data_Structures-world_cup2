
#include "RankTree.h"
#include <stdio.h>


int main2(){

    AvlTree<int> tree;

    tree.insert(4);
    tree.insert(8);
    tree.insert(2);
    tree.insert(5);
    tree.insert(7);
    tree.insert(21);
    tree.insert(51);
    tree.insert(71);

    std::cout << countNodes(tree.getRoot());

    return 0;
}
