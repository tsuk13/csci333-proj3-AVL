#include "BST.h"

int main() {
  BST<int>* bst = new BST<int>();

  bst->insert(2);
  bst->insert(1);
  bst->insert(3);
  bst->insert(5);
  bst->insert(4);
  bst->print();
  bst->remove(3);
  bst->print();


}
