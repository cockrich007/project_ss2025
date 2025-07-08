#include <RBTree.h>
#include <limits>
#include <iostream>

NodeInt::NodeInt() {
    int value = 0;
    int height;
    bool color;
    l = r = nullptr;
    this->parent = nullptr;
    height = 1;
}

NodeInt::NodeInt(int value, bool color = true) {
    this->value = value;
    int height;
    bool color;
    l = r = nullptr;
    this->parent = nullptr;
    height = 1;
}

NodeInt::NodeInt(int value, NodeInt* l, NodeInt* r, bool color = true) {
    this->value = value;
    int height;
    bool color;
    this->l = l;
    this->r = r;
    this->parent = nullptr;
    height = 1 + std::max(l->height, r->height);
}

NodeInt::~NodeInt() {
    delete l;
    delete r;
}

RBTree::RBTree() {
	root = nullptr;
    root->color = false;
	size = 0;
}

RBTree::RBTree(int value) {
	root = new NodeInt(value);
    root->color = false;
	size = 1;
}

RBTree::RBTree(NodeInt* root) {
	this->root = root;
    root->color = false;
}

RBTree::~RBTree() {
	delete(root);
}

int RBTree::getHeight(NodeInt* node) {
    return node ? node->height : 0;
}

int RBTree::height() {
    return getHeight(root);
}

void RBTree::updateHeight(NodeInt* node) {
    if (node) {
        node->height = 1 + std::max(getHeight(node->l), getHeight(node->r));
    }
}

int pos;

int RBTree::find_by_pos(int index, NodeInt* curr_node) {
    int buffer;
    if (curr_node->l != nullptr) {
        if ((buffer = find_by_pos(index, curr_node->l)) != std::numeric_limits<int>::max()) {
            return buffer;
        }
    }
    if (pos == index) {
        return curr_node->value;
    }
    pos += 1;
    if (curr_node->r != nullptr) {
        if ((buffer = find_by_pos(index, curr_node->r)) != std::numeric_limits<int>::max()) {
            return buffer;
        }
    }
    return std::numeric_limits<int>::max();
}

int RBTree::select(int index) {
    pos = 0;
    if (root == nullptr) {
        return std::numeric_limits<int>::max();
    }
    return find_by_pos(index, root);
}

void RBTree::flipColors(NodeInt* node) {
    if (node != root) {
        node->color = !node->color;
    }
    node->l->color = !node->color;
    node->r->color = !node->color;
}

void RBTree::set_parents(NodeInt* curr_node) {
    if (curr_node->l != nullptr) {
        curr_node->l->parent = curr_node;
    }
    if (curr_node->r != nullptr) {
        curr_node->r->parent = curr_node;
    }
}

void RBTree::rightRotate(NodeInt* node) {
    NodeInt* l_child = node->l;
    node->r = l_child->r;
    l_child->r = node;
    set_parents(l_child);
    set_parents(l_child->parent);
}

void RBTree::leftRotate(NodeInt* node) {
    NodeInt* r_child = node->r;
    node->r = r_child->l;
    r_child->l = node;
    set_parents(r_child);
    set_parents(r_child->parent);
}

void RBTree::rightleftRotate(NodeInt* node) {

}

void RBTree::leftrightRotate(NodeInt* node) {

}