CC := g++
CFLAGS := -Wall -g -std=c++11
TARGET := test

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o
	
.PHONY: all clean
# all: scrabble

# scrabble: scrabble.cpp bag.o dictionary.o board.o consolePrinter.o
# 	g++ -g -std=c++11 -Wconversion -Wextra -Wall scrabble.cpp bag.o dictionary.o player.o consolePrinter.o board.o -o scrabble

# board.o: Board.h Tile.h Square.h Move.h Dictionary.h Board.cpp 
# 	g++ -g -std=c++11 -Wconversion -Wextra -Wall move.o dictionary.o -o Board.cpp

# move.o: Tile.h Player.h Bag.h Dictionary.h move.cpp 
# 	g++ -g -std=c++11 -Wconversion -Wextra -Wall player.o dictionary.o -o move.o

# dictionary.o: Dictionary.h Dictionary.cpp
# 	g++ -g -std=c++11 -Wconversion -Wextra -Wall -c Dictionary.cpp

# player.o: Player.h Player.cpp
# 	g++ -g -std=c++11 -Wconversion -Wextra -Wall -c Player.cpp

# bag.o: Tile.h Bag.h Exceptions.h Bag.cpp
# 	g++ -g -std=c++11 -Wconversion -Wextra -Wall -c Bag.cpp

# consolePrinter.o: ConsolePrinter.h ConsolePrinter.cpp 
# 	g++ -g -std=c++11 -Wconversion -Wextra -Wall -o consolePrinter.cpp
