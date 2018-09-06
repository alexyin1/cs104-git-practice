#include <iostream>
#include <stdlib.h>
#include "flexCharManager.h"
using namespace std;

int main(int argc, char *argv[])
{
  flexCharManager flex_mem_manager;

/*replace with driver code as specificed in the assignment*/
  char* c1 = flex_mem_manager.alloc_chars(2);
  c1[0] = 'h';
  c1[1] = 'y';
  char* c2 = flex_mem_manager.alloc_chars(3);
  cout << c1[0] << c1[1] << endl;
  flex_mem_manager.free_chars(c1);  
  
  return 0;
}

