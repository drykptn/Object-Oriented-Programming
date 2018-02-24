all: exe 

exe: main.o ConnectFour.o
	g++ ConnectFour.o main.o -o exe

main.o: main.cpp
	g++ -c main.cpp -std=c++11 

ConnectFour.o: ConnectFour.cpp
	g++ -c ConnectFour.cpp -std=c++11 

clean:
	rm *.o exe