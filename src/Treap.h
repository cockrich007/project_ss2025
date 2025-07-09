#pragma once

#include "Node.h"
#include "SplitedTree.h"

template <typename T>
struct Treap {
 private:
    Node<T>* root;

    void destruct(Node<T>* node);

    void set_parent(Node<T>* child, Node<T>* parent);
    void keep_parent(Node<T>* node);

    int get_height(Node<T>* node);
    int get_subtree_size(Node<T>* node);
    void update_info(Node<T>* node);

    Node<T>* merge(Node<T>* left, Node<T>* right);
    SplitedTree<T> split(Node<T>* node, T key);

    void insert(Node<T>* node, T key);
    void erase(Node<T>* node, T key);
    Node<T>* find_by_id(Node<T>* node, int id);
    Node<T>* find_by_key(Node<T>* node, T key);

    Node<T>* floor(Node<T>* node, T key);
    Node<T>* ceiling(Node<T>* node, T key);

    Node<T>* min_in_subtree(Node<T>* node);
    Node<T>* max_in_subtree(Node<T>* node);

 public:
    Treap();
    Treap(T key);
    ~Treap();

    int get_tree_height();

    void insert(T key);
    void erase(T key);
    bool contains(T key);
    T find_by_id(int id);
    // int find_by_key(T key);
    T floor(T key);
    T ceiling(T key);
};

// Impl

#include <iostream>

template <typename T>
Treap<T>::Treap() {
    root = nullptr;
}

template <typename T>
Treap<T>::Treap(T key) {
    root = new Node<T>(key);
}

template <typename T>
Treap<T>::~Treap() {
    destruct(root);
}

template <typename T>
void Treap<T>::destruct(Node<T>* node) {
    if (!node) {
        return;
    }
    destruct(node->left);
    destruct(node->right);
    delete node;
}

template <typename T>
void Treap<T>::set_parent(Node<T>* child, Node<T>* parent) {
    if (child) {
        child->parent = parent;
    }
}

template <typename T>
void Treap<T>::keep_parent(Node<T>* node) {
    if (node) {
        set_parent(node->left, node);
        set_parent(node->right, node);
    }
}

template <typename T>
int Treap<T>::get_height(Node<T>* node) {
    return node ? node->height : 0;
}

template <typename T>
int Treap<T>::get_subtree_size(Node<T>* node) {
    return node ? node->subtree_size : 0;
}

template <typename T>
void Treap<T>::update_info(Node<T>* node) {
    if (!node) {
        return;
    }
    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    node->subtree_size = 1 + get_subtree_size(node->left) + get_subtree_size(node->right);
}

template <typename T>
int Treap<T>::get_tree_height() {
    return get_height(root);
}

template <typename T>
Node<T>* Treap<T>::merge(Node<T>* left, Node<T>* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        keep_parent(left);
        update_info(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        keep_parent(right);
        update_info(right);
        return right;
    }
}

template <typename T>
SplitedTree<T> Treap<T>::split(Node<T>* node, T key) {
    if (node == nullptr) {
        return SplitedTree<T>(nullptr, nullptr);
    }
    if (node->key < key) {
        SplitedTree<T> splited = split(node->right, key);
        node->right = splited.left;
        keep_parent(node);
        update_info(node);
        return SplitedTree<T>(node, splited.right);
    } else {
        SplitedTree<T> splited = split(node->left, key);
        node->left = splited.right;
        keep_parent(node);
        update_info(node);
        return SplitedTree<T>(splited.left, node);
    }
}

template <typename T>
void Treap<T>::insert(T key) {
    if (root == nullptr) {
        root = new Node<T>(key);
        return;
    }
    SplitedTree<T> splited = split(root, key);
    Node<T>* new_node = new Node<T>(key);
    root = merge(merge(splited.left, new_node), splited.right);
}

template <typename T>
void Treap<T>::erase(T key) {
    if (root == nullptr) {
        return;
    }
    SplitedTree<T> splited = split(root, key);
    if (splited.right != nullptr && splited.right->key == key) {
        Node<T>* del = splited.right;
        splited.right = merge(del->left, del->right);
        delete del;
    }
    root = merge(splited.left, splited.right);
}

template <typename T>
bool Treap<T>::contains(T key) {
    Node<T>* node = find_by_key(root, key);
    return node && node->key == key;
}

template <typename T>
Node<T>* Treap<T>::find_by_key(Node<T>* node, T key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->key == key) {
        return node;
    }
    if (key < node->key) {
        return find_by_key(node->left, key);
    }
    return find_by_key(node->right, key);
}

template <typename T>
Node<T>* Treap<T>::find_by_id(Node<T>* node, int id) {
    if (node == nullptr) {
        return nullptr;
    }
    int left_size = get_subtree_size(node->left);
    if (id == left_size) {
        return node;
    }
    if (id < left_size) {
        return find_by_id(node->left, id);
    }
    return find_by_id(node->right, id - left_size - 1);
}

template <typename T>
T Treap<T>::find_by_id(int id) {
    Node<T>* node = find_by_id(root, id);
    if (node == nullptr) {
        return T();
    }
    return node->key;
}

template <typename T>
Node<T>* Treap<T>::floor(Node<T>* node, T key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->key == key) {
        return node;
    }
    if (node->key > key) {
        return floor(node->left, key);
    }
    Node<T>* right_floor = floor(node->right, key);
    return right_floor ? right_floor : node;
}

template <typename T>
T Treap<T>::floor(T key) {
    Node<T>* node = floor(root, key);
    if (node == nullptr) {
        return T();
    }
    return node->key;
}

template <typename T>
Node<T>* Treap<T>::ceiling(Node<T>* node, T key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->key == key) {
        return node;
    }
    if (node->key < key) {
        return ceiling(node->right, key);
    }
    Node<T>* left_ceiling = ceiling(node->left, key);
    return left_ceiling ? left_ceiling : node;
}

template <typename T>
T Treap<T>::ceiling(T key) {
    Node<T>* node = ceiling(root, key);
    if (node == nullptr) {
        return T();
    }
    return node->key;
}
