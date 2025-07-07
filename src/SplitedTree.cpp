#include "SplitedTree.h"

template <typename T>
SplitedTree<T>::SplitedTree(Node<T>* l, Node<T>* r) {
    this->left = l;
    this->right = r;
}