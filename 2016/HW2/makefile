all: run1 run2 run3 clean

run1: main.o
	g++ main.o -o main
	./main filename.txt 0

run2:
	./main filename.txt 1

run3:
	./main filename.txt 2
	
clean:
	rm *.o main
