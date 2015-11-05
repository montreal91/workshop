
CXX = g++
CXXFLAGS += -Wall -std=c++11

all: vectors

Vector2.o: Vector2.cpp
	$(CXX) -c "Vector2.cpp" -o Vector2.o $(CXXFLAGS)

Vector3.o: Vector3.cpp
	$(CXX) -c "Vector3.cpp" -o Vector3.o $(CXXFLAGS)

Main.o: Main.cpp
	$(CXX) -c "Main.cpp" -o Main.o $(CXXFLAGS)

vectors: Main.o Vector2.o Vector3.o
	$(CXX) -o vectors Main.o Vector2.o Vector3.o $(CXXFLAGS)

clean:
	$(RM) *.o vectors
