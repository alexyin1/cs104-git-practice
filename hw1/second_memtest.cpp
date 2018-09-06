#include <iostream>
#include <stdlib.h>
#include "flexCharManager.h"
using namespace std;

int main(int argc, char *argv[])
{
  //flexCharManager flex_mem_manager;

/*replace with driver code as specificed in the assignment*/
 
  flexCharManager simplest_mem_manager;

  /*write driver code as described in the assignment to replace this */
  char* c1 = simplest_mem_manager.alloc_chars(1);
  c1[0] = 'H';
  char* c2 = simplest_mem_manager.alloc_chars(1);
  c2[0] = 'e';
  char* c3 = simplest_mem_manager.alloc_chars(1);
  c3[0] = 'l';
  char* c4 = simplest_mem_manager.alloc_chars(1);
  c4[0] = 'l';
  char* c5 = simplest_mem_manager.alloc_chars(1);
  c5[0] = 'o';
  char* c6 = simplest_mem_manager.alloc_chars(1);
  c6[0] = ' ';
  char* c7 = simplest_mem_manager.alloc_chars(1);
  c7[0] = 'w';
  char* c8 = simplest_mem_manager.alloc_chars(1);
  c8[0] = 'o';
  char* c9 = simplest_mem_manager.alloc_chars(1);
  c9[0] = 'r';
  char* c10 = simplest_mem_manager.alloc_chars(1);
  c10[0] = 'l';
  char* c11 = simplest_mem_manager.alloc_chars(1);
  c11[0] = 'd';
  char* c12 = simplest_mem_manager.alloc_chars(1);
  c12[0] = '!';
  char* c13 = simplest_mem_manager.alloc_chars(1);
  c13[0] = '\n';

  char* c14 = simplest_mem_manager.alloc_chars(1);
  c14[0] = 'm';
  char* c15 = simplest_mem_manager.alloc_chars(1);
  c15[0] = 'o';
  char* c16 = simplest_mem_manager.alloc_chars(1);
  c16[0] = 'o';
  char* c17 = simplest_mem_manager.alloc_chars(1);
  c17[0] = 'n';
  char* c18 = simplest_mem_manager.alloc_chars(1);
  c18[0] = '!';
  char* c19 = simplest_mem_manager.alloc_chars(1);
  c19[0] = ' ';
  char* c20 = simplest_mem_manager.alloc_chars(1);
  c20[0] = 'B';
  char* c21 = simplest_mem_manager.alloc_chars(1);
  c21[0] = 'y';
  char* c22 = simplest_mem_manager.alloc_chars(1);
  c22[0] = 'e';
  char* c23 = simplest_mem_manager.alloc_chars(1);
  c23[0] = '.';
  char* c24 = simplest_mem_manager.alloc_chars(1);
  c24[0] = '\n';

  cout<<c1[0]<<c2[0]<<c3[0]<<c4[0]<<c5[0]<<c6[0]<<c7[0]<<c8[0]<<c9[0]<<c10[0]<<c11[0]<<c12[0]<<c13[0]; 
 

  //slightly different than 1stmemtest, checks if the memblock array can decrease in size after deallocation
  simplest_mem_manager.free_chars(c4);  
  simplest_mem_manager.free_chars(c5);  
  simplest_mem_manager.free_chars(c6);  
  simplest_mem_manager.free_chars(c7);  
  simplest_mem_manager.free_chars(c8);  
  simplest_mem_manager.free_chars(c9);  
  simplest_mem_manager.free_chars(c10);  
  simplest_mem_manager.free_chars(c11);  
  simplest_mem_manager.free_chars(c12);  
  simplest_mem_manager.free_chars(c13);  
  simplest_mem_manager.free_chars(c14);  
  simplest_mem_manager.free_chars(c15);  
  simplest_mem_manager.free_chars(c16);  
  simplest_mem_manager.free_chars(c17);  
  simplest_mem_manager.free_chars(c18);    

  return 0;
}

