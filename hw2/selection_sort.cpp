#include <cstddef>
#include "selection_sort.h"
#include <iostream>
using namespace std;
        
Item* findMin(Item * head){
  if(head!=nullptr){
    Item* min = head;
    Item* iter = head; 
    while(iter->next != nullptr){
      iter = iter->next;
      if(min->getValue() > iter->getValue()){
        min = iter;  
      }
    }
    return min;
  }
  return nullptr; 
}

void movefront(Item*& front, Item*& element, Item*& head){
  Item* etemp = element;
  if(front == element){  //if the pointers point to the same item
    return;
  }
  else{
    //adjust element's neighboring nodes
    if(element->prev!=nullptr){
      element->prev->next = element->next;
    }
    if(element->next!=nullptr){
      element->next->prev = element->prev;
    }
    //if front and element are neighboring, front->next needs to be adjusted, otherwise not needed
    if(front->next == element){
      front->next = element->next;
    }
    element->next = front;
    element->prev = front->prev;
    if(front->prev!=nullptr){
      front->prev->next = element;
    }
    front->prev = element;
    if(front == head){
      head = element;
    }
  }
}

// Sorts the given list in ascending order and returns the new head.
// Returns nullptr iff head is nullptr.
Item* LLSelectionSort(Item * head){
  Item* iter = head;
  if(head!=nullptr){
    while(iter!=nullptr){
      Item* temp = findMin(iter);
      if(iter == temp){
        iter = iter->next;
      }
      else{
        movefront(iter, temp, head);
      }
    }
  }
  return head;
}

