#include <iostream>
#include <stack>
#include <sstream>
using namespace std;
int main(){
	stack<int> rope; char c; string command; int mult;
	cin >> command;
	stringstream ss(command);
	while(ss >> c){
		if(c== 'n'||c=='s'){
         mult=2;
      }
      else if(c=='e'||c=='w'){
         mult =1;
      }
      else{
         cout <<"invalid"<<endl;
         return 0;
      }
      if(!rope.empty() && rope.top()/mult == 1){ //check not for equality but for previous
           rope.pop();
      }
      else{
         rope.push(mult);
      }
	}
   if(rope.empty()){
      cout <<"Rolled up"<<endl;
   }
   else{
      cout <<"Not Rolled up"<<endl;
   }
   return 0;
}
