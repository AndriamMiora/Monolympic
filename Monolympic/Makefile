CXX = g++
CXXFLAGS = -std=c++11
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


all: mon_programme

mon_programme: *.cpp
	$(CXX) $(CXXFLAGS) -o mon_programme ./*.cpp $(LIBS)
	./mon_programme

clean:
	rm -f mon_programme
