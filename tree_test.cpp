#include "AVL.h"
#include <iostream>

int main() {
  AVL<int>* avl = new AVL<int>();

  avl->insert(6);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(4);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(9);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(2);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(5);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(8);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(10);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(7);
  avl->treePrint();
  std::cout << "\n";
  avl->remove(10);
  avl->treePrint();
  std::cout << "\n";


}
