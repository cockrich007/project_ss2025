#pragma once

template <typename T>
struct Node {
    T key;
    int height;
    int subtree_size;
    long long priority;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;

    Node();
    Node(T _key);
    Node(T _key, Node<T>* l, Node<T>* r);
};

#include "Node.cpp"