
CXX = g++
CXXFLAGS += -Wall -std=c++11

all: vectors

Vector2.o: Vector2.cpp
	$(CXX) -c "Vector2.cpp" -o Vector2.o $(CXXFLAGS)

Main.o: Main.cpp
	$(CXX) -c "Main.cpp" -o Main.o $(CXXFLAGS)

vectors: Main.o Vector2.o
	$(CXX) -o vectors Main.o Vector2.o $(CXXFLAGS)

clean:
	$(RM) *.o vectors
