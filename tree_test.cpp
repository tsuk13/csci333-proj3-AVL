#include "AVL.h"
#include <iostream>

int main() {
  AVL<int>* avl = new AVL<int>();

  avl->insert(5);
  avl->insert(3);
  avl->insert(2);
  avl->insert(4);
  avl->insert(7);
  avl->print();
  std::cout << "\n";
  avl->treePrint();
  avl->remove(5);
  avl->remove(4);
  avl->print();
  std::cout <<"\n";
  avl->treePrint();


}
