CXX = arch -x86_64 /usr/bin/g++ # g++ 
CXXFLAGS = -std=c++17 -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


all: monolympic

monolympic: *.cpp
	$(CXX) $(CXXFLAGS) -o monolympic ./*.cpp $(LIBS)
	./monolympic


clean:
	rm -f monolympic
