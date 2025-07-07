#pragma once

#include "Node.h"
#include "SplitedTree.h"

template <typename T>
struct SplayTree {
private:
    Node<T>* root;

    void destruct(Node<T>* node);
    void set_parent(Node<T>* child, Node<T>* parent);
    void keep_parent(Node<T>* node);
    int get_height(Node<T>* node);
    int get_subtree_size(Node<T>* node);
    void update_info(Node<T>* node);
    int get_rank(Node<T>* node);
    void rotate(Node<T>* parent, Node<T>* child);
    Node<T>* splay(Node<T>* node);
    Node<T>* find_by_key(Node<T>* root, T key);
    SplitedTree<T> split(Node<T>* root, T key);
    Node<T>* insert(Node<T>* root, T key);
    Node<T>* merge(Node<T>* left, Node<T>* right);
    Node<T>* erase(Node<T>* root, T key);
    Node<T>* min_in_subtree(Node<T>* node);
    Node<T>* max_in_subtree(Node<T>* node);
    Node<T>* find_by_id(Node<T>* node, int id);

public:
    SplayTree() : root(nullptr) {}
    SplayTree(T _key) : root(new Node<T>(_key)) {}
    ~SplayTree() { destruct(root); }

    void insert(T key);
    void erase(T key);
    bool contains(T key);
    int find_by_key(T key);
    T find_by_id(int id);
    T floor(T key);
    T ceiling(T key);
};

#include "SplayTree.cpp"