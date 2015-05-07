
#CFLAGS	= -g -O0 -pg -ggdb
CFLAGS = -O3

all: balls

balls: main.o Data.o Ort.o KDTree.o Tester.o
	clang++ $(CFLAGS) -std=c++11 main.o Tester.o Data.o Ort.o KDTree.o -o balls

main.o: main.cpp
	clang++ -c $(CFLAGS) -std=c++11 main.cpp

Data.o: Data.cpp
	clang++ -c $(CFLAGS) -std=c++11 Data.cpp

Ort.o: Ort.cpp
	clang++ -c $(CFLAGS) -std=c++11 Ort.cpp

KDTree.o: KDTree.cpp
	clang++ -c $(CFLAGS) -std=c++11 KDTree.cpp

Tester.o: Tester.cpp
	clang++ -c $(CFLAGS) -std=c++11 Tester.cpp

clean:
	rm -rf *.o balls
