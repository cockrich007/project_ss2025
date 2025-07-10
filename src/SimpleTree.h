#pragma once

#include "Node.h"

template <typename T>
struct SimpleTree {
private:
    Node<T>* root;

    void destruct(Node<T>* node);

    int get_height(Node<T>* node);
    int get_subtree_size(Node<T>* node);
    void update_info(Node<T>* node);

    Node<T>* find_by_key(Node<T>* node, T key);
    Node<T>* insert(Node<T>* node, T key);
    Node<T>* erase(Node<T>* node, T key);

    Node<T>* min_in_subtree(Node<T>* node);
    Node<T>* max_in_subtree(Node<T>* node);

public:
    SimpleTree();
    SimpleTree(T key);
    ~SimpleTree();

    int get_tree_height();

    bool contains(T key);
    void insert(T key);
    void erase(T key);
};

// Impl

template <typename T>
SimpleTree<T>::SimpleTree() {
    root = nullptr;
}

template <typename T>
SimpleTree<T>::SimpleTree(T key) {
    root = new Node<T>(key);
}

template <typename T>
SimpleTree<T>::~SimpleTree() {
    destruct(root);
}

template <typename T>
void SimpleTree<T>::destruct(Node<T>* node) {
    if (!node) {
        return;
    }
    destruct(node->left);
    destruct(node->right);
    delete node;
}

template <typename T>
int SimpleTree<T>::get_height(Node<T>* node) {
    return node ? node->height : 0;
}

template <typename T>
int SimpleTree<T>::get_subtree_size(Node<T>* node) {
    return node ? node->subtree_size : 0;
}

template <typename T>
void SimpleTree<T>::update_info(Node<T>* node) {
    if (!node) {
        return;
    }
    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    node->subtree_size = 1 + get_subtree_size(node->left) + get_subtree_size(node->right);
}

template <typename T>
int SimpleTree<T>::get_tree_height() {
    return get_height(root);
}

template <typename T>
Node<T>* SimpleTree<T>::min_in_subtree(Node<T>* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

template <typename T>
Node<T>* SimpleTree<T>::max_in_subtree(Node<T>* node) {
    while (node && node->right) {
        node = node->right;
    }
    return node;
}

template <typename T>
Node<T>* SimpleTree<T>::find_by_key(Node<T>* node, T key) {
    if (!node) {
        return nullptr;
    }
    if (node->key == key) {
        return node;
    }
    if (node->key > key) {
        return find_by_key(node->left, key);
    } else {
        return find_by_key(node->right, key);
    }
}

template <typename T>
bool SimpleTree<T>::contains(T key) {
    Node<T>* node = find_by_key(root, key);
    return node && (node->key == key);
}

template <typename T>
Node<T>* SimpleTree<T>::insert(Node<T>* node, T key) {
    if (!node) {
        node = new Node<T>(key);
        return node;
    }
    if (node->key > key) {
        node->left = insert(node->left, key);
        update_info(node);
        return node;
    } else if (node->key < key) {
        node->right = insert(node->right, key);
        update_info(node);
        return node;
    }
    return node;
}

template <typename T>
void SimpleTree<T>::insert(T key) {
    root = insert(root, key);
}

template <typename T>
Node<T>* SimpleTree<T>::erase(Node<T>* node, T key) {
    if (!node) {
        return nullptr;
    }
    if (key < node->key) {
        node->left = erase(node->left, key);
    } else if (key > node->key) {
        node->right = erase(node->right, key);
    } else {
        if (!node->left) {
            Node<T>* right_child = node->right;
            delete node;
            return right_child;
        } else if (!node->right) {
            Node<T>* left_child = node->left;
            delete node;
            return left_child;
        }
        Node<T>* min_right = min_in_subtree(node->right);
        node->key = min_right->key;
        node->right = erase(node->right, min_right->key);
    }
    update_info(node);
    return node;
}

template <typename T>
void SimpleTree<T>::erase(T key) {
    root = erase(root, key);
}
