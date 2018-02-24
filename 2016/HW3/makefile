all: run1 run2 clean

run1: driver.o
	g++ CPUProgram.cpp CPU.cpp driver.cpp -o driver -std=c++11
	./driver filename.txt 0

run2:
	./driver filename.txt 1

clean:
	rm *.o driver
