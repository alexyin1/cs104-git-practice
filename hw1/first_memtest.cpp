#include <iostream>
#include <stdlib.h>
#include "simpleCharManager.h"
using namespace std;

int main(int argc, char *argv[])
{
  simpleCharManager simplest_mem_manager;

  /*write driver code as described in the assignment to replace this */
  char* c1 = simplest_mem_manager.alloc_chars(2);
  c1[0] = 'h';
  c1[1] = 'y';
  char* c2 = simplest_mem_manager.alloc_chars(3);
  cout << c1[0] << c1[1] << endl;
  simplest_mem_manager.free_chars(c1);  
  return 0;
}

