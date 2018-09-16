#include "circular_list_int.h"
#include <cstdlib>
#include <iostream>
#include <string>
//check all heads for null, check all counts for 0,1
//never access prev, next when head null or count<=1
  

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
    if(index >= this->count){
      index = index%count;   //convert index=8 into 8%count, giving a usable number
    }  
    Item* temp = head;
    for(size_t i=0; i<index; i++){
      temp = temp->next;
    }
    return temp;
  }
 
  int CircularListInt::get(size_t index) const
  {
    return findItem(index)->value;
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
    if(this->count==0){
      head = thing;
    } 
    else{
      findItem(this->count-1)->next = thing;
      thing->prev = findItem(this->count-1);
      thing->next = head;
    }
    this->count = this->count+1;
  }

	// Sets the item at the given index to have the given value.
	// If an index is passed that is >= the number of items in the list, it should "wrap around" back to the first element.
	void CircularListInt::set(size_t index, int value) 
  {
    findItem(index)->value = value;
  }
  //how to adjust indexs after removal

	// Removes the item at the given index from the list.
	// List elements after the removed element are pulled forward, so their indicies decrease by one.
	// If an index is passed that is larger then the number of items in the list, it should "wrap around" back to the first element.
	void CircularListInt::remove(size_t index)
  {
    if(this->count == 0){
      return;
    }
    else if(this->count == 1){
      delete findItem(index);
      head = nullptr;
      this->count = this->count-1;
      return;
    }
    else{//count>1
      //what if head is deleted
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
  }
