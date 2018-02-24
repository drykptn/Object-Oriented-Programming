all: run1 run2 clean

run1: _mainTester.o
	g++ CPUProgram.cpp CPU.cpp Memory.cpp Computer.cpp _mainTester.cpp -o _mainTester -std=c++11
	./_mainTester file.txt 0

run2:
	./_mainTester file.txt 1
run3:
	./_mainTester file.txt 2
clean:
	rm *.o _mainTester
