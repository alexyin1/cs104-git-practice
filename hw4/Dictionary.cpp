#include <set>
#include <string>
#include "Dictionary.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;


	/* The constructor gets passed the name of the file from which
	   to read the word list. */
	Dictionary::Dictionary (string dictfile){
    //efficient searching of dictionary
//    string word;      
      ifstream wordlist(dictfile);
  //      if(wordlist.is_open()){
  //        while(wordlist.good()){
  //           wordlist>>word;
  //           this->dictionary.insert(word);
  //        }
  //      }
  // }
    copy(istream_iterator<string>(wordlist),
         istream_iterator<string>(),
         inserter(this->dictionary, this->dictionary.end()));
  
   }
	Dictionary::~Dictionary (){

  }

	/* Checks whether the given word is in the dictionary, and returns true if so.
	   Case should not matter. Must run in O(logn) for the number of words in the dictionary. */
	bool Dictionary::isLegalWord (std::string const & word) const{
    if(this->dictionary.find(word) != this->dictionary.end()){
       return 1;
    }
    return 0;
  }

	//Add more public and private functions/variables here.

