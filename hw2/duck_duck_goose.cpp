#include <iostream>
#include <fstream>
#include "duck_duck_goose.h"
using namespace std;

/* config.txt format
line 1: random seed (unsigned integer)
line 2: number of players in the game (1-indexed)
line 3: ID of "it" player
lines 4 to n+3: IDs of each seated player, from player 0 onward
*/

int main(int argc, char* argv[]){
  if(argc < 3){
    cerr << "Please provide config.txt and output.txt" << endl;
    return 1;
  } 
  int seed; int n; int IDit; int ID;
  ifstream myfile(argv[1]);
  ofstream outfile(argv[2]);

  // add people to playerList
  if(myfile.is_open())
  {
    myfile>>seed;
    myfile>>n;
    myfile>>IDit;
    srand(seed);
    GameData* gd = new GameData();
    gd->itPlayerID = IDit; 
    gd->playerList.push_back(IDit);   //1 it player
    while(n>0){                       //n other players, n+1 total players
      myfile>>ID;
      gd->playerList.push_back(ID);
      n--;
    }
    n = gd->playerList.size();
    while(n>1){
      simulateDDGRound(gd, outfile);
      n = gd->playerList.size(); 
      if(n==1){
        break;
      }
    }
  }
  return 0;
}
void simulateDDGRound(GameData * gameData, std::ostream & output){
  int m = rand()%(4*gameData->playerList.size());   //0 to 4n-1 inclusive
  int itroll;int gooseroll;
  int i;
  int itindex=0; //'it' always starts at index 0.
  int n;
  
  //while(gameData->itPlayerID==gameData->playerList.get(m)){  //it cannot choose itself as a goose
    m = rand()%(4*n);
  //}
  i=0;
  while(i<m){
    //if(gameData->itPlayerID!=gameData->playerList.get(i)){  //dont increment if it spot is chosen, 'it' could never be chosen as a goose
      output << gameData->playerList.get(i) << " is a Duck." <<endl;  //m ducks
      i++;
    //}
  }  
  //if(gameData->itPlayerID==gameData->playerList.get(i)){ //if the next spot is 'it'
  //  i++;
  //}
  output << gameData->playerList.get(i) << " is a Goose!" <<endl; 
  itroll = rand()%49 +1;  //1-49 inclusive
  gooseroll = rand()%49 +1;  //1-49 inclusive
  while(itroll==gooseroll){  //ties need a reroll
    itroll = rand()%49 +1; 
    gooseroll = rand()%49 +1; 
  }
  if(itroll>gooseroll){
     output<< gameData->itPlayerID << " took " << gameData->playerList.get(i) << "'s spot!"<<endl;
     gameData->playerList.set(itindex, gameData->playerList.get(i));   //change 'it' ID to goose ID in playerlist
     gameData->playerList.set(i, gameData->itPlayerID); // change goose ID to 'it' ID
     gameData->itPlayerID = gameData->playerList.get(itindex);  //change 'it' ID in gamedata variable
  }
  else if(gooseroll<itroll){
    output<< gameData->itPlayerID << " is out!"<<endl;
    gameData->playerList.remove(itindex);
    n=gameData->playerList.size();
    if(n==1){
      output<< "Winner is " << gameData->playerList.get(i) << "!"<<endl;
      return;
    }
    itindex = rand()%n; //all ducks are available
    while(gameData->playerList.get(itindex)==gameData->playerList.get(i)){ //while goose == it
      itindex = rand()%n;
    }
    gameData->itPlayerID = gameData->playerList.get(itindex);   //assign new 'it'
    output << gameData->itPlayerID <<" was chosen as the new it." <<endl;
  }
}


//randomly generate target goose 
//randomly generate goose and "it" numbers to see who wins
//while(n>0)
// if(it>goose) goose becomes it, it takes goose's spot in list
// if(goose>it) it is removed from list, n--
