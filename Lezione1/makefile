CXXFLAGS = -std=c++11 -g -Wall --pedantic

main: main.o funzioni.o
	g++ $(CXXFLAGS) funzioni.o main.o -o main
main.o: main.cpp funzioni.h
	g++ $(CXXFLAGS) -c main.cpp -o main.o
funzioni.o:funzioni.cpp funzioni.h
	g++ $(CXXFLAGS) -c funzioni.cpp -o funzioni.o
clean: 
	rm main
	rm *.o