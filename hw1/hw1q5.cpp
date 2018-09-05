/**
 * Incorrect code to identify palindromes
 */

#include <iostream>
#include <istream>
#include <fstream>
#include <cstring> 

using namespace std;

bool helper (int len)
{
  return true;
}
//do not change the main function.
int main (int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a '.txt' file." << endl;
    return 1;
  }
  ifstream myfile(argv[1]);
  int nwords = 0;
  string line = "";
  string word = "";
  int num = 0;
  if (myfile.is_open())
  {
    while(!myfile.eof())
    {
        myfile >> word;
        nwords++;
    }
    char**lines = NULL;
    lines = new char*[nwords];
    int*chars = NULL;
    chars = new int[nwords];
    for(int i=0; i<nwords; i++){
      lines[i]= NULL; 
    }
    myfile.clear();
    myfile.seekg(0, ios::beg);

    for(int j=nwords-1; j>=0; j--){
      myfile >> word;
      chars[j] = word.length();
      //put words in backwards order
      if(word.length()>0){
        lines[j] = new char[word.length()];
        for(int i=0; i<word.length(); i++){
          lines[j][i] = word.at(i);
        }
      }      
    }
    for(int i=0; i<nwords; i++){
      for(int j=0; j<chars[i]; j++){
        cout<<lines[i][j];
      }
      cout<<endl;
    }
    myfile.close();
    for(int i=0; i<nwords; i++){
      delete[] lines[i];
    }
    delete []lines;
    delete []chars;
  }

  return 0;
}
