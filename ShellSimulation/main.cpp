#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <cctype>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 80                                 //maximum length command

int main() {
  //Print basic information about the program
	std::cout << "CS 433 Programming assignment 2" << std::endl;
	std::cout << "Author: Dustin Tabar and Matt Warren" << std::endl;
	std::cout << "Date: 10/15/2021" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description : Program to simulate a shell interface" << std::endl;
	std::cout << "=================================" << std::endl;
  
  char *args[MAX_LINE / 2 + 1];                    //command line arguments
  bool shouldRun = true;                           //flag to exit program
  bool shouldWait = true;                          //flag if parent waits for child
  char redirectCh;
  std::string fileName;
  std::string CMD, prevCMD = "empty";
  int i, status, in_fd, out_fd, redirectPos = -1;
  pid_t pid;
  int child_status;                               //used in waitpid()

  while (shouldRun) {
    std::cout << "osh>";

    getline(std::cin, CMD);                       //read user command
    /*for (int j = 0; j < CMD.length(); j++) {      //convert command to lowercase
      CMD[j] = tolower(CMD[j]);
    }*/

    if (CMD == "!!") {
      if (prevCMD == "empty") {                  //no command in history
        std::cout << "no commands in history" << std::endl;
        continue;
      }
      else {                                     //succsessful use of history feature
        CMD = prevCMD;
      }
    }
    else {
      prevCMD = CMD;                             //update previous command for history
    }

    if (CMD == "exit") {                         //check if user is exiting
      shouldRun = false;
      break;
    }

    i = 0;                                       //reset i to overwrite args
    args[i] = strtok(&CMD[0], " ");              //split command into tokens
    while (args[i] != NULL) {
      i++;
      args[i] = strtok(NULL, " ");
      if (args[i] != NULL) {
        if (args[i][0] == '<' || args[i][0] == '>') { //check for redirect
          redirectPos = i;
          redirectCh = args[i][0];
        }
      }
    }

    if (i > 0 && args[i - 1][0] == '&') {        //check for & to flag should wait
      shouldWait = false;
      args[i - 1] = NULL;
    }

    if (redirectPos != -1) {                    //if there is a redirect, truncate cmd
      fileName = args[redirectPos + 1];         
      args[redirectPos] = NULL;
    }

    pid = fork();                                //create child process

    if (pid < 0) {                               //check if child fails to create
      std::cout << "fork failed" << std::endl;
    }
    else if (pid == 0) {                         //child successful
      if (redirectCh == '<') {                   //input redirect
        int stdin_copy;
        in_fd = open(fileName.c_str(), O_RDONLY);
        if (in_fd == -1) {
          std::cout << "no such file or directory" << std::endl;
          exit(0);
        }
        stdin_copy = dup(0);
        dup2(in_fd, 0);
        status = execvp(args[0], args);
        close(in_fd);
        dup2(stdin_copy, 0);
        close(stdin_copy);

        if (status == -1) {                      //check for invalid command
          std::cout << "command not found" << std::endl;
        }
        exit(0);
      }
      else if (redirectCh == '>') {              //output redirect
        int stdout_copy;
        out_fd = open(fileName.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP);
        stdout_copy = dup(1);
        dup2(out_fd, 1);
        status = execvp(args[0], args);
        close(out_fd);
        dup2(stdout_copy, 1);
        close(stdout_copy);
        if (status == -1) {                      //check for invalid command
          std::cout << "command not found" << std::endl;
        }
        exit(0);
      }
      else {                                     //no redirect
        status = execvp(args[0], args);
        if (status == -1) {                      //check for invalid command
          std::cout << "command not found" << std::endl;
        }
        exit(0);
      }
    }
    else if (shouldWait) {                      //check if parent should wait
      waitpid(pid, &child_status, 0);   
    }
    redirectCh = '\0';                          //reset conditions for
    redirectPos = -1;                           //next iteration of loop
    shouldWait = true;
  }
  return 0;
}