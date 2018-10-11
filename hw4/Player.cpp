
#include <list>         // std::list
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>    // std::copy
#include <iterator>

#include "Player.h"
using namespace std;

	/* Constructor giving the player the given name, and setting their points to 0.
	   Does not give the player any tiles.
	*/
	Player::Player (string const & name, size_t maxTiles){
		this->maxTiles = maxTiles;
		this->name = name;
		this->points = 0;
	}

	/* Destructor for a player. Deletes all the tiles the player still has. */
	Player::~Player (){

	}

	/* Returns the set of tiles the player currently holds. */
	set<Tile*> Player::getHandTiles() const{
		return this->hand;
	}

	size_t Player::getMaxTiles() const{
		return maxTiles;
	}

	string Player::getName() const{
		return name;
	}

	/* Reads a move string and confirms that the player has the tiles necessary to
	   execute this move.

	   The move string is case-insensitive.

	   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
	   If resolveBlanks is true, then when the string contains a '?',
	   the next letter is interpreted as the letter to use the blank as.

	   By definition, if this function returns true, then takeTiles() would
	   succeed.
	 */
	bool Player::hasTiles(string & move, bool resolveBlanks) const{
      //resolveBlanks 1 -> place
      //resolveBlanks 0 -> exchange
      bool hasblank = 0;
      for(size_t j=0; j<move.size(); j++){
         if(move.at(j)=='?'){
            hasblank=1;
            break;
         }
      }              
      if(hasblank){
         if(resolveBlanks){
            for(size_t i=0; i<maxTiles; i++){
               if(move.at(i)=='?'){
                  for(set<Tile*>::iterator it = this->hand.begin(); it != this->hand.end(); ++it){
                     if((*(*it)).getLetter()=='?'){
                        (*(*it)).useAs(move.at(i+1)); //set the ? use as the letter that follows as per hw4 instructions input, fails if ? is not followed by the desired character
                     }
                  }
               }
            }
         }
         else{ //for some dumb reason user is trading in blank tile
            for(set<Tile*>::iterator it = this->hand.begin(); it != this->hand.end(); ++it){
               if((*(*it)).getLetter()=='?'){
                  (*(*it)).useAs('?');
               }
            }
         }
      }
      bool letterfound = 0;
      //create shallow copy of Tiles into handcheck
      vector<Tile*>handcheck;
      for(set<Tile*>::iterator it =this->hand.begin(); it != this->hand.end(); ++it){
         handcheck.push_back(*it); //copy pointers
      }
      for(size_t i=0; i<move.size(); i++){
         for (size_t j=0; j<handcheck.size(); j++){
            if(handcheck[j]->getUse()==move.at(i)){
               handcheck.erase(handcheck.begin()+j);
               break;
            }
         }
      }
      if(this->hand.size()-move.size() == handcheck.size()){ //if all letters were found
         return 1;
      }
      return 0;
   }


	/* Reads a move string, finds the corresponding tiles in the player's hand, and
	   removes and returns those tiles in the order they appear in the move string.

	   The move string is case-insensitive.

	   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
	   If resolveBlanks is true, then when the string contains a '?',
	   the next letter is interpreted as the letter to use the blank as,
	   and the "use" field of the tile is set accordingly.

	   The move string is assumed to have correct syntax.
	*/
	void Player::removeTiles (string& move, Bag& bag, bool resolveBlanks){ //takes tiles needed for a move
		//vector<Tile*> movev;
		for(size_t i=0; i<move.size(); i++){ //iterate through string          
         for (set<Tile*>::iterator it = this->hand.begin(); it != this->hand.end(); ++it){
            if((*(*it)).getUse()==move.at(i)){
               if(!resolveBlanks){//if its a replacemove
                  bag.addTile((*it));
               }
               this->hand.erase(*it);
               break;
            }
         }
      }     
		//return movev;
	}

   bool Player::replaceMove(string & move, Bag& bag){
      if(hasTiles(move, 0)){
         removeTiles(move, bag, 0);
         vector<Tile*> l = bag.drawTiles(move.size());
         addTiles(l);      
      }
      return 0;
   }

	// Adds all the tiles in the vector to the player's hand.
	void Player::addTiles (const vector<Tile*>& tilesToAdd){
		if(this->hand.size()+tilesToAdd.size()>maxTiles){ //if tilesToAdd is too large
			cout<<"Tiles to be added exceeds tile max"<<endl;
		}
		else{ //append to hand
         for(size_t i=0; i<tilesToAdd.size(); i++){
            hand.insert(tilesToAdd[i]);
         }
		}	
	}

   void Player::addScore(unsigned int turnscore){
      //cout << turnscore;
      points = points + turnscore;
   }

   unsigned int Player::getScore(){
      return points;
   }

   const vector<Tile*> Player::getMoveTiles(string& move){ //takes tiles needed for a move
      vector<Tile*> movev;
      for(size_t i=0; i<move.size(); i++){ //iterate through string          
         for (set<Tile*>::iterator it = this->hand.begin(); it != this->hand.end(); ++it){
            if((*(*it)).getUse()==move.at(i)){
               movev.push_back(*it);
               break;
            }
         }
      }    
      return movev;
   }
