#ifndef __AVL_H__
#define __AVL_H__

#include "Node.h"
#include <string>

template <typename T>
class AVL {
 private:
  Node<T>* root;
  void traversalPrint(Node<T>* root);
  int depth(Node<T>* r, int curDepth);
  int twoPow(int x);

 public:
  AVL<T>();
  ~AVL<T>();

  void treePrint();
  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
};


#endif
