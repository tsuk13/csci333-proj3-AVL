#include "BST.h"
#include <iostream>

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
  traversalPrint(root);
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
