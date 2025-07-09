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

// Impl

#include <iostream>

template <typename T>
void SplayTree<T>::destruct(Node<T>* node) {
    if (!node) {
        return;
    }
    destruct(node->left);
    destruct(node->right);
    delete node;
}

template <typename T>
void SplayTree<T>::set_parent(Node<T>* child, Node<T>* parent) {
    if (child) {
        child->parent = parent;
    }
}

template <typename T>
void SplayTree<T>::keep_parent(Node<T>* node) {
    if (node) {
        set_parent(node->left, node);
        set_parent(node->right, node);
    }
}

template <typename T>
int SplayTree<T>::get_height(Node<T>* node) {
    return node ? node->height : 0;
}

template <typename T>
int SplayTree<T>::get_subtree_size(Node<T>* node) {
    return node ? node->subtree_size : 0;
}

template <typename T>
void SplayTree<T>::update_info(Node<T>* node) {
    if (!node) {
        return;
    }
    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    node->subtree_size = 1 + get_subtree_size(node->left) + get_subtree_size(node->right);
}

template <typename T>
int SplayTree<T>::get_rank(Node<T>* node) {
    if (!node) {
        return -1;
    }
    return get_subtree_size(node->left);
}

template <typename T>
void SplayTree<T>::rotate(Node<T>* parent, Node<T>* child) {
    Node<T>* grand_parent = parent->parent;
    if (grand_parent) {
        if (grand_parent->left == parent) {
            grand_parent->left = child;
        } else {
            grand_parent->right = child;
        }
    }
    if (parent->left == child) {
        parent->left = child->right;
        child->right = parent;
    } else {
        parent->right = child->left;
        child->left = parent;
    }
    keep_parent(child);
    keep_parent(parent);
    child->parent = grand_parent;
    update_info(parent);
    update_info(child);
}

template <typename T>
Node<T>* SplayTree<T>::splay(Node<T>* node) {
    if (!node || !node->parent) {
        return node;
    }
    Node<T>* parent = node->parent;
    Node<T>* grand_parent = parent->parent;
    if (!grand_parent) {
        rotate(parent, node);
        return node;
    } else {
        bool zigzig = (grand_parent->left == parent) == (parent->left == node);
        if (zigzig) {
            rotate(grand_parent, parent);
            rotate(parent, node);
        } else {
            rotate(parent, node);
            rotate(grand_parent, node);
        }
        return splay(node);
    }
}

template <typename T>
Node<T>* SplayTree<T>::find_by_key(Node<T>* root, T key) {
    if (!root) {
        return nullptr;
    }
    if (key == root->key) {
        return splay(root);
    }
    if (key < root->key && root->left) {
        return find_by_key(root->left, key);
    }
    if (key > root->key && root->right) {
        return find_by_key(root->right, key);
    }
    return splay(root);
}

template <typename T>
SplitedTree<T> SplayTree<T>::split(Node<T>* root, T key) {
    if (!root) {
        return SplitedTree<T>(nullptr, nullptr);
    }
    root = find_by_key(root, key);
    if (root->key == key) {
        set_parent(root->left, nullptr);
        set_parent(root->right, nullptr);
        Node<T>* left_subtree = root->left;
        Node<T>* right_subtree = root->right;
        delete root;
        return SplitedTree<T>(left_subtree, right_subtree);
    }
    if (root->key < key) {
        Node<T>* right = root->right;
        root->right = nullptr;
        set_parent(right, nullptr);
        update_info(root);
        return SplitedTree<T>(root, right);
    } else {
        Node<T>* left = root->left;
        root->left = nullptr;
        set_parent(left, nullptr);
        update_info(root);
        return SplitedTree<T>(left, root);
    }
}

template <typename T>
Node<T>* SplayTree<T>::insert(Node<T>* root, T key) {
    SplitedTree<T> result = split(root, key);
    Node<T>* new_root = new Node<T>(key, result.left, result.right);
    keep_parent(new_root);
    update_info(new_root);
    return new_root;
}

template <typename T>
Node<T>* SplayTree<T>::merge(Node<T>* left, Node<T>* right) {
    if (!left) {
        return right;
    }
    if (!right) {
        return left;
    }
    Node<T>* max_left = max_in_subtree(left);
    left = splay(max_left);
    left->right = right;
    right->parent = left;
    update_info(left);
    return left;
}

template <typename T>
Node<T>* SplayTree<T>::erase(Node<T>* root, T key) {
    root = find_by_key(root, key);
    if (!root || root->key != key) {
        return root;
    }
    set_parent(root->left, nullptr);
    set_parent(root->right, nullptr);
    Node<T>* left = root->left;
    Node<T>* right = root->right;
    delete root;
    return merge(left, right);
}

template <typename T>
Node<T>* SplayTree<T>::min_in_subtree(Node<T>* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

template <typename T>
Node<T>* SplayTree<T>::max_in_subtree(Node<T>* node) {
    while (node && node->right) {
        node = node->right;
    }
    return node;
}

template <typename T>
Node<T>* SplayTree<T>::find_by_id(Node<T>* node, int id) {
    if (!node) {
        return nullptr;
    }
    int left_subtree_size = get_subtree_size(node->left);
    if (id == left_subtree_size) {
        return node;
    } else if (id < left_subtree_size) {
        return find_by_id(node->left, id);
    } else {
        return find_by_id(node->right, id - left_subtree_size - 1);
    }
}

template <typename T>
void SplayTree<T>::insert(T key) {
    root = insert(root, key);
}

template <typename T>
void SplayTree<T>::erase(T key) {
    root = erase(root, key);
}

template <typename T>
bool SplayTree<T>::contains(T key) {
    root = find_by_key(root, key);
    return root && root->key == key;
}

template <typename T>
int SplayTree<T>::find_by_key(T key) {
    root = find_by_key(root, key);
    if (!root || root->key != key) {
        return -1;
    }
    return get_rank(root);
}

template <typename T>
T SplayTree<T>::find_by_id(int id) {
    if (id < 0 || id >= get_subtree_size(root)) {
        return T();
    }
    Node<T>* node = find_by_id(root, id);
    root = splay(node);
    return node->key;
}

template <typename T>
T SplayTree<T>::floor(T key) {
    if (!root) {
        return T();
    }
    root = find_by_key(root, key);
    if (root->key <= key) {
        return root->key;
    }
    Node<T>* node = max_in_subtree(root->left);
    if (!node) {
        return T();
    }
    root = splay(node);
    return node->key;
}

template <typename T>
T SplayTree<T>::ceiling(T key) {
    if (!root) {
        return T();
    }
    root = find_by_key(root, key);
    if (root->key >= key) {
        return root->key;
    }
    Node<T>* node = min_in_subtree(root->right);
    if (!node) {
        return T();
    }
    root = splay(node);
    return node->key;
}