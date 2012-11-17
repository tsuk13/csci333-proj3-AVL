#include "AVL.h"
#include <iostream>
#include <list>
using std::list;

template <typename T>
AVL<T>::AVL() {
  root = 0;
}

template <typename T>
AVL<T>::~AVL() {
  
}


template <typename T>
bool AVL<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void AVL<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>** curr = &root;
  list<Node<T>**> nodeStack; //keeps track of node path
  list<int> dirStack; //keeps track of directions of the path

  //main insert
  while (*curr != 0) {
    nodeStack.push_front(curr);
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
      dirStack.push_front(-1);
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
      dirStack.push_front(1);
    }
  }
  *curr = temp;

  //balance updating
  int prevDir = 0;
  while(!nodeStack.empty()){
    Node<T>** nUp = nodeStack.front();
    int dir = dirStack.front();
    if((*nUp)->getBalance() == 0)
      break;
    //balance hits 2
    else if((*nUp)->getBalance() == 2){
       if(prevDir != -1){ //outside insert
         rotate(nUp, -1);
         break;
       }
       else{              //inside insert
         rotate(&((*nUp)->getRightChild()), 1);
         rotate(nUp, -1);
         break;
       }
    }
    //balance hits -2
    else if((*nUp)->getBalance() == -2){
       if(prevDir != 1){ //outside insert
         rotate(nUp, 1);
         break;
       }
       else{              //inside insert
         rotate(&((*nUp)->getLeftChild()), -1);
         rotate(nUp, 1);
         break;
       }
    }
    (*nUp)->setHeight((*nUp)->getHeight()+1);
    prevDir = dir;
    nodeStack.pop_front();
    dirStack.pop_front();
  }
}

template <typename T>
void AVL<T>::remove(T v) {
  list<Node<T>**> nStack;
  list<int> dirStack;
  //find the nodeToRemove
  Node<T>** nodeToRemove = &(root);
  nStack.push_front(nodeToRemove);
  while((*nodeToRemove) != 0 && (*nodeToRemove)->getValue() != v){
    if(v < (*nodeToRemove)->getValue()){
      nodeToRemove = &((*nodeToRemove)->getLeftChild());
      dirStack.push_front(-1);
    }
    else if(v > (*nodeToRemove)->getValue()){
      nodeToRemove = &((*nodeToRemove)->getRightChild());
      dirStack.push_front(1);
    }
    nStack.push_front(nodeToRemove);
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
    dirStack.push_front(1);
    delete tmp;
  }
  //case for no right child
  else if((*nodeToRemove)->getRightChild() == 0){
    (*nodeToRemove) = (*nodeToRemove)->getLeftChild();
    dirStack.push_front(-1);
    delete tmp;
  }
  //case two childs
  //find in order predessesor
  else{
    Node<T>** IOP = &((*nodeToRemove)->getLeftChild());
    nStack.push_front(IOP);
    dirStack.push_front(-1);
    while((*IOP)->getRightChild() != 0){
      IOP = &((*IOP)->getRightChild());
      nStack.push_front(IOP);
      dirStack.push_front(1);
    }
    //IOP's right subtree becomes what nodeToRemoves was
    (*IOP)->setRightChild(*((*nodeToRemove)->getRightChild()));
    //IOP's left subtree becomes what nodeToRemoves was
    Node<T>* tmplc = (*IOP)->getLeftChild();
    (*IOP)->setLeftChild(*((*nodeToRemove)->getLeftChild()));
    //NodeTO REmove's parent pointer gets set to IOP 
    (*nodeToRemove) = (*IOP);
    //IOP's parent points to IOP LeftChild
    (*IOP) = tmplc;
    //nodeToRemove is deleted
    delete tmp;
    //update balance
  }
  while(!nStack.empty()){
    Node<T>** curN = nStack.front();
    int dir = dirStack.front();
    if((*curN) == 0){
      nStack.pop_front();
    }
    else{
      fixHeight(*curN);
      if((*curN)->getBalance() == 2){
        if(dir == -1){
          rotate(curN, -1);
        }
        else{
          rotate(&((*curN)->getRightChild()), 1);
          rotate(curN, -1);
        }
      }
      else if((*curN)->getBalance() == -2){
        if(dir == 1){
          rotate(curN, 1);
        }
        else{
          rotate(&((*curN)->getLeftChild()), -1);
          rotate(curN, 1);
        }
      }
      nStack.pop_front();
      dirStack.pop_front();
    }
  }
}

template <typename T>
void AVL<T>::print() {
  traversalPrint(root);
}

template <typename T>
void AVL<T>::treePrint(){
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
int AVL<T>::depth(Node<T>* r, int curDepth){
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
int AVL<T>::twoPow(int x){
  if(x == 0)
    return 1;
  else
    return 2 * twoPow(x - 1);
}

template <typename T>
void AVL<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template <typename T>
void AVL<T>::rotate(Node<T>** crit, int dir){
  if(dir == -1){
    Node<T>* tmpRC = (*crit)->getRightChild();
    Node<T>* tmpLC = tmpRC->getLeftChild();
    tmpRC->setLeftChild(*(*crit));
    (*crit) = tmpRC;
    tmpRC->getLeftChild()->setRightChild(*tmpLC);
    //update heights
    fixHeight(tmpRC->getLeftChild());
    fixHeight(tmpRC);
  }
  else if(dir == 1){
    Node<T>* tmpLC = (*crit)->getLeftChild();
    Node<T>* tmpRC = tmpLC->getRightChild();
    tmpLC->setRightChild(*(*crit));
    (*crit) = tmpLC;
    tmpLC->getRightChild()->setLeftChild(*tmpRC);
    //update heights
    fixHeight(tmpLC->getRightChild());
    fixHeight(tmpLC);
  }
  else{
    std::cout << "An error has occured with direction in rotate\n";
  }
}

template <typename T>
void AVL<T>::fixHeight(Node<T>* n){
  if(n == 0)
    return;
  int leftH = 0;
  int rightH = 0;
  if(n->getLeftChild() != 0)
    leftH = n->getLeftChild()->getHeight();
  if(n->getRightChild() != 0)
    rightH = n->getRightChild()->getHeight();
  if (leftH > rightH)
    n->setHeight(leftH + 1);
  else
    n->setHeight(rightH + 1);
}

template class AVL<int>;
template class AVL<double>;
template class AVL<std::string>;
