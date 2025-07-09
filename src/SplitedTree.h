#pragma once

#include "Node.h"

template <typename T>
struct SplitedTree {
    Node<T>* left;
    Node<T>* right;
    SplitedTree(Node<T>* l, Node<T>* r);
};

// Impl

template <typename T>
SplitedTree<T>::SplitedTree(Node<T>* l, Node<T>* r) {
    this->left = l;
    this->right = r;
}