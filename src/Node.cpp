#include "Node.h"

template <typename T>
Node<T>::Node() {
    this->key = T();
    this->height = 0;
    this->subtree_size = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

template <typename T>
Node<T>::Node(T _key) {
    this->key = _key;
    this->height = 1;
    this->subtree_size = 1;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

template <typename T>
Node<T>::Node(T _key, Node<T>* l, Node<T>* r) {
    this->key = _key;
    this->height = 1;
    this->subtree_size = 1;
    this->left = l;
    this->right = r;
    this->parent = nullptr;
}