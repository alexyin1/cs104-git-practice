/**
 * Incorrect code to identify palindromes
 */

#include <iostream>
#include <sstream>
#include <cstring> 

using namespace std;

bool helper (stringstream &input, int len)
{
	char prev;

	//if we are at the midpoint of the string, return true.
	if (len == 0) return true;

	/**
	 * If the length of the string is odd, and the next
	 * character is the midpoint of the string, consume it
	 * and return true.
	 */
	input >> prev;
	if (len == 1) return true;

	bool val = helper(input, len-2);

  input.seekg(0, ios::end);
  int size = input.tellg();
  string s = input.str().substr(size/2 - len/2, len);
  //input.str();
  //cout<<s<<endl;
  if(s[0] != s[s.length()-1]){
      val = false;  
  }
  //cout<<word<<endl;
  if (val) return true;
  return false;
}

//do not change the main function.
int main (int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a string of characters." << endl;
    return 1;
  }
  stringstream ss;
  ss << argv[1];
  if(helper(ss, strlen(argv[1])))
	  cout << "Palindrome" << endl;
  else cout << "Not a Palindrome" << endl;
  return 0;
}
