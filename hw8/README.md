I only have the Trie working, so please don't doc me 10 points for using starter code, thanks.
I have an AI.h file that and a CPUL.cpp file that inherits from it and neither works, but it uses the idea of backtracking in the context of scrabble board positions.
The getLegalWords() function in AI.h is suppose to get all the legal words on a specific square on the Scrabble board,
which is then supposed to be used by the virtual function doBestMove() on every possible square a move can be done on on the Scrabble board,
eventually comparing the sets of possible words on every square and returning a string with the best move, which would change with the type of AI.
