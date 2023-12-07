run:
	g++ -std=c++11  -I /usr/include/jsoncpp -L /usr/lib -ljsoncpp main.cpp -o main.o && ./main.o

default:
	g++ -I /opt/homebrew/include -L /usr/lib -ljson main.cpp -o main.o 