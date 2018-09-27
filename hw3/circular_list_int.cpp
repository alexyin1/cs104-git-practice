#include "circular_list_int.h"
#include <cstdlib>
#include <iostream>
#include <string>

  CircularListInt::CircularListInt(){
  }

  // Destructor. Should delete all data allocated by the list. 
  CircularListInt::~CircularListInt(){
    while(head!=nullptr && this->count>0){ 
      Item* temp = nullptr; 
      temp = head->next; 
      delete head; 
      head = temp; 
      this->count = this->count-1; 
    }

  }

  CircularListInt::Item* CircularListInt::findItem(size_t index) const
  {
    index = (size_t)abs(index);
    Item *temp=nullptr;
    if(index >= this->count-1){//index = count-1 is the last index
      index = index%count;   //convert index=8 into 8%count, giving a usable number
    }  
    if(index == this->count-1){  //if top or pop is called O(1) runtime for find ensures O(1) for remove and get
      temp = head->prev;
    }
    else{
      temp = head;
      for(size_t i=0; i<index; i++){
        temp = temp->next;
      }
    }
    return temp;
  }
  

  int CircularListInt::get(size_t index) const
  {
    if(empty()){
      return 0;
    }
    else{
      return findItem(index)->value;
    }
  }

	// get length of list.
	size_t CircularListInt::size() const
  {
    return this->count;
  }


	// returns true iff the list is empty.
	bool CircularListInt::empty() const
  {
    if(this->count>0){
      return false;
    }
    return true;
  }

	// Inserts (a copy of) the given item at the end of list.
	void CircularListInt::push_back(int value) 
  {
    Item* thing = new Item(value);
    if(empty()){
      head = thing;
      head->prev = thing;
    } 
    else{
      thing->prev = head->prev;
      head->prev = thing;
      thing->next = head;
    }
    this->count = this->count+1;
  }

	// Sets the item at the given index to have the given value.
	// If an index is passed that is >= the number of items in the list, it should "wrap around" back to the first element.
	void CircularListInt::set(size_t index, int value) 
  {
    if(!empty()){
      findItem(index)->value = value;
    }
  }
  //how to adjust indexs after removal

	// Removes the item at the given index from the list.
	// List elements after the removed element are pulled forward, so their indicies decrease by one.
	// If an index is passed that is larger then the number of items in the list, it should "wrap around" back to the first element.
	void CircularListInt::remove(size_t index)
  {
    if(!empty()){
      if(this->count == 1){
        delete findItem(index); 
        this->count = this->count-1;
        head = nullptr;
      }
      else{
        Item* delItem = findItem(index); 
        if(delItem==head){
          head = head->next;
          head->prev = findItem(count-1);
        }
        if(delItem->prev != nullptr){
          delItem->prev->next = delItem->next;
        }
        if(delItem->next != nullptr){
          delItem->next->prev = delItem->prev;
        }
        this->count = this->count-1;
        delete delItem;
      }
      // else if(index == this->count-1){  //removing from end
      //   delete findItem(index);
      //   this->count = this->count-1;
      //   Item *back = findItem(index-1);
      //   back->next = head;
      //   head->prev = back;
      // }
      // else{  //removing from middle
      //   Item* temp = findItem(index-1);
      //   temp->next = findItem(index+1);
      //   findItem(index+1)->prev = temp;
      //   delete findItem(index);
      //   this->count = this->count-1;
      // }
    }
  }
