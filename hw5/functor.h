#include <string>
#include <stdio.h>//int tolower ( int c );
#include <ctype.h>//int tolower ( int c );

struct AlphaStrComp {
  bool operator() (const std::string& lhs, const std::string& rhs)
  { // Uses string's built in operator<
    // to do lexicographic (alphabetical) comparison
    return (lhs < rhs);
  }
};

struct LengthStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { // Compares strings by size;
    // Breaks ties by lexicographic comparison
    return (   (lhs.size() < rhs.size())
            || (lhs.size() == rhs.size() && lhs < rhs));
  }
};

struct NumStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { // Compares strings by ascii sum; return (lhs < rhs)
    // Breaks ties by lexicographic comparison 
    return ((sum(lhs) < sum(rhs)) || lhs < rhs);
  }
  int sum(const std::string& s){
    int sum = 0;
    for(size_t i=0; i<s.size(); i++){
        if(48<=(int)s.at(i) && (int)s.at(i)<=57){
            sum = sum + (int)s.at(i)-48;
        }
        else if((int)s.at(i)<65 || (int)s.at(i)>122){}
        else{
            sum = sum + tolower((int)s.at(i))-87;
        }
    }
    return sum;
  }
};