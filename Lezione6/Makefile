LIBS:= `root-config --libs` `root-config --cflags`
CXXFLAGS = -g -Wall --pedantic -std=c++11 
DIR = -I ../ -I ../../

solutore.o:solutore.cpp solutore.h
	g++ -c -o $@  $< $(CXXFLAGS)

clean:
	rm -f *.o 
cleanall: clean
	rm -f *.o 