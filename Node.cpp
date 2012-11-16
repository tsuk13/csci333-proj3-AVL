#include <string>
#include "Node.h"

template <typename T>
Node<T>::Node(T v) {
  value = v;
  height = 1;
  leftChild = 0;
  rightChild = 0;
}

template <typename T>
T Node<T>::getValue() {
  return value;
}

template <typename T>
Node<T>*& Node<T>::getLeftChild() {
  return leftChild;
}

template <typename T>
void Node<T>::setLeftChild(Node<T>& lc) {
  leftChild = &lc;
}

template <typename T>
Node<T>*& Node<T>::getRightChild() {
  return rightChild;
}

template <typename T>
void Node<T>::setRightChild(Node<T>& rc) {
  rightChild = &rc;
}

template <typename T>
int Node<T>::getBalance(){
  int rightH;
  int leftH;
  if(rightChild == 0)
    rightH = 0;
  else
    rightH = rightChild->getHeight();
  if(leftChild == 0)
    leftH = 0;
  else
    leftH = leftChild->getHeight();
  return rightH - leftH;
}

template <typename T>
int Node<T>::getHeight(){
  return height;
}

template <typename T>
void Node<T>::setHeight(int h){
  height = h;
}

template class Node<int>;
template class Node<double>;
template class Node<std::string>;

