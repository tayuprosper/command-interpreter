#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <assert.h>
#include <sys/wait.h>
int execute(std::vector<std::string> command)
{
  int pipefd[2];      //file decriptors for sharing data between parent and child
  assert((pipefd));   // assert pipe to make sure it is created successfully
  pid_t pid = fork();   //create child process to handle executoin of commands

  if (pid == 0)
  {

    // close(pipefd[0]);       //prevent child from reading
    // dup2(pipefd[1], STDOUT_FILENO);    //redirect all write to STDOUT to the pipe instead
    // close(pipefd[1]);

    std::vector<char *> tokens;

    for (auto &str : command)
    {
      tokens.push_back((char *)str.c_str());
    }

    tokens.push_back(nullptr);

    execvp(tokens[0], tokens.data());
    std::cout << "child is done\n";
    std::cout.flush();
    perror("execvp failled");
    exit(0);
  }
  wait(0);
  return 0;
}