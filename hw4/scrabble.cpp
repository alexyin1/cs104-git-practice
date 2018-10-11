// ConsolePrinter: Outputs the board to console. This is fully implemented, but you may make modifications if you desire a different style.
// Player: Captures all of the relevant information about a player (name, score, currently held tiles), and may have a function to return a move the player wishes to make. In implementing this class, keep in mind that in a few weeks, you will be adding computer players to the game. Does that affect your design?
// Move: Captures an individual proposed move, maybe the sequence of letters, location, and direction. Alternatively, the letters to return to the bag, or just the fact that it's a pass move. This is a natural place for inheritance from a superclass Move.
// Dictionary: Should be able to check efficiently whether a word is allowed. Keep in mind that word lists can be quite long.
// Board: presumably stores what tiles have been placed where, along with the (static) information about the bonus squares. You need a function that figures out what words would be formed by a proposed move, and return those words for checking. (It's quite likely you will find this the most cumbersome function in the whole project.)

#include "Board.h"
#include "Dictionary.h"
#include "Bag.h"
#include "ConsolePrinter.h"
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
//run a player's Turn
void playerTurn(Player& p, ConsolePrinter& printer, Bag & bag, Board & board){
   unsigned int score = 0;
   printer.printBoard(board);
   printer.printHand(p);
   printer.printScore(p);
   string movecommand; string movetype; string tiles; // does not handle invalid input, just skips turn
   char direction; size_t row; size_t column; bool horizontal;
   cout << p.getName() << "'s Turn:" <<endl;
   stringstream ss;
   getline(cin, movecommand);
   ss.str(movecommand);
   ss >> movetype;
   if(movetype == "EXCHANGE" || movetype == "exchange"){
      ss >> tiles;
      p.replaceMove(tiles, bag); //if replaceMove resolveBlanks -> 0
      printer.printHand(p);
      return;
   }
   else if(movetype == "PLACE" || movetype == "place"){
      ss >> direction;
      ss >> row;
      ss >> column;
      ss >> tiles;
      if(direction == '|'){
         horizontal = 0;
      }
      else{
         horizontal = 1;
      }
      if(!p.hasTiles(tiles, 1)){ //resolveblanks is 1 for placemoves
         cout <<"Invalid move!"<< endl;
         return;
      }
      score = board.placeMove(p.getMoveTiles(tiles), row, column, horizontal);
      if(score == 0){
         cout <<"Invalid move!"<< endl;
         return;
      }
      else{
        p.addScore(score);
      }
      printer.printBoard(board);
      printer.printScore(p);//updated score
      return;
   }
   else{
      return;
   }
  
}

int main(int argc, char* argv[]){
    if(argc < 2){
      cout << "Please provide a configuration text file." << endl;
      return 1;
    } 

    int HANDSIZE=0; string tilefile = ""; string dictfile= ""; string boardfile= ""; int seed=-1;
    string curr; 
    ifstream configfile(argv[1]);
    if(configfile.is_open())
    {
      while(configfile.good()){
        configfile>>curr;
       // cout<<curr<<endl;
        if(curr == "HANDSIZE:"){
          configfile>>HANDSIZE;
        }
        else if(curr == "TILES:"){
          configfile>>tilefile;
        }
        else if(curr == "DICTIONARY:"){
          configfile>>dictfile;
        }
        else if(curr == "BOARD:"){ 
          configfile>>boardfile;
        }
        else if(curr == "SEED:"){
          configfile>>seed;
        }
      }      
      if(HANDSIZE==0 || tilefile=="" || dictfile=="" || boardfile=="" || seed==-1){
        cout <<"Malformed configuration file" << endl;
        return 1;
      }
      else{
         Dictionary dict = Dictionary(dictfile);
         Board board = Board(boardfile, dictfile);
         Bag bag = Bag(tilefile, seed);
         ConsolePrinter printer = ConsolePrinter();
         vector<Tile*> p1hand;
         p1hand = bag.drawTiles(HANDSIZE);
         //put players in vector 
         int nofp=0;
         cout <<"How Many Players?"<<endl;
         cin >> nofp;
         vector<Player*> players;
         while(nofp>0){
            string name;
            cin >> name; 
            Player *p = new Player(name, HANDSIZE);
            players.push_back(p);
            nofp--;
         }
         cin.ignore();
         for(size_t i=0; i< players.size(); i++){
            players[i]->addTiles(p1hand);
            playerTurn(*players[i], printer, bag, board);
         }
          
      }
    }
    configfile.close();
  return 0;
}


