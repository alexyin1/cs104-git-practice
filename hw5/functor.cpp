#include <iostream>
#include "functor.h"

using namespace std;
template <class Comparator>
void DoStringCompare(const std::string& s1, const std::string& s2, Comparator comp)
{
  cout << comp(s1, s2) << endl;  // calls comp.operator()(s1,s2);
}

int main() {
  string s1 = "Blue";
  string s2 = "Red";
  AlphaStrComp comp1;   
  LengthStrComp comp2;
  NumStrComp comp3;


  // Here comp1(s1,s2) is calling comp1.operator() (s1, s2);
  cout << "Blue compared to Red using AlphaStrComp yields "; DoStringCompare(s1, s2, comp1); cout<< endl;

  // Here comp2(s1,s2) is calling comp2.operator() (s1, s2);
  cout << "Blue compared to Red using LenStrComp yields "; DoStringCompare(s1, s2, comp2); cout << endl;

  cout << "Blue compared to Red using NumStrComp yields "; DoStringCompare(s1, s2, comp3); cout << endl;
  return 0;
}
