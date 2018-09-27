#include "stackint.h"
/**
   * Returns true if the stack is empty, false otherwise
   */
  StackInt::StackInt(){

  }
  StackInt::~StackInt(){

  }
  bool StackInt::empty() const{
    return list.empty();
  }

  /**
   * Pushes a new value, val, onto the top of the stack
   */
  void StackInt::push(const int& val){
    list.push_back(val);
  }

  /**
   * Returns the top value on the stack
   */
  int StackInt::top() const{
    return list.get(list.size()-1);
  }

  /**
   * Removes the top element on the stack
   */
  void StackInt::pop(){
    list.remove(list.size()-1);
  }
