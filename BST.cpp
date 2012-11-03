#include "BST.h"
#include <iostream>
#include <list>
using std::list;

template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  
}


template <typename T>
bool BST<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void BST<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>** curr = &root;

  while (*curr != 0) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
  }
  *curr = temp;
}

template <typename T>
void BST<T>::remove(T v) {
  //find the nodeToRemove
  Node<T>** nodeToRemove = &(root);
  while((*nodeToRemove) != 0 && (*nodeToRemove)->getValue() != v){
    if(v < (*nodeToRemove)->getValue())
      nodeToRemove = &((*nodeToRemove)->getLeftChild());
    else if(v > (*nodeToRemove)->getValue())
      nodeToRemove = &((*nodeToRemove)->getRightChild());
  }
  //case nodetoRemove is not present
  if((*nodeToRemove) == 0){
    return;
  }
  //keep a pointer to nodeToRemove for deletion
  Node<T>* tmp = (*nodeToRemove);
  //case for no left child
  if((*nodeToRemove)->getLeftChild() == 0){
    (*nodeToRemove) = (*nodeToRemove)->getRightChild();
    delete tmp;
    return;
  }
  //case for no right child
  else if((*nodeToRemove)->getRightChild() == 0){
    (*nodeToRemove) = (*nodeToRemove)->getLeftChild();
    delete tmp;
    return;
  }
  //case two childs
  //find in order predessesor
  Node<T>* IOP = (*nodeToRemove)->getLeftChild();
  while(IOP->getRightChild() != 0){
    IOP = IOP->getRightChild();
  }
  //IOP's right subtree becomes what nodeToRemoves was
  IOP->setRightChild(*((*nodeToRemove)->getRightChild()));
  //nodeToRemove's parent pointer gets set to nodeToRemoves leftChild
  (*nodeToRemove) = (*nodeToRemove)->getLeftChild();
  //nodeToRemove is deleted
  delete tmp;
}

template <typename T>
void BST<T>::print() {
  traversalPrint(root);
}

template <typename T>
void BST<T>::treePrint(){
  int size = depth(root, 0);
  list<Node<T>*>** alNode = new list<Node<T>*>*[size];
  for(int i = 0; i < size; i++){
    alNode[i] = new list<Node<T>*>();
  }
  list<Node<T>*>* q = new list<Node<T>*>();
  list<int>* l = new list<int>();
  //store it all
  q->push_back(root);
  l->push_back(0);
  for(int curLevel = l->front(); curLevel < size; curLevel = l->front()){
    l->pop_front();
    Node<T>* curNode = (Node<T>*) q->front();
    q->pop_front();
    alNode[curLevel]->push_back(curNode);
    if( curNode == 0){
      q->push_back(curNode);
      q->push_back(curNode);
    }
    else {
      q->push_back(curNode->getLeftChild());
      q->push_back(curNode->getRightChild());
    }
    l->push_back(curLevel + 1);
    l->push_back(curLevel + 1);
  }
  //print
  for(int i = 0; i < size; i++){
    for(int j = 0; j < twoPow(size - i - 1) - 1; j++)
      std::cout << " ";
    while(!alNode[i]->empty()){
      if(alNode[i]->front() == 0)
        std::cout << "X";
      else
        std::cout << alNode[i]->front()->getValue();
      for(int j = 0; j < twoPow(size - i) - 1; j++)
        std::cout << " ";
      alNode[i]->pop_front();
    }
    std::cout << "\n";
  }
}

template <typename T>
int BST<T>::depth(Node<T>* r, int curDepth){
  if(r == 0)
    return curDepth;
  int lc = depth(r->getLeftChild(), curDepth + 1);
  int rc = depth(r->getRightChild(), curDepth + 1);
  if(rc >= lc)
    return rc;
  else
    return lc;
}

template <typename T>
int BST<T>::twoPow(int x){
  if(x == 0)
    return 1;
  else
    return 2 * twoPow(x - 1);
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
