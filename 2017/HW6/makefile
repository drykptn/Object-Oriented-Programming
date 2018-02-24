all: exe 

exe: main.o GTUSet.o GTUIterator.o GTUMap.o 
	g++ GTUSet.o GTUIterator.o GTUMap.o main.o -o exe

main.o: main.cpp
	g++ -c main.cpp -std=c++11 

GTUMap.o: GTUMap.cpp
	g++ -c GTUMap.cpp -std=c++11 
GTUIterator.o: GTUIterator.cpp
	g++ -c GTUIterator.cpp -std=c++11 

GTUSet.o: GTUSet.cpp
	g++ -c GTUSet.cpp -std=c++11 

clean:
	rm *.o exe
