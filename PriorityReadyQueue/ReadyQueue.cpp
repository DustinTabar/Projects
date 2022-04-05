#include <iostream>
#include "ReadyQueue.h"

ReadyQueue::ReadyQueue() {
  root = nullptr;
}

//recursive helper function
PCB* ReadyQueue::addPCB(PCB *pcbptr, PCB *curr, PCB *prev) {
  //base case
  if (curr == nullptr) {
    curr = pcbptr;
    curr->left = curr->right = nullptr;
    curr->parent = prev;
  }
  //recursive case
  else if (pcbptr->priority < curr->priority) {
    curr->left = addPCB(pcbptr, curr->left, curr);
  }
  else if (pcbptr->priority >= curr->priority) {
    curr->right = addPCB(pcbptr, curr->right, curr);
  }
  return curr;
}

void ReadyQueue::addPCB(int ID, unsigned int PRIORITY) {
  PCB *newPCB = new PCB(ID, PRIORITY);
  newPCB->state = ProcState::READY;
  root = addPCB(newPCB, root, nullptr); //calls recursive helper function
}

//finds the right most node
PCB* ReadyQueue::findHighest() {
  PCB *highest = root;
  while (highest->right != nullptr) {
    highest = highest->right;
  }
  return highest;
}

PCB* ReadyQueue::removePCB() {
  //queue is empty
  if (root == nullptr) {
    return nullptr;
  }
  //queue not empty
  PCB *highest = findHighest();
  PCB *temp = new PCB(highest->id, highest->priority);
  temp->state = ProcState::RUNNING;
  highest->state = ProcState::RUNNING;
  //highest priority PCB is the root
  if (highest == root) {
    //root with left child
    if (root->left != nullptr) {
      root = root->left;
      root->parent = nullptr;
    }
    //root with no children
    else {
      root = nullptr;
    }
  }
  //highest priority PCB is not the root
  else {
    //highest priority PCB has a left child
    if (highest->left != nullptr) {
      PCB *nextHighest = highest->left;
      highest->parent->right = nextHighest;
      nextHighest->parent = highest->parent;
    }
    //highest priority PCB is a leaf
    else {
      highest->parent->right = nullptr;
    }
  }
  delete highest;
  return temp;
}

//recursive helper function
int ReadyQueue::size(PCB *pcbptr) {
  //base case
  if (pcbptr == nullptr) {
    return 0;
  }
  //recursive case
  return (1 + size(pcbptr->left) + size(pcbptr->right));
}

int ReadyQueue::size() {
  return size(root); //calls recursive helper function
}

//recursive helper function
void ReadyQueue::display(PCB *pcbptr) {
  //base case
  if (pcbptr == nullptr) {
    return;
  }
  //recursive case, prints according to in-order traversal
  display(pcbptr->left);
  std::cout << "ID: " << pcbptr->id << " Priority: " << pcbptr->priority << std::endl;
  display(pcbptr->right);
}

void ReadyQueue::display() {
  if (this->size() == 0) {
    std::cout << "Queue is empty" << std::endl;
    return;
  }
  display(root);
}

//deletes all PCB objects
void ReadyQueue::destroyAllPCB(PCB *pcbptr) {
  if (pcbptr == nullptr)
    return;
  destroyAllPCB(pcbptr->left);  //release all PCBs in the left subtree
  destroyAllPCB(pcbptr->right); //release all PCBs in the right subtree
  delete pcbptr;
}

ReadyQueue::~ReadyQueue() {
  destroyAllPCB(root); //calls recursive helper function
}