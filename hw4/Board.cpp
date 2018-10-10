

#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
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
   if(y<0 || x<0){
      return nullptr;
   }
   if(y-1>this->getColumns() ||x-1>this->getRows()){
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

bool Board::placeMove(const vector<Tile*>& attplay, size_t startx, size_t starty, const bool horizontal){  
   //check if all squares are open
   size_t x=startx; size_t y=starty; size_t xiter = 0; size_t yiter = 0;
   if(horizontal==1){
      xiter = 1;  //when going horizontally iterate x
   }
   else{
      yiter = 1; //when going vertically iterate y
   }
   for(size_t i=0; i<=attplay.size(); i++){
      if(this->getSquare(x,y) == nullptr){
         return 0; //attempted move places tiles outofbounds
      }
      if(this->getSquare(x,y)->isOccupied()){
         return 0; //attempted move places tiles in already occupied square
      }
      x = x+xiter;
      y = y+yiter;
   }
   
   // if(this->inlineValid(attplay, startx, starty, horizontal) && this->perpValid(attplay, startx, starty, horizontal)){
   //    //put the attplay into the board, confirm the scores
   // }
   // else{
   //    //remove the words from the wordscore vector 
   //    cout<<"Invalid placement move"<<endl;
   // }
   this->placeTiles(attplay, startx, starty, horizontal);
   
   return 1;
}
//direction must be specified for attplay 

bool Board::inlineValid(const vector<Tile*>& attplay, const size_t startx, const size_t starty, const bool horizontal){//checks if inline word is valid
   size_t x=startx; size_t y=starty; size_t xiter=0; size_t yiter=0; 
   string word="";  
   size_t startword; size_t endword;
   if(horizontal==1){
      xiter = 1;  //when going horizontally, iterate x
      startword=startx;
      endword=starty;
   }
   else{
      yiter = 1; //when going vertically, iterate y
      startword=starty;
      endword=starty;
   }
   // find the leftmost and rightmost letter to the attplay, stopping when null or endofboard.
   while(this->getSquare(x-xiter, y-yiter)!=nullptr){ //find start of word
      if(!this->getSquare(x-xiter, y-yiter)->isOccupied()){
         break;
      }
      startword = startword - xiter - yiter;  //will always iterate by 1
   }
   while(this->getSquare(x+xiter, y+yiter)!=nullptr){ //find end of word
      if(this->getSquare(x-xiter, y-yiter)->isOccupied()){
         break;
      }
      endword = startword + xiter + yiter;  //will always iterate by 1
   }
   if(startword==endword){ 
      return 0;
   }

   else if(dict.isLegalWord(word)){
      if(horizontal){
         wordscore.push_back(wordScore(attplay, startword, starty, endword, starty, xiter, yiter));
      }
      else{
         wordscore.push_back(wordScore(attplay, startx, startword, startx, endword, xiter, yiter));
      }
      return 1;
   }

   return 1;
}

bool Board::perpValid(const vector<Tile*>& attplay, size_t startx, size_t starty, const bool horizontal){//checks if perpindicular words are valid
   //bool validvert=1;
   // if(horizontal==0){ //check perpindicular to vertical 

   // }
   // else{

   // }
   return 1;
}
//assumes valid play
size_t Board::wordScore(const vector<Tile*>& attplay, size_t x_start, size_t y_start, size_t x_end, size_t y_end, size_t xiter, size_t yiter){ //for inline words
   size_t wordscore=0; size_t charscore=0; size_t wordmultiplier = 1;
   while(x_start!=x_end || y_start!=y_end){
      if(this->getSquare(x_start,y_start)==nullptr){ //stop iterating if outofbounds 
         break;
      }
      if(this->getSquare(x_start,y_start)->isOccupied()){ //add the letters before and after the attplay to the wordscore, also ignoring multipliers
         wordscore += getSquare(x_start,y_start)->getScore();
         x_start += xiter;
         y_start += yiter;
      }
      else{ //add the tiles in attplay to the wordscore, including multipliers
         for(size_t i=0; i<attplay.size(); i++){
            charscore = this->getSquare(x_start,y_start)->getLMult() * attplay[i]->getPoints(); //include multiplier
            wordmultiplier = this->getSquare(x_start,y_start)->getWMult() * wordmultiplier;   //include word mult                     
            wordscore+= charscore;
            x_start += xiter;
            y_start += yiter;
         }
      }
      
   }
   wordscore = wordmultiplier*wordscore;
   return wordscore;
}

size_t wordScore(const Tile* attLetter, size_t x_start, size_t y_start, size_t x_end, size_t y_end, size_t xiter, size_t yiter){ //for perp words
   // size_t wordscore=0; size_t charscore=0; size_t wordmultiplier = 1;
   // while(x_start!=x_end || y_start!=y_end){
   //    if(getSquare(x_start,y_start)==nullptr){ //stop iterating if outofbounds 
   //       break;
   //    }
   //    if(getSquare(x_start,y_start)->isOccupied()){ //add the letters before and after the attplay to the wordscore, also ignoring multipliers
   //       wordscore += getSquare(x_start,y_start)->getScore();
   //    }
   //    else{ //add the tiles in attplay to the wordscore, including multipliers
   //       charscore = getSquare(x_start,y_start)->_LMult * attLetter->getPoints(); //include multiplier
   //       wordmultiplier = getSquare(x_start,y_start)->_WMult * wordmultiplier;   //include word mult                     
   //       wordscore+= charscore;
   //    }
   //    startx += xiter;
   //    starty += yiter;
   // }
   // wordscore = wordMultiplier*wordscore;
   // return wordscore;
}

