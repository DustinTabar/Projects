#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <iomanip>
#include "ReadyQueue.h"

int main(int argc, char* argv[]) {
	//Print basic information about the program
	std::cout << "CS 433 Programming assignment 1" << std::endl;
	std::cout << "Author: Dustin Tabar and Matt Warren" << std::endl;
	std::cout << "Date: 09/22/2021" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description : Program to implement a priority ready queue of processes" << std::endl;
	std::cout << "=================================" << std::endl;

	//Test 1
	std::cout << "Performing Test 1..." << std::endl << std::endl;
  
  ReadyQueue q1;

  //add processes 15, 6, 23, 39 and 8 to 𝑞1. Display the content of 𝑞1
  std::cout << "Adding PCBs 15, 6, 23, 39, 8 into the ReadyQueue" << std::endl;
  q1.addPCB(15,15);
  q1.addPCB(6,6);
  q1.addPCB(23,23);
  q1.addPCB(39,39);
  q1.addPCB(8,8);
  q1.display();
  std::cout << std::endl;

  //remove the process with the highest priority from 𝑞1 and display 𝑞1
  std::cout << "Removing highest priority PCB from the ReadyQueue" << std::endl;
  q1.removePCB();
  q1.display();
  std::cout << std::endl;

  //add processes 47, 1, 37 and 5 into 𝑞1, and display 𝑞1
  std::cout << "Adding PCBs 47, 1, 37, 5 into the ReadyQueue" << std::endl;
  q1.addPCB(47,47);
  q1.addPCB(1,1);
  q1.addPCB(37,37);
  q1.addPCB(5,5);
  q1.display();
  std::cout << std::endl;

  //remove the process with the highest priority from 𝑞1 and display 𝑞1
  std::cout << "Removing highest priority PCB from the ReadyQueue" << std::endl;
  q1.removePCB();
  q1.display();
  std::cout << std::endl;

  //add processes 43, 17, 32, 12 and 19 to 𝑞1 and display 𝑞1
  std::cout << "Adding PCBs 43, 17, 32, 12, 19 into the ReadyQueue" << std::endl;
  q1.addPCB(43,43);
  q1.addPCB(17,17);
  q1.addPCB(32,32);
  q1.addPCB(12,12);
  q1.addPCB(19,19);
  q1.display();
  std::cout << std::endl;

  //One by one remove the process with the highest priority from the queue 𝑞1 and
  //display the queue after each removal
  std::cout << "Removing all PCBs from the ReadyQueue one at a time" << std::endl;

  while(q1.size() > 0) {
    q1.removePCB();
    q1.display();
    std::cout << std::endl;
  }
  std::cout << std::endl;

	//Test 2
	std::cout << "Performing Test 2..." << std::endl << std::endl;

  clock_t start, end;

  ReadyQueue q2;
  int randomNum, inOrOut, i;
  srand(time(NULL)); //seed

  for (i = 1; i <= 100; i++) { //initial 100 PCBs in ReadyQueue
    randomNum = rand() % 50 + 1; //generate random number between 1-50
    q2.addPCB(i, randomNum);
  }

  start = clock(); //timer start

  for (int j = 0; j < 1000000; j++) { //iterate one million times
    inOrOut = rand() % 2;
    if (inOrOut == 0) {
      q2.removePCB();
    }
    else {
      randomNum = rand() % 50 + 1;
      q2.addPCB(++i, randomNum);
    }
  }

  end = clock(); //timer end
  double time = double(end-start)/double(CLOCKS_PER_SEC); //calculation for clock speed

  q2.display();
  std::cout << std::endl << "Execution time: " << std::fixed << time << std::setprecision(5) << " secs" << std::endl;
}