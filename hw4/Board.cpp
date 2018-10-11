

#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>    // std::reverse
#include "Tile.h"
#include "Square.h"
#include "Move.h"
#include "Dictionary.h"
#include "Board.h"
using namespace std;

Board::Board (string boardfile, string dictfile): dict(dictfile){
   ifstream myfile(boardfile);
   unsigned int wmult=1; unsigned lmult=1; char c; bool start=0;
   // add people to playerList
   if(myfile.is_open()){
      myfile>>this->rows;
      myfile>>this->columns;
      myfile>>this->sx;
      myfile>>this->sy;
      sx = sx-1;
      sy = sy-1;
      for(size_t i=0; i<this->columns; i++){ //iter down board
         this->board.push_back(vector<Square*>());
      	for(size_t j=0; j<this->rows; j++){ //iter across board
         myfile>>c;
         wmult =1; lmult =1; start=0; // set mults to 1, start=0 by default
         if(c == 'd'){
            wmult = 2;
         }
         else if(c == 't'){
            wmult = 3;
         }
         else if(c == '2'){
            lmult = 2;
         }
         else if(c == '3'){
            lmult = 3;
         }
         if(j==this->sx && i==this->sy){
            start = 1;
         }
         Square* square = new Square(lmult, wmult, start);
      		this->board.at(i).push_back(square);	
      	}
      }  
   }
   else{
   	cout <<"File not Found"<<endl;
   }

   }

Board::~Board (){
   for(size_t i=0; i< this->getColumns(); i++){
      for(size_t j=0; j< this->getRows(); j++){
         delete board[i][j];
      }
   }
}


void  Board::placeTiles (const vector<Tile*> & attplay, size_t startx, size_t starty, const bool horizontal){
   if(horizontal){
      for(size_t i=0; i<attplay.size(); i++){
         this->getSquare(startx+i, starty)->placeTile(attplay[i]);
      }
   }
   else{
      for(size_t j=0; j<attplay.size(); j++){
         this->getSquare(startx, starty+j)->placeTile(attplay[j]);
      }
   }
}


/* Returns a pointer to the Square object representing the
    (y,x) position of the board. Indexing starts at 1 here.
   This is needed only to display the board. */
Square *  Board::getSquare (size_t x, size_t y) const{  //checks for outofbounds x,y
   if(y<=0 || x<=0){
      return nullptr;
   }
   if(y>this->getColumns() || x>this->getRows()){
      return nullptr;
   }
   return board[y-1][x-1];
}


/* Returns the number of rows of the board.*/
size_t  Board::getRows() const{
   return rows;
}

/* Returns the number of columns of the board.*/
size_t  Board::getColumns() const{
   return columns;
}

unsigned int Board::placeMove(const vector<Tile*>& attplay,const size_t startx,const size_t starty, const bool horizontal){  
   //check if all squares are open
   size_t x=startx; size_t y=starty; size_t xiter = 0; size_t yiter = 0; bool firstmove = 0;
   if(horizontal==1){
      xiter = 1;  //when going horizontally iterate x
   }
   else{
      yiter = 1; //when going vertically iterate y
   }
   for(size_t i=0; i<attplay.size(); i++){
      if(this->getSquare(x,y) == nullptr){
         return 0; //attempted move places tiles outofbounds
      }
      if(this->getSquare(x,y)->isOccupied()){
         return 0; //attempted move places tiles in already occupied square
      }
      if(this->getSquare(x,y)->isStart()){
         firstmove = 1;
      }
      x = x+xiter;
      y = y+yiter;
   }

   if(firstmove == 1){
      string word="";
      for(size_t i=0; i<attplay.size(); i++){
         word += attplay[i]->getUse();
      }
      if(!dict.isLegalWord(word)){
         return 0;
      }
      wordScore(attplay, startx, starty, x, y, xiter, yiter);
      this->placeTiles(attplay, startx, starty, horizontal);
   }
   else if(this->inlineValid(attplay, startx, starty, horizontal)){
      this->placeTiles(attplay, startx, starty, horizontal);
   }
   else{
      return 0;
   }
   
   return wordscore;
}
//direction must be specified for attplay 

bool Board::inlineValid(const vector<Tile*>& attplay, const size_t startx, const size_t starty, const bool horizontal){//checks if inline word is valid
   size_t x=startx; size_t y=starty; size_t xiter=0; size_t yiter=0; 
   string preword="";  string postword = ""; string word="";
   size_t startword; size_t endword;
   if(horizontal==1){
      xiter = 1;  //when going horizontally, iterate x
      startword=startx;
      endword=startx;
   }
   else{
      yiter = 1; //when going vertically, iterate y
      startword=starty;
      endword=starty;
   }
   // find the leftmost and rightmost letter to the attplay, stopping when null or endofboard.
   while(this->getSquare(x, y)!=nullptr){ //find start of word
      if(!this->getSquare(x, y)->isOccupied()){
         break;
      }
      preword += this->getSquare(x,y)->getLetter();
      startword = startword - xiter - yiter;  //will always iterate by 1
   }
   while(this->getSquare(x, y)!=nullptr){ //find end of word
      if(!this->getSquare(x, y)->isOccupied()){
         break;
      }
      postword += this->getSquare(x,y)->getLetter();
      endword = startword + xiter + yiter;  //will always iterate by 1
   }

   if(startword==endword){ 
      return 0;
   }
   else{
      reverse(preword.begin(), preword.end());
      for(int i=0; i<preword.size(); i++){
         word+= preword.at(i);
      }
      for(size_t i=0; i<attplay.size(); i++){
         word+= attplay[i]->getUse();
      }
      for(int i=0; i<postword.size(); i++){
         word+= postword.at(i);
      }
      if(dict.isLegalWord(word)){
         if(horizontal){
            wordScore(attplay, startword, starty, endword, starty, xiter, yiter);
         }
         else{
            wordScore(attplay, startx, startword, startx, endword, xiter, yiter);
         }
         return 1;
      }
   }
   return 0;
}

bool Board::perpValid(const vector<Tile*>& attplay, size_t startx, size_t starty, const bool horizontal){//checks if perpindicular words are valid
   return 1;
}
//assumes valid play
void Board::wordScore(const vector<Tile*>& attplay,const size_t x_start,const size_t y_start,const size_t x_end,const size_t y_end,const size_t xiter,const size_t yiter){ //for inline words
   unsigned int curwordscore=0; unsigned int charscore=0; unsigned int wordmultiplier = 1;
   size_t x = x_start; size_t y = y_start;
   while(x<=x_end && y<=y_end){

      if(this->getSquare(x,y)==nullptr){ //stop iterating if outofbounds 
         break;
      }
      else{
         if(this->getSquare(x,y)->isOccupied()){ //add the letters before and after the attplay to the wordscore, also ignoring multipliers
            cout<<"hello" <<endl;
            curwordscore += this->getSquare(x,y)->getScore();
            x = x + xiter;
            y = y + yiter;
         }
         else{ //add the tiles in attplay to the wordscore, including multipliers
            for(size_t i=0; i<attplay.size(); i++){
               charscore = this->getSquare(x,y)->getLMult() * attplay[i]->getPoints(); //include multiplier
               wordmultiplier = this->getSquare(x,y)->getWMult() * wordmultiplier;   //include word mult                     
               curwordscore+= charscore;
               x = x + xiter;
               y = y + yiter;
            }
         }
      }
   }
   curwordscore = wordmultiplier*curwordscore;
   wordscore += curwordscore;
   wordscore;
}
