#include "flexCharManager.h"

simpleCharManager::simpleCharManager(){
  for(int i=0; i<BUF_SIZE;i++){
    buffer[i] = '\0';
  }
}

simpleCharManager::~simpleCharManager(){
}

flexCharManager::flexCharManager(){ 
  free_mem = BUF_SIZE;
  active_requests = 0;
  usable_mem_size = 2;    // usable more readible to me
  
  used_memory = NULL;
  used_memory = new Mem_Block*[usable_mem_size];
  for(int j=0; j<active_requests+usable_mem_size; j++){
    used_memory[j] = NULL;
  }
}

flexCharManager::~flexCharManager(){
  for(int j=0; j<active_requests; j++){
    delete []used_memory[j];
  }
  delete[] used_memory;
}
             
char* flexCharManager::alloc_chars(int n){
  int firstopenspot=0;
  if(n<=free_mem){ //if there is space in buffer
    if(usable_mem_size==0){   //if memblock has space
      Mem_Block **temp = NULL;
      temp = new Mem_Block*[active_requests];  
      for(int j=0; j<active_requests; j++){
        temp[j] = new Mem_Block(used_memory[j]->size, used_memory[j]->physical_location);
      }
      for(int j=0; j<active_requests; j++){
        delete []used_memory[j];
      } 
      used_memory = new Mem_Block*[active_requests*2];
      for(int i=0; i<active_requests;i++){
        used_memory[i] = new Mem_Block(temp[i]->size, temp[i]->physical_location);  
      } 
      for(int j=active_requests; j<active_requests*2;j++){
        used_memory[j] = NULL;
      }
      delete []temp;
      for(int j=0; j<active_requests; j++){
        delete []temp[j];
      }
    //adjust global
    usable_mem_size = active_requests;      
    }
   firstopenspot = BUF_SIZE-free_mem;      
   free_place = &buffer[firstopenspot];
   used_memory[active_requests] = new Mem_Block(n,&buffer[firstopenspot]);   
   active_requests++;
   usable_mem_size--;
   free_mem = free_mem-n;   
  }

  return free_place;
}

void flexCharManager::free_chars(char* p){

}         


