#include <cstddef>
#include "simpleCharManager.h"


simpleCharManager::simpleCharManager(){
  for(int i=0; i<BUF_SIZE;i++){
    buffer[i] = '\0';
  }
}

simpleCharManager::~simpleCharManager(){
}
             
char* simpleCharManager::alloc_chars(int n){  
  int firstopenspot=0;
  while(buffer[firstopenspot]!='\0' && firstopenspot<BUF_SIZE){
    firstopenspot++;
  }
  if(firstopenspot+n<BUF_SIZE){
    free_place = &buffer[firstopenspot];
  }
  else{
    free_place=NULL;
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



