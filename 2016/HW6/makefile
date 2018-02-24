all: _mainTester

_mainTester: _mainTester.o CPU.o CPUProgramDyn.o Memory.o Computer.o
	g++ _mainTester.o CPU.o CPUProgramDyn.o Memory.o Computer.o -o testexe

_mainTester.o : _mainTester.cpp
	g++ -c _mainTester.cpp -std=c++11

CPU.o :	CPU.cpp
	g++ -c CPU.cpp -std=c++11

CPUProgramDyn.o : CPUProgramDyn.cpp
	g++ -c CPUProgramDyn.cpp -std=c++11

Memory.o : Memory.cpp
	g++ -c Memory.cpp -std=c++11

Computer.o : Computer.cpp
	g++ -c Computer.cpp -std=c++11

clean: 
	rm *.o exe testexe

run: 
	./exe file.txt 0

run1: 
	./exe file.txt 1

run2: 
	./exe file.txt 2

runtest: 
	./testexe file.txt 0
