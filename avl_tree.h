//
// Created by 张晰铭 on 2022/9/3.
//

#ifndef AVLTREE_AVL_TREE_H
#define AVLTREE_AVL_TREE_H

#include "vector"
#include "node.h"

#define depth(n) (n?n->depth:0)

template<typename T>
class avl_tree {
private:
    Node<T> *root;

    Node<T> *insert(Node<T> *node, T data);

    Node<T> *rightRotate(Node<T> *root);

    Node<T> *leftRotate(Node<T> *root);

    Node<T> *deleteX(Node<T> *root, T data);

    Node<T> *minEle(Node<T> *root);

public:
    avl_tree(std::vector<T> &);

    avl_tree() : root(nullptr) {};

    void add(T data);

    void remove(T data);

    void traverse();


};

#include "queue"
#include "iostream"

template<typename T>
Node<T> *avl_tree<T>::minEle(Node<T> *root) {
    if (!root) return nullptr;
    while (root->left) root = root->left;
    return root;
}

template<typename T>
void avl_tree<T>::traverse() {
    std::queue<Node<T> *> q;
    if (root) q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            auto n = q.front();
            q.pop();
            std::cout << n->val << " ";
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        std::cout << std::endl;
    }
}


template<typename T>
avl_tree<T>::avl_tree(std::vector<T> &v) {
    for (auto e: v) add(e);
}

template<typename T>
void avl_tree<T>::add(T data) {
    root = insert(root, data);
}

template<typename T>
Node<T> *avl_tree<T>::insert(Node<T> *node, T data) {
    if (!node) {
        return new Node<T>(data);
    } else {
        if (data < node->val) {
            node->left = insert(node->left, data);
        } else if (data > node->val) {
            node->right = insert(node->right, data);
        } else return node;
        node->depth = std::max(depth(node->left), depth(node->right)) + 1;
        int balance = depth(node->left) - (depth(node->right));
        if (balance > 1) {
            if (data < node->left->val) {
                return rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if (balance < -1) {
            if (data < node->right->val) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            } else {
                return leftRotate(node);
            }
        }
    }
    return node;
}

template<typename T>
Node<T> *avl_tree<T>::rightRotate(Node<T> *root) {
    Node<T> *newroot = root->left, *mv = newroot->right;
    root->left = mv;
    newroot->right = root;
    newroot->depth = std::max(depth(newroot->left), depth(newroot->right)) + 1;
    root->depth = std::max(depth(root->left), depth(root->right)) + 1;
    return newroot;
}

template<typename T>
Node<T> *avl_tree<T>::leftRotate(Node<T> *root) {
    Node<T> *newroot = root->right, *mv = newroot->left;
    newroot->left = root;
    root->right = mv;
    root->depth = std::max(depth(root->left), depth(root->right)) + 1;
    newroot->depth = std::max(depth(newroot->left), depth(newroot->right)) + 1;
    return newroot;
}

template<typename T>
void avl_tree<T>::remove(T data) {
    root = deleteX(root, data);
}

template<typename T>
Node<T> *avl_tree<T>::deleteX(Node<T> *root, T data) {
    if (!root) return nullptr;
    if (data < root->val) {
        root->left = deleteX(root->left, data);
    } else if (data > root->val) {
        root->right = deleteX(root->right, data);
    } else {
        if (!root->left || !root->right) {
            Node<T> *tmp = root->left ? root->left : root->right;
            if (!tmp) {
                tmp = root;
                root = nullptr;
            } else {
                *root = *tmp;
                delete tmp;
            }
        } else {
            auto tmp = minEle(root->right);
            root->val = tmp->val;
            root->right = deleteX(root->right, tmp->val);
        }
    }
    if (!root) return nullptr;

    root->depth = std::max(depth(root->left), depth(root->right)) + 1;
    auto getBalance = [](Node<T> *r) { return depth(r->left) - depth(r->right); };
    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balance < -1) {
        if (getBalance(root->right) <= 0) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}


#endif //AVLTREE_AVL_TREE_H
