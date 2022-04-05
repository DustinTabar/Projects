#pragma once

#include "PCB.h"

/**
 * ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue here uch that the process with the highest priority
 * can be selected next.
 */

 //BST inplementation of ReadyQueue
class ReadyQueue {
private:
  //BST root
  PCB *root;

  //Recursive helper functions
  int size(PCB*);
  void display(PCB*);
  PCB* addPCB(PCB*, PCB*, PCB*);

  //helper function for removePCB()
  PCB* findHighest();

  //used by the destructor
  void destroyAllPCB(PCB*);

public:
  // Constructor
  ReadyQueue();

	// add a PCB representing a process into the ready queue.
	void addPCB(int, unsigned int);

	// remove and return the PCB with the highest priority from the queue
	PCB* removePCB();

	// Returns the number of elements in the queue.
	int size();

	// Prints the queue contents to standard output.
	void display();

  //destructor
  ~ReadyQueue();
};
