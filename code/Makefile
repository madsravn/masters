all: balls

balls: main.o Data.o Ort.o
	clang++ -O3 -std=c++14 main.o Data.o Ort.o -o balls

main.o: main.cpp
	clang++ -c -O3 -std=c++14 main.cpp

Data.o: Data.cpp
	clang++ -c -O3 -std=c++14 Data.cpp

Ort.o: Ort.cpp
	clang++ -c -O3 -std=c++14 Ort.cpp

clean:
	rm -rf *.o balls
