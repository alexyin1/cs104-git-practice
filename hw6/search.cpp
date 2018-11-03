#include <queue> 
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


void explore(vector<vector<pair<char,int> > >&map, char letter, int x, int y, vector<int>& lcounts, int count){
    if(x <0 || y <0 || x>=map[0].size()|| y>=map.size()){
        return;
    }
    if(map[y][x].second==0 && map[y][x].first == letter){
        map[y][x].second = 1;
        lcounts[count]++;
        //explore above
        explore(map, letter, x, y-1, lcounts, count);
        //explore left
        explore(map, letter, x-1, y, lcounts, count);
        //explore right
        explore(map, letter, x+1, y, lcounts, count);
        //explore bottom
        explore(map, letter, x, y+1, lcounts, count);
    }
}

int main(int argc, char* argv[]){
	if(argc < 2){
        cerr << "Please include a .txt file with the map" << endl;
        return 1;
    } 
    //the # of letters, rows and columns in the map 
    size_t nletters;
    size_t colsize;
    size_t rowsize;
    string rowofletters;
    int count = 0;
    ifstream myfile(argv[1]);
    if(myfile.good()){
        myfile >> nletters;
        myfile >> colsize;
        myfile >> rowsize;
        vector<vector<pair<char, int> > >map(colsize, vector<pair<char, int> >(rowsize)); //stores letter and if map
        getline(myfile,rowofletters); // need to get rid of the '/n' after the constants in line 1
        for(size_t y=0; y<colsize; y++){
            getline(myfile,rowofletters);
            for(size_t x=0; x<rowsize; x++){
                map[y][x].first = rowofletters.at(x);
                map[y][x].second = 0; 
            }
        }
        vector<int> lcounts; //not sure, what is max num of countries?
        for(size_t y=0; y<colsize; y++){
            for(size_t x=0; x<rowsize; x++){
                if(map[y][x].second == 0){
                    lcounts.push_back(0);
                    explore(map, map[y][x].first, x, y, lcounts, count);
                    count++;
                }
            }
        }
        cout << *max_element(lcounts.begin(), lcounts.end());
        return 0;

    }
    return 0;
}