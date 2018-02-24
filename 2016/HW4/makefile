all: run1 run2 clean

run1: driver.o
	g++ CPUProgram.cpp CPU.cpp Memory.cpp Computer.cpp driver.cpp -o driver -std=c++11
	./driver file.txt 0

run2:
	./driver file.txt 1
run3:
	./driver file.txt 2
clean:
	rm *.o driver
