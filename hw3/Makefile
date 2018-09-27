all: parser

parser: parser.cpp stackint.o 
	g++ -g -std=c++11 -Wconversion -Wextra -Wall parser.cpp stackint.o circular_list_int.o -o parser

stackint.o: stackint.h stackint.cpp circular_list_int.o 
	g++ -g -std=c++11 -Wconversion -Wextra -Wall -c stackint.cpp circular_list_int.o -o stackint.o

circular_list_int.o: circular_list_int.cpp circular_list_int.h 
	g++ -g -std=c++11 -Wconversion -Wextra -Wall -c circular_list_int.cpp -o circular_list_int.o