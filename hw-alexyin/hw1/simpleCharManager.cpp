#include <cstddef>
#include "simpleCharManager.h"


simpleCharManager::simpleCharManager(){
  for(int i=0; i<BUF_SIZE;i++){
    buffer[i] = '\0';
  }
}

simpleCharManager::~simpleCharManager(){
}
             
char* simpleCharManager::alloc_chars(int n){  //does not handle when there are not n available addresses 
  int firstopenspot=0;
  while(buffer[firstopenspot]!='\0' && firstopenspot<BUF_SIZE){
    firstopenspot++;
  }
  if(firstopenspot<BUF_SIZE){
  free_place = &buffer[firstopenspot];
  }
  return free_place;
}

void simpleCharManager::free_chars(char* p){
  int pindex = 0;
  while(pindex<BUF_SIZE){
    if(p == &buffer[pindex]){
      break;
    }
    pindex++;
  }
  if(pindex<BUF_SIZE){
    for(int i=pindex; i<BUF_SIZE; i++){
      buffer[i] = '\0';
      p[i-pindex] = '\0';
    }
  }
}         



