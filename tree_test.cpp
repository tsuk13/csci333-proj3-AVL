#include "BST.h"
#include <iostream>

int main() {
  BST<int>* bst = new BST<int>();

  bst->insert(5);
  bst->insert(3);
  bst->insert(2);
  bst->insert(4);
  bst->insert(7);
  bst->print();
  std::cout << "\n";
  bst->treePrint();
  bst->remove(5);
  bst->remove(4);
  bst->print();
  std::cout <<"\n";
  bst->treePrint();


}
