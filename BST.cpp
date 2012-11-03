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
  bool slashRound = false;
  bool slashForward = true;
  list<Node<T>*>* tmp;
  for(int i = 1; (i/2) < size; i++){
    if(slashRound)
      tmp = new list<Node<T>*>();  //used to keep the stuff
    for(int j = 0; j < twoPow(size - (i/2) - 1) - 1; j++) //make start spaces
      std::cout << " ";
    while(!alNode[i/2]->empty()){
      if(alNode[i/2]->front() == 0){  //if node is null
        if(slashRound){          //if the line being printed is the slash line
          std::cout << " ";
        }
        else{                    //if its the actual printing line
          std::cout << " ";
        }
      }
      else{                      //if the node exists
        if(slashRound){          //if its the slash round
          if(slashForward)       //if its a foward slash
            std::cout << "/";
          else                   //if its a backslash
            std::cout << "\\";   
        }
        else{
          std::cout << alNode[i/2]->front()->getValue();
        }
      }
      if(slashRound)
        slashForward = !slashForward; // change for the next slash
      for(int j = 0; (j < twoPow(size - (i/2)) - 1); j++)   //spaces for inbet
        std::cout << " ";
      if(slashRound)
        tmp->push_back(alNode[i/2]->front());
      alNode[i/2]->pop_front();  //pop front
    }
    std::cout << "\n";
  if(slashRound)
     alNode[i/2] = tmp;
  slashRound = !slashRound;
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
