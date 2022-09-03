//
// Created by 张晰铭 on 2022/9/3.
//

#ifndef AVLTREE_NODE_H
#define AVLTREE_NODE_H

template<typename T>
class Node {
public:
    T val;
    int balacnum;
    int depth;
    Node<T> *parent;
    Node<T> *left;
    Node<T> *right;

    Node() : val(0), balacnum(0), depth(1), parent(nullptr), left(nullptr), right(nullptr) {}

    Node(T num) : val(num), balacnum(0), depth(1), parent(nullptr), left(nullptr), right(nullptr) {}
};


#endif //AVLTREE_NODE_H
