
CXX = g++
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS+=-std=c++11 -Wall

all: airstrike-sfml

Game.o: Sources/Game/Game.cpp
	$(CXX) -c "Sources/Game/Game.cpp" -o Game.o $(CXXFLAGS)

Main.o: Sources/Main.cpp
	@echo "** Compiling the game"
	$(CXX) -c "Sources/Main.cpp" -o Main.o $(CXXFLAGS)

airstrike-sfml: Main.o Game.o
	@echo "\n** Building the game"
	$(CXX) -o airstrike-sfml Main.o Game.o $(LIBS) $(CXXFLAGS)

clean:
	@echo "** Cleaning up the mess"
	$(RM) *.o airstrike-sfml
