#include "stackint.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// const int NEW_LINE = -7;
// const int OPEN_PAREN = -6;
// const int CLOSED_PAREN = -5;
// const int MULTIPLIER = -4;
// const int ADDER = -3;
// const int SHIFTLEFT = -2;
// const int SHIFTRIGHT = -1;
// const int NUMBER = 0;
// const int NONE = -10;


class Parser {
public:
  Parser(){

  }
  ~Parser(){

  }

  bool emptySyntax(StackInt& stack, stringstream& ss){  //if stack is empty, see if syntax is acceptable
    char c=' '; int symbolval; 
    if(ss.peek()) //check all starting conditions/basic errors
    {
      c = ss.peek();
      symbolval = convert(c);
      if(symbolval>=-5 && symbolval<= -3){  //if first symbol is +,*,)
        return false;
      }
    }
    return true;
  }

  int getNumber(stringstream& ss){  //make sure to call only when a number upnext in stream
    int number=0; char c = '0';  string wordnum =""; int hasnum = 0; 
    while(!ss.str().empty()){  // dont double count a single number
      c = ss.peek(); 
      if(c >= '0' && c <= '9'){  
        hasnum = 1;
        c = ss.get();
        wordnum += c;          
      }
      else{
        break;
      }
    }
    if(hasnum == 1){
        number = stoi(wordnum);      
    } 
    return number;
  }

//parenCheck, operatorCheck, addmultCheck check if a symbol is ok to push to stack
  bool parenCheck(StackInt& stack, stringstream& ss){ //check syntax when '<' or '>' is next input
    char c=' '; int currentchar;
    c = ss.get();
    currentchar = convert(c);
    if(stack.top() == -5 || stack.top()>=0){
      return false;
    }
    stack.push(currentchar);
    return true;
  }

  bool operatorCheck(StackInt& stack, stringstream& ss){ //check syntax when '<' or '>' is next input
    char c=' '; int currentchar;
    c = ss.get();
    currentchar = convert(c);
    if(stack.top() >= 0){
      return 0;                  //number cannot be followed by < or >
    }
    // if(stack.top() == -6 || stack.top() == -6 )  //only numbers and +* can be inside parentheses
    //   return 0;
    // }
    stack.push(currentchar);
    return 1;
  }

  bool addmultCheck(StackInt& stack, stringstream& ss){ //check syntax when '*' or '-' is next input
    char c=' '; int topofstack; int currentchar;
    c = ss.get();
    currentchar = convert(c);
    if(stack.top() == -6){
      return 0;
    }
    if(stack.top() >= -4 && stack.top() <= -1){
      return 0;
    }
    stack.push(currentchar);  
    return 1;
  }

  bool evalPiece(StackInt& stack, stringstream& ss, StackInt& solution){ // evaluating parts of expression
    int topofstack = stack.top(); int currentchar; int num1; int num2;
    char c = ' ';
    if(!ss.eof()){
      c = ss.get(); 
      //cout << c << endl;
      currentchar = convert(c);
      if(currentchar == -5){ //if simplifying from )
        if(topofstack == -6){  //edge case ()
          return 0;
        }
        else if(topofstack >= -4 && topofstack <= -1){ //if *) +) <) or >) occur
          return 0;
        }
      }
    }
    while(!stack.empty()){  // loop will always break because # of () is counted beforehand
      //cout<<topofstack<<endl;
      if(topofstack == -6){
        stack.pop();
        break;
      }
      else if(topofstack == -2 || topofstack == -1){ //< or >
        stack.pop();
        if(solution.empty()){  //edge case <()  with no number
          return 0;
        }
        else{
          if(topofstack == -2){
            num1 = solution.top();

            solution.pop();
            num1 = num1*2;
            solution.push(num1);
          } 
          else{
            num1 = solution.top();
            solution.pop();
            num1 = num1/2;
            solution.push(num1);
          }  
        }
      }
      else if(topofstack == -4 || topofstack == -3){ //mult add
        stack.pop(); //remove the * or +
        if(stack.empty()){  // case +) with  no left number
          return 0;
        }
        if(solution.empty()){  //edge case <()  with no number
          return 0;
        }
        //else{  //if next element is a number //not considering (1+2*4)
        if(topofstack == -4){
          num2 = stack.top(); //reach the number following the *
          num1 = solution.top();
          solution.pop();
          num1 = num1*num2;
          solution.push(num1);
        }
        else{
          num2 = stack.top(); //reach the number following the +
          num1 = solution.top();
          solution.pop();
          num1 = num1+num2;
          solution.push(num1);
          //cout<<solution.top() <<endl;
        }
      }
      else{ //number
        num1 = topofstack;
        //cout << num1<< endl;
        solution.push(num1);
      }
      //increment stack
      stack.pop();
      topofstack = stack.top();
    }
    return 1;
  }

  void calc(StackInt& stack, stringstream& ss){ //calculate
    char c=' '; int symbolval; int holder; 
    StackInt solution;
    if(stack.empty()){
      if(!emptySyntax(stack, ss)){
        cout<< "Malformed" <<endl;
        return;
      }
      else{
        c = ss.peek();
        symbolval = convert(c);
        if(symbolval>=-6 && symbolval<=-1){ //if symbol
          c = ss.get();
          stack.push(symbolval);
        }
        else{  //if number  //also check if top is operator
          holder = getNumber(ss);
          solution.push(holder);
          if(!ss.eof()){//if ss still has values, then expression syntax must be false
            cout<< "Malformed" <<endl;
            return; 
          }
        }
      }
    }
   // cout<<ss.str()<<endl;
    while(!ss.eof()){
      c = ss.peek();
      //cout <<ss.str() <<endl;
      symbolval = convert(c); 
      //cout <<symbolval <<endl;
      if(symbolval==0){
        holder = getNumber(ss);
        //cout <<stack.top();
        while(stack.top() == -2 || stack.top() == -1){
          if(stack.top() == -2){
          holder = holder *2;
          }
          else if(stack.top() == -1){
            holder = holder/2;
          }
          stack.pop();
        }
        //cout<<holder;
        stack.push(holder);
      }
      else{
        if(symbolval == -6){ 
          if(!parenCheck(stack, ss)){
            cout<<"Malformed" <<endl;
            return;
          }
        }
        else if(symbolval == -4 || symbolval == -3){
          if(!addmultCheck(stack, ss)){
            cout<<"Malformed" <<endl;
            return;
          }
        }
        else if(symbolval == -2 || symbolval == -1){
          if(!parenCheck(stack, ss)){
            cout<<"Malformed" <<endl;
            return;
          }
        }
        else if(symbolval==-5){
          if(!evalPiece(stack, ss, solution)){ //evaluate up to '('
            cout<<"Malformed" <<endl;
            return;
          }
        }
      }
      // if(stack.empty()){  //if nothing is pushed or removed
      //   cout <<"Malformed" <<endl; //if ss has values and stack is empty, must be malformed;
      //   return;
      // }
    }
    while(!stack.empty()){
      evalPiece(stack, ss, solution);
    }
    if(!solution.empty()){
      cout<<solution.top();
      solution.pop();
    }
  }

  int convert(char c){
      int symbolval = -10;
      if(c== '\n'){
        symbolval = -7;
      }
      else if(c == '('){
        symbolval = -6;
      }
      else if(c == ')'){
        symbolval = -5;
      }
      else if(c == '*'){
        symbolval = -4;
      }
      else if(c == '+'){
        symbolval = -3;
      }
      else if(c == '<'){
        symbolval = -2;
      }
      else if(c == '>'){
        symbolval = -1;
      }
      else if(c >= '0' && c <= '9'){
        symbolval = 0;
      }
      else{
        symbolval = -10;
      }
      return symbolval;
  }

bool matching(string expression){
  size_t leftparen=0; size_t rightparen=0; size_t addmult=0; size_t nofnumbers=0; size_t i=0; char c = ' '; //count number of each
  int symbolval = 0;
  leftparen = count(expression.begin(), expression.end(), '(');
  rightparen = count(expression.begin(), expression.end(), ')');
  addmult = count(expression.begin(), expression.end(), '*');
  addmult = addmult + count(expression.begin(), expression.end(), '+');
  while(i<expression.length()){
    c = expression.at(i);
    symbolval = convert(c);
    i++;           
    if(symbolval == 0){
      nofnumbers++;
      while(symbolval == 0 && i<expression.length()){  // dont double count a single number
        c = expression.at(i);
        symbolval = convert(c);
        i++;
      }
    }
    else if(symbolval == -10){  //strange character found
      return false;
    }
  }
  if(leftparen != rightparen || addmult+1 != nofnumbers){
    return false;
  }
  if(leftparen > addmult){
    return false;
  }
  return true;
}
};


string removeSpaces(string str) 
{ 
    stringstream ss; 
    string temp; 
    ss << str; 
    str = ""; 
    while (!ss.eof()) 
    { 
        temp ="";
        ss >> temp; 
        str = str + temp; 
        //cout << str<<endl;
    } 
    return str; 
} 

int main(int argc, char* argv[]){
	if(argc<2){
    cout<<"Please provide an input file"<<endl;
    return 1;
  }
  StackInt stack;
  Parser pars;
  ifstream myfile(argv[1]);
  //stringstream ss;
  string input;
  //add people to playerList
  if(myfile.is_open())
  {
    while(getline(myfile, input))
    {
      //clear stack
      input = removeSpaces(input); 

      if(!input.empty()){
        stringstream ss(input);
        if(!pars.matching(input)){
          cout<< "Malformed" <<endl;
        }
        else{
          //cout << ss.str();
          //do calculation
          pars.calc(stack, ss);
          //stringstream ss(input);//need to put the expression back into the stream
        }
      }
    }
  }
  return 0;
}
