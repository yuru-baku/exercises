run:
	g++ -std=c++23  -I /usr/include/jsoncpp -L /usr/lib -ljsoncpp -Wall -Wextra -Wpedantic main.cpp -o main.o && ./main.o