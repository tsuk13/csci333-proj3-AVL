#include "AVL.h"
#include <iostream>

int main() {
  AVL<int>* avl = new AVL<int>();

  avl->insert(3);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(1);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(5);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(2);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(4);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(6);
  avl->treePrint();
  std::cout << "\n";
  avl->insert(7);
  avl->treePrint();
  std::cout << "\n";
  avl->remove(5);
  std::cout << "made it through remove\n";
  avl->treePrint();
  std::cout << "\n";


}
