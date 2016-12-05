all : sheduler clean

sheduler: main.o snapshot.o algorithm.o
	g++ ./Main.o ./TaskReader.o ./Algorithm.o ./Task.o ./TaskContainer.o -o ./prog_02160560_521
	
Main.o: ./src/Main.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/Main.cpp -I ./include -I

TaskReader.o: ./src/TaskReader.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/TaskReader.cpp -I ./include -I
	
Algorithm.o: ./src/Algorithm.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/Algorithm.cpp -I ./include -I

Task.o: ./src/Task.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/Task.cpp -I ./include -I

TaskContainer.o: ./src/TaskContainer.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/TaskContainer.cpp -I ./include -I
	
clean:
	rm ./Main.o ./TaskReader.o ./Algorithm.o ./Task.o ./TaskContainer.o
