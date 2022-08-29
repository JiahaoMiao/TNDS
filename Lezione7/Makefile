LIBS:= `root-config --libs` `root-config --cflags`
CXXFLAGS = -g -Wall --pedantic -std=c++11 
DIR = -I ../ -I ../../

esercizio7.0.o:esercizio7.0.cpp integrale.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR)
esercizio7.0:esercizio7.0.o ../format.o
	g++ -o $@ $^ $(CXXFLAGS) $(DIR)
esercizio7.1.o:esercizio7.1.cpp integrale.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR)
esercizio7.1:esercizio7.1.o ../format.o
	g++ -o $@ $^ $(CXXFLAGS) $(DIR) && ./esercizio7.1
test_runtime.o:test_runtime.cpp integrale.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR)
test_runtime:test_runtime.o ../format.o
	g++ -o $@ $^ $(CXXFLAGS) $(DIR) && ./test_runtime