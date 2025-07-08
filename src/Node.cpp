#include "Node.h"
#include <random>

std::mt19937 rng(std::random_device{}());

template <typename T>
Node<T>::Node() {
    this->key = T();
    this->height = 0;
    this->subtree_size = 0;
    this->priority = rng();
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

template <typename T>
Node<T>::Node(T _key) {
    this->key = _key;
    this->height = 1;
    this->subtree_size = 1;
    this->priority = rng();
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

template <typename T>
Node<T>::Node(T _key, Node<T>* l, Node<T>* r) {
    this->key = _key;
    this->height = 1;
    this->subtree_size = 1;
    this->priority = rng();
    this->left = l;
    this->right = r;
    this->parent = nullptr;
}