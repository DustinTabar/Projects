#include "PCB.h"

//Constructor for PCB with unique id and priority, starts in NEW state
PCB::PCB(int ID, unsigned int PRIORITY) {
  id = ID;
  priority = PRIORITY;
  state = ProcState::NEW;
  left = right = parent =nullptr;
}