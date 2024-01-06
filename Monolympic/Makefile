CXX = g++
CXXFLAGS = -std=c++11
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: mon_programme

mon_programme: tableau.cpp Pion.cpp Des.cpp Button.cpp 
	$(CXX) $(CXXFLAGS) -o mon_programme tableau.cpp Pion.cpp Des.cpp Button.cpp $(LIBS)
	./mon_programme

clean:
	rm -f mon_programme
