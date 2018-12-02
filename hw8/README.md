I only have the Trie working, so please don't doc me 10 points for using starter code.

I have an AI.h file that and a CPUL.cpp file that inherits from it and neither works, but it uses the idea of backtracking in the context of scrabble board positions which are designed around the starter code but don't work.
The getLegalWords() function in AI.h is suppose to get all the legal words on a specific square on the Scrabble board,
which is then supposed to be used by the virtual function doBestMove() on every possible square a move can be done on on the Scrabble board,
eventually comparing the sets of possible words on every square and returning a string with the best move, which would change with the type of AI.

getLegalWords() would work something like this:

void AI::getLegalWords(bool horizontal, int y, int x, string prefix, string remainingletters, set<string>& words, Board* &b){
    int xiter =0; int yiter = 0;
    size_t xmax = b->getColumns();
    size_t ymax = b->getRows();
    Square* cursquare;
    char c;
       
    if(horizontal == true){ //then move is going horizontal
        xiter = 1;
    }
    else{
        yiter = 1;
    }

    while(y < ymax && x < xmax){  //if there already is a letter at this index, then it must be in the prefix string
        cursquare = b->getSquare(y,x);
        c = cursquare->getLetter();
        if(c == ' '){
            break;
        }  
        prefix += c;
        x += xiter;
        y += yiter;
    }

    if(dict.isPrefix(prefix)==false){
        return;
    }

    if(dict.isLegalWord(prefix)==true){
        words.insert(prefix);
    }

    if(y > ymax || x>xmax){
        return;
    } 

    for(int i=0; i<remainingletters.size(); i++){
        string s = prefix;
        s+= remainingletters.at(i);
        string s2 = remainingletters;
        s2.erase(i, 1);
        getLegalWords(horizontal, y+yiter, x+xiter, s, s2, words, b);
    }
}

