#include <queue> 
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#define ncolors = 4;
using namespace std;

//keep track of all indexes belonging to country
//keep track of all bordering countries

struct Country{
    int color;
    char letter;
    set<char> neighbors;
    Country(char c, int col){
        letter = c;
        color = col; //0 as no color
    }
};

void printSolution(vector<Country>& countries){
    char name;
    for(size_t i=0; i<countries.size(); i++){
        name = 'A'+ i;
        cout << name << ' ' << countries[i].color;
        cout <<endl;
    }
     cout <<endl;
}

bool colorsConsistant(int row, vector<Country>& countries){
    //iterate through set instead
        for(char c : countries[row].neighbors) {
            if(countries[row].color == countries[(int)c-65].color && countries[row].color!=0){  //if true means a neighbor shares colors
                return 0; 
            }
        }    
    return 1;
}

bool mapFilled(vector<Country>& countries){
    //iterate through set instead
    for(size_t i=0; i<countries.size(); i++){
        if(countries[i].color ==0){  // consider 0 to be ok
            return 0; //if true means a country has same color as a neighbor
        }
    }
    return 1;
}

void search(int row, vector<Country>& countries){
    int origcolor;
    for(int i=1; i<=4; i++){
        origcolor = countries[row].color;
        countries[row].color = i; //can be  adjusted for actual colors 
        if(colorsConsistant(row, countries)){
            if(mapFilled(countries)){ //if all rows have color filled
                printSolution(countries);
                return;
            }
            for(char c : countries[row].neighbors){
                if(countries[c-65].color == 0){
                    search((int)c-65, countries);
                }
            } 
        }
        countries[row].color = origcolor;
    }
}

bool compareAlphName(const Country &a, const Country &b)
{
    return a.letter < b.letter;
}


//explore should get all the indexes of all of the countries, and a set of all neighboring countries
void explore(vector<vector<pair<char,int> > >&map, char letter, int x, int y, vector<Country>& countries, int iter){
    if(x <0 || y <0 || x>=map[0].size()|| y>=map.size()){
        return;
    }
    if(map[y][x].second==0 && map[y][x].first == letter){
        map[y][x].second = 1;
        explore(map, letter, x, y-1, countries, iter);
        explore(map, letter, x-1, y, countries, iter);
        explore(map, letter, x+1, y, countries, iter);
        explore(map, letter, x, y+1, countries, iter);
    }
    else if(map[y][x].first != letter){
        countries[iter].neighbors.insert(map[y][x].first); //add neighboring country's name
    }
}

int main(int argc, char* argv[]){
    if(argc < 2){
        cerr << "Please include a .txt file with the map" << endl;
        return 1;
    } 
    //the # of letters, rows and columns in the map 
    size_t nletters; size_t colsize; size_t rowsize; string rowofletters;
    ifstream myfile(argv[1]);
    if(myfile.good()){
        myfile >> nletters;
        myfile >> colsize;
        myfile >> rowsize;
        vector<vector<pair<char, int> > >map(colsize, vector<pair<char, int> >(rowsize)); //stores letter and if map
        //initialize map
        vector<Country> countries;
        getline(myfile,rowofletters); // need to get rid of the '/n' after the constants in line 1
        for(size_t y=0; y<colsize; y++){   
            getline(myfile,rowofletters);
            for(size_t x=0; x<rowsize; x++){
                map[y][x].first = rowofletters.at(x);
                map[y][x].second = 0; 
            }
        }
        //explore map, 
        int iter = 0;
        for(size_t y=0; y<colsize; y++){
            for(size_t x=0; x<rowsize; x++){
                if(map[y][x].second == 0){
                    countries.push_back(Country(map[y][x].first, 0));//   countries[iter].letter = map[y][x].first; color = 0
                    explore(map, countries[iter].letter, x, y, countries, iter); 
                    iter++;
                }
            }
        }
        sort(countries.begin(), countries.end(), compareAlphName); //ensure 'A' is at index 0, 'B' at 1 etc
        search(0, countries);
    }
    return 0;
}