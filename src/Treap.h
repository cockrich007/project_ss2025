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

   void insert(T key);
   void erase(T key);
   bool contains(T key);
   T find_by_id(int id);
   // int find_by_key(T key);
   T floor(T key);
   T ceiling(T key);
};

#include "Treap.cpp"