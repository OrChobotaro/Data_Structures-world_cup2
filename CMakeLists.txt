cmake_minimum_required(VERSION 3.20)
project(Data_Structures_ex2_new)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Data_Structures_ex2_new
        avlTree.h
        Node.h
        Node.cpp
        hashTable.h
        HashTable.cpp
        HashPlayerData.h
        HashPlayerData.cpp
        LinkedList.h
        LinkedListNode.h
        UnionFindData.cpp
        UnionFindData.h
        wet2util.h
        worldcup23a2.cpp
        worldcup23a2.h
        UnionFind.h
        UnionFind.cpp
        RankTree.h
        RankTree.cpp
        main.cpp
        main23a2.cpp
        RankTreeTests.cpp
        UnionFindTests.cpp
        WorldCupTests.cpp
        catch.hpp)


