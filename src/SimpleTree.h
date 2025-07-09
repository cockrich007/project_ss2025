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

// Impl

#include <iostream>
#include <numeric>
#include <limits>

template <typename T>
SimpleTree<T>::SimpleTree() {
    root = nullptr;
    size = 0;
}

template <typename T>
SimpleTree<T>::SimpleTree(T first_value) {
    root = new Node<T>(first_value);
    size = 1;
}

template <typename T>
SimpleTree<T>::SimpleTree(Node<T>* root) {
    this->root = root;
}

template <typename T>
SimpleTree<T>::~SimpleTree() {
    delete root;
}

template <typename T>
void SimpleTree<T>::insert(T key) {
    Node<T>* cur_node = root;
    bool is_inserted = false;

    if (root == nullptr) {
        root = new Node<T>(key);
        ++size;
        return;
    }

    while (!is_inserted) {
        if (cur_node->key > key) {
            if (cur_node->left == nullptr) {
                cur_node->left = new Node<T>(key);
                is_inserted = true;
            }
            cur_node = cur_node->left;
        } else if (cur_node->key < key) {
            if (cur_node->right == nullptr) {
                cur_node->right = new Node<T>(key);
                is_inserted = true;
            }
            cur_node = cur_node->right;
        } else {
            return;
        }
    }
    ++size;
}

template <typename T>
void SimpleTree<T>::erase(Node<T>* node, T key) {
    if (node == nullptr) {
        return;
    }
    if (key < node->key) {
        erase(node->left, key);
    } else if (key > node->key) {
        erase(node->right, key);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
            --size;
        } else if (node->left == nullptr) {
            Node<T>* temp = node;
            node = node->right;
            delete temp;
            --size;
        } else if (node->right == nullptr) {
            Node<T>* temp = node;
            node = node->left;
            delete temp;
            --size;
        } else {
            Node<T>* min_right = node->right;
            while (min_right->left != nullptr) {
                min_right = min_right->left;
            }
            node->key = min_right->key;
            erase(node->right, min_right->key);
        }
    }
}

template <typename T>
void SimpleTree<T>::erase(T key) {
    erase(root, key);
}

template <typename T>
T SimpleTree<T>::find_by_id(int index, Node<T>* cur_node, int &pos) {
    int buffer;
    if (cur_node->left != nullptr) {
        if ((buffer = find_by_id(index, cur_node->left, pos)) != std::numeric_limits<T>::max()) {
            return buffer;
        }
    }
    if (pos == index) {
        return cur_node->key;
    }
    ++pos;
    if (cur_node->right != nullptr) {
        if ((buffer = find_by_id(index, cur_node->right, pos)) != std::numeric_limits<T>::max()) {
            return buffer;
        }
    }
    return std::numeric_limits<T>::max();
}

template <typename T>
T SimpleTree<T>::find_by_id(int index) {
    int pos = 0;
    if (root == nullptr) {
        return std::numeric_limits<T>::max();
    }
    return find_by_id(index, root, pos);
}

template <typename T>
void SimpleTree<T>::find_floor(T key, Node<T>* cur_node, T &local_max) {
    if (cur_node->key > key) {
        if (cur_node->left != nullptr) {
            find_floor(key, cur_node->left, local_max);
        }
    } else if (cur_node->key < key) {
        if (local_max < cur_node->key) {
            local_max = cur_node->key;
        }
        if (cur_node->right != nullptr) {
            find_floor(key, cur_node->right, local_max);
        }
    } else {
        cur_node = cur_node->left;
        if (cur_node == nullptr) {
            return;
        }
        while (cur_node->right != nullptr) {
            cur_node = cur_node->right;
        }
        local_max = cur_node->key;
    }
}

template <typename T>
T SimpleTree<T>::floor(T key) {
    T local_max = std::numeric_limits<T>::min();
    if (root == nullptr) {
        return std::numeric_limits<T>::min();
    }
    find_floor(key, root, local_max);
    return local_max;
}

template <typename T>
void SimpleTree<T>::find_ceiling(T key, Node<T>* cur_node, T &local_min) {
    if (cur_node->key > key) {
        if (local_min > cur_node->key) {
            local_min = cur_node->key;
        }
        if (cur_node->left != nullptr) {
            find_ceiling(key, cur_node->left, local_min);
        }
    } else if (cur_node->key < key) {
        if (cur_node->right != nullptr) {
            find_ceiling(key, cur_node->right, local_min);
        }
    } else {
        cur_node = cur_node->right;
        if (cur_node == nullptr) {
            return;
        }
        while (cur_node->left != nullptr) {
            cur_node = cur_node->left;
        }
        local_min = cur_node->key;
    }
}

template <typename T>
T SimpleTree<T>::ceiling(T key) {
    T local_min = std::numeric_limits<T>::max();
    if (root == nullptr) {
        return std::numeric_limits<T>::max();
    }
    find_ceiling(key, root, local_min);
    return local_min;
}
