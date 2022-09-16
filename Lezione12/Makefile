LIBS:= `root-config --libs` `root-config --cflags`
CXXFLAGS = -g -Wall --pedantic -std=c++11
DIR = -I ../ -I ../../

randomGen.o:randomGen.cpp randomGen.h
	g++ -c -o $@ $< $(CXXFLAGS)

Esercizio11.0.o:Esercizio11.0.cpp esperimentoPrisma.h
	g++ -c -o $@ $< $(CXXFLAGS) $(LIBS) $(DIR)
Esercizio11.0:Esercizio11.0.o randomGen.o ../format.o
	g++ -o $@ $^ $(CXXFLAGS)  $(LIBS) $(DIR) && ./$@

Esercizio11.1.o:Esercizio11.1.cpp attritoViscoso.h
	g++ -c -o $@ $< $(CXXFLAGS) $(LIBS) $(DIR)
Esercizio11.1:Esercizio11.1.o randomGen.o ../format.o
	g++ -o $@ $^ $(CXXFLAGS)  $(LIBS) $(DIR) && ./$@