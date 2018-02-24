all: run1 run2 clean

run1: hw1.o
	g++ hw1.o -o hw
	./hw filename.txt 0

run2:
	./hw filename.txt 1

clean:
	rm *.o hw
