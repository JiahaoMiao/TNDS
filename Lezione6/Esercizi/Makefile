LIBS:= `root-config --libs` `root-config --cflags`
CXXFLAGS = -g -Wall --pedantic -std=c++11 
DIR = -I ../ -I ../../
CLASS = ../solutore.o ../../format.o

esercizio6.1.o:esercizio6.1.cpp 
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) 
esercizio6.1:esercizio6.1.o solutore.o
	g++ -o $@  $< $(CLASS) $(CXXFLAGS) $(DIR) 
esercizio6.3.o:esercizio6.3.cpp 
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) 
esercizio6.3:esercizio6.3.o solutore.o
	g++ -o $@  $< $(CLASS) $(CXXFLAGS) $(DIR)
esercizio6.5.o:esercizio6.5.cpp 
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) 
esercizio6.5:esercizio6.5.o solutore.o
	g++ -o $@  $< $(CLASS) $(CXXFLAGS) $(DIR) 
solutore.o:
	make ../solutore.o 



clean:
	rm -f *.o 
cleanall: clean
	rm -f *.o 