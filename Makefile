all : sheduler clean_objective

sheduler: Main.o TaskReader.o Algorithm.o Task.o TaskContainer.o
	g++ ./Main.o ./TaskReader.o ./Algorithm.o ./Task.o ./TaskContainer.o -o ./prog_02160560_521
	
Main.o: ./src/Main.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/Main.cpp

TaskReader.o: ./src/TaskReader.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/TaskReader.cpp
	
Algorithm.o: ./src/Algorithm.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/Algorithm.cpp

Task.o: ./src/Task.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/Task.cpp

TaskContainer.o: ./src/TaskContainer.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/TaskContainer.cpp
	
clean_objective:
	rm -rf ./Main.o ./TaskReader.o ./Algorithm.o ./Task.o ./TaskContainer.o

clean:
	rm -rf ./prog_02160560_521 ./Main.o ./TaskReader.o ./Algorithm.o ./Task.o ./TaskContainer.o

