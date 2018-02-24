all: _mainTesterMap _mainTesterDyn

_mainTesterMap: _mainTester.o BigramMap.o
	g++ _mainTester.o BigramMap.o -o exe

_mainTesterDyn:_mainTester.o BigramDyn.o
	g++ _mainTester.o BigramDyn.o -o exe

_mainTester.o : _mainTester.cpp
	g++ -c _mainTester.cpp -std=c++11

BigramDyn.o :	BigramDyn.cpp
	g++ -c BigramDyn.cpp -std=c++11

BigramMap.o : BigramMap.cpp
	g++ -c BigramMap.cpp -std=c++11

clean: 
	rm *.o exe

runMap1: 
	./exe t1.txt 1 1

runMap2: 
	./exe t2.txt 2 1

runMap3: 
	./exe t3.txt 3 1

runMap4: 
	./exe t4.txt 1 1

runMap5: 
	./exe t5.txt 3 1

runDyn1:
	./exe t1.txt 1 2

runDyn2: 
	./exe t2.txt 2 2

runDyn3: 
	./exe t3.txt 3 2

runDyn4: 
	./exe t4.txt 1 2

runDyn5: 
	./exe t5.txt 3 2
