#pragma once

#include "Node.h"

template <typename T>
struct SimpleTree {
 private:
    Node<T>* root;
    int size;

    void erase(Node<T>* node, T value);
    T find_by_id(int id, Node<T>* cur_node, int &pos);
    void find_floor(T key, Node<T>* cur_node, T &local_max);
    void find_ceiling(T key, Node<T>* cur_node, T &local_min);

 public:
    SimpleTree();
    SimpleTree(T key);
    SimpleTree(Node<T>* root);
    ~SimpleTree();

    void insert(T value);
    void erase(T value);
    T find_by_id(int id);
    T floor(T value);
    T ceiling(T value);
};

#include "SimpleTree.cpp"