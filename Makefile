all : sheduler clean_objective

sheduler: Main.o TaskReader.o Algorithm.o Task.o TaskContainer.o
	g++ ./Main.o ./TaskReader.o ./Algorithm.o ./Task.o ./TaskContainer.o -o ./prog_02160560_521
	
Main.o: ./src/Main.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/Main.cpp -I ./include

TaskReader.o: ./src/TaskReader.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/TaskReader.cpp -I ./include
	
Algorithm.o: ./src/Algorithm.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/Algorithm.cpp -I ./include

Task.o: ./src/Task.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/Task.cpp -I ./include

TaskContainer.o: ./src/TaskContainer.cpp
	g++ -O2 -g -Wall -std=c++0x -c ./src/TaskContainer.cpp -I ./include
	
clean_objective:
	rm ./Main.o ./TaskReader.o ./Algorithm.o ./Task.o ./TaskContainer.o

clean:
	rm ./prog_02160560_521

