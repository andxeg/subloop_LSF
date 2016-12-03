all : static_sheduler clean

static_sheduler: main.o snapshot.o algorithm.o tinyxml2.o
	g++ ./main.o ./snapshot.o ./algorithm.o -o ./prog_02160560_521
	
main.o: ./src/main.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/main.cpp -I ./include -I

snapshot.o: ./src/snapshot.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/snapshot.cpp -I ./include -I
	
algorithm.o: ./src/algorithm.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/algorithm.cpp -I ./include -I
	
clean:
	rm ./main.o ./snapshot.o ./algorithm.o
