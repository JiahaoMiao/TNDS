LIBS:= `root-config --libs` `root-config --cflags`
CXXFLAGS = -g -Wall --pedantic -std=c++11
DIR = -I ../ -I ../../

randomGen.o:randomGen.cpp randomGen.h
	g++ -c -o $@ $< $(CXXFLAGS)

Esercizio10.0.o:Esercizio10.0.cpp 
	g++ -c -o $@ $< $(CXXFLAGS) $(LIBS) $(DIR)
Esercizio10.0:Esercizio10.0.o randomGen.o ../format.o
	g++ -o $@ $^ $(CXXFLAGS)  $(LIBS) $(DIR) && ./$@

Esercizio10.1.o:Esercizio10.1.cpp
	g++ -c -o $@ $< $(CXXFLAGS) $(LIBS) $(DIR)
Esercizio10.1:Esercizio10.1.o randomGen.o ../format.o
	g++ -o $@ $^ $(CXXFLAGS) $(LIBS) $(DIR)

Esercizio10.2.o:Esercizio10.2.cpp funzioneBase.h integraleMC.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) -fopenmp
Esercizio10.2:Esercizio10.2.o randomGen.o ../format.o
	g++  -o $@ $^ $(CXXFLAGS) $(DIR) -fopenmp

Analisi10.2.o:Analisi10.2.cpp
	g++ -c -o $@ $< $(CXXFLAGS) $(LIBS) $(DIR) 
Analisi10.2:Analisi10.2.o ../format.o
	g++  -o $@ $^ $(CXXFLAGS) $(LIBS) $(DIR) -fopenmp && ./$@

Esercizio10.3.o:Esercizio10.3.cpp
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) $(LIBS) -fopenmp
Esercizio10.3:Esercizio10.3.o randomGen.o ../format.o
	g++  -o $@ $^ $(CXXFLAGS) $(DIR) $(LIBS) -fopenmp && ./$@

Esercizio10.4.o:Esercizio10.4.cpp funzioneScalareBase.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) -fopenmp
Esercizio10.4:Esercizio10.4.o randomGen.o ../format.o
	g++  -o $@ $^ $(CXXFLAGS) $(DIR) -fopenmp

Analisi10.4.o:Analisi10.4.cpp
	g++ -c -o $@ $< $(CXXFLAGS) $(LIBS) $(DIR) 
Analisi10.4:Analisi10.4.o ../format.o
	g++  -o $@ $^ $(CXXFLAGS) $(LIBS) $(DIR) -fopenmp && ./$@


prova.o:prova.cpp integraleMC.h funzioneBase.h
	g++ -c -o $@ $< $(CXXFLAGS) -fopenmp
prova:prova.o randomGen.o
	g++ -o $@ $^ $(CXXFLAGS) -fopenmp && ./$@

clean:
	rm -f *.o