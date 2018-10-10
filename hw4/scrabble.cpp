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

using namespace std;

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
 //        board.loadDictionary(dict);
         Bag bag = Bag(tilefile, seed);
         ConsolePrinter printer = ConsolePrinter();
         printer.printBoard(board);
         vector<Tile*> p1hand;
         p1hand = bag.drawTiles(HANDSIZE);
         Player p1 = Player("Jake", HANDSIZE);
         p1.addTiles(p1hand);
         printer.printHand(p1);
         printer.printScore(p1);
         cout<<dict.isLegalWord("apple") << "!" <<endl;
         string movetype; string move = "eoiv";
         cout << "Jake's Turn:" <<endl;
         printer.printHand(p1);
         cout << "Enter Type of Move: (Place, Replace, or Pass)" <<endl;
         //cin >> movetype;
         cout << "Enter all the letters you would like to replace" <<endl; 
         //cin >> move;
         p1.replaceMove(move, bag); //if replaceMove resolveBlanks -> 0
         printer.printHand(p1);

      }
    }
    configfile.close();
  return 0;
}

