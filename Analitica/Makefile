LIBS:= `root-config --libs` `root-config --cflags`
CXXFLAGS = -g -Wall --pedantic -std=c++11
DIR = -I ../ -I ../../

Pendolo.o:Pendolo.cpp funzioneVettorialeBase.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) $(LIBS)
Pendolo:Pendolo.o ../format.o 
	g++ -o $@ $^ $(CXXFLAGS) $(DIR) $(LIBS) && ./$@

Gravitazione.o:Gravitazione.cpp funzioneVettorialeBase.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) $(LIBS) 
Gravitazione:Gravitazione.o ../format.o 
	g++ -o $@ $^ $(CXXFLAGS) $(DIR) $(LIBS) && ./$@

clean:
	rm *.o
cleanall:
	rm provaAlgebra Pendolo Oscillatore_Armonico_Forzato Risonanza 
