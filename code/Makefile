all: balls

balls: main.o Data.o Ort.o KDTree.o
	clang++ -O3 -std=c++14 main.o Data.o Ort.o KDTree.o -o balls

main.o: main.cpp
	clang++ -c -O3 -std=c++14 main.cpp

Data.o: Data.cpp
	clang++ -c -O3 -std=c++14 Data.cpp

Ort.o: Ort.cpp
	clang++ -c -O3 -std=c++14 Ort.cpp

KDTree.o: KDTree.cpp
	clang++ -c -O3 -std=c++14 KDTree.cpp

clean:
	rm -rf *.o balls
