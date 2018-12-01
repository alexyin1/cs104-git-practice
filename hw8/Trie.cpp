#include "Trie.h"
using namespace std;

TrieSet::TrieSet(){ // a constructor for an empty trie
    root = new TrieNode();
    root->c = ' ';
    root->inSet=true; //let empty word be true word
    root->parent = nullptr;
    for(size_t i=0; i<26; i++){
        root->children[i] = nullptr;
    }
} 

TrieSet::~TrieSet(){ // destructor
    if(root!=nullptr){
        clear(root);
    }
} 

void TrieSet::clear(TrieNode* node){
    if(node == nullptr){
        return;
    }
    for(size_t i=0; i<26; i++){
        clear(node->children[i]);
    }
    delete node;
}

void TrieSet::insert(string input){  /* Add this string to the set. Do nothing if the string is already in the set. */
    if(input.size()==0){ //empty string is held in root
        return;
    }
    size_t iter = 0;
    int index;
    TrieNode* node = root;
    while(iter < input.size()){
        index = input.at(iter) - 'a';
        if(node->children[index] == nullptr){
            TrieNode* freshnode = new TrieNode();
            freshnode->inSet = false;
            freshnode->c = input.at(iter);
            freshnode->parent = node;
            for(size_t i=0; i<26; i++){
                freshnode->children[i] = nullptr;
            }
            node->children[index] = freshnode;
        }
        node = node->children[index];
        if(iter == input.size()-1){
            node->inSet=true;
        }
        iter++;
    }
}
/* Removes this string from the set.
  Do nothing if the string is not already in the set. */
void TrieSet::remove(string input){
    if(input.size()==0){ //empty string is held in root
        return;
    }
    size_t iter = 0;
    int index;
    TrieNode* node = root;
    while(iter < input.size()){
        index = input.at(iter) - 'a';
        if(node->children[index] == nullptr){  //if word not found
            return;
        }
        node = node->children[index];
        iter++;
    }
    node->inSet = false;
}


/* returns the TrieNode matching the provided string, or returns NULL 
  if it is not the prefix of a word in the Trie. */

TrieNode* TrieSet::prefix(string px) const{
    size_t iter = 0;
    int index;
    TrieNode* node = root;
    while(iter < px.size()){
        index = px.at(iter) - 'a';
        if(node->children[index] == nullptr){  //if word not found
            return nullptr;
        }
        node = node->children[index];
        iter++;
    }
    return node;
} 
