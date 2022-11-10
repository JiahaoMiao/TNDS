ROOT:= `root-config --libs` `root-config --cflags`
CXXFLAGS := -g -Wall --pedantic 
LIBS := format.o
INC := -I ../

millikan:millikan.o $(LIBS)
	g++ -o $@ $^ $(CXXFLAGS) $(ROOT)  $(INC)
millikan.o:millikan.cpp 
	g++ -c $< $(CXXFLAGS) $(ROOT) $(INC)

analisi:analisi.o Library.hpp
	g++ -o $@ $^ $(CXXFLAGS) 
analisi.o:analisi.cpp Library.hpp
	g++ -c $< $(CXXFLAGS) 
format.o:../format.cc ../fmtlib.h
	g++ -c $<
clean:
	rm -f *.o
cleanall:clean	
	rm -f millikan
