
CXX = g++
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS+=-std=c++11 -Wall

all: airstrike-sfml

Aircraft.o: Sources/Aircraft.cpp
	$(CXX) -c "Sources/Aircraft.cpp" -o Aircraft.o $(CXXFLAGS)

Application.o: Sources/Application.cpp
	$(CXX) -c "Sources/Application.cpp" -o Application.o $(CXXFLAGS)

Command.o: Sources/Command.cpp
	$(CXX) -c "Sources/Command.cpp" -o Command.o $(CXXFLAGS)

CommandQueue.o: Sources/CommandQueue.cpp
	$(CXX) -c "Sources/CommandQueue.cpp" -o CommandQueue.o $(CXXFLAGS)

Entity.o: Sources/Entity.cpp
	$(CXX) -c "Sources/Entity.cpp" -o Entity.o $(CXXFLAGS)

GameState.o: Sources/GameState.cpp
	$(CXX) -c "Sources/GameState.cpp" -o GameState.o $(CXXFLAGS)

LoadingState.o: Sources/LoadingState.cpp
	$(CXX) -c "Sources/LoadingState.cpp" -o LoadingState.o $(CXXFLAGS)

MenuState.o: Sources/MenuState.cpp
	$(CXX) -c "Sources/MenuState.cpp" -o MenuState.o $(CXXFLAGS)

ParallelTask.o: Sources/ParallelTask.cpp
	$(CXX) -c "Sources/ParallelTask.cpp" -o ParallelTask.o $(CXXFLAGS)

PauseState.o: Sources/PauseState.cpp
	$(CXX) -c "Sources/PauseState.cpp" -o PauseState.o $(CXXFLAGS)

Player.o: Sources/Player.cpp
	$(CXX) -c "Sources/Player.cpp" -o Player.o $(CXXFLAGS)

SceneNode.o: Sources/SceneNode.cpp
	$(CXX) -c "Sources/SceneNode.cpp" -o SceneNode.o $(CXXFLAGS)

SpriteNode.o: Sources/SpriteNode.cpp
	$(CXX) -c "Sources/SpriteNode.cpp" -o SpriteNode.o $(CXXFLAGS)

State.o: Sources/State.cpp
	$(CXX) -c "Sources/State.cpp" -o State.o $(CXXFLAGS)

StateStack.o: Sources/StateStack.cpp
	$(CXX) -c "Sources/StateStack.cpp" -o StateStack.o $(CXXFLAGS)

TitleState.o: Sources/TitleState.cpp
	$(CXX) -c "Sources/TitleState.cpp" -o TitleState.o $(CXXFLAGS)

Utility.o: Sources/Utility.cpp
	$(CXX) -c "Sources/Utility.cpp" -o Utility.o $(CXXFLAGS)

World.o: Sources/World.cpp
	$(CXX) -c "Sources/World.cpp" -o World.o $(CXXFLAGS)

Main.o: Sources/Main.cpp
	@echo "** Compiling the game"
	$(CXX) -c "Sources/Main.cpp" -o Main.o $(CXXFLAGS)

airstrike-sfml: Main.o Aircraft.o Application.o Command.o CommandQueue.o Entity.o GameState.o LoadingState.o MenuState.o ParallelTask.o PauseState.o Player.o SceneNode.o SpriteNode.o State.o StateStack.o TitleState.o Utility.o World.o
	@echo "\n** Building the game"
	$(CXX) -o airstrike-sfml Main.o Aircraft.o Application.o Command.o CommandQueue.o Entity.o GameState.o LoadingState.o MenuState.o ParallelTask.o PauseState.o Player.o SceneNode.o SpriteNode.o State.o StateStack.o TitleState.o Utility.o World.o $(LIBS) $(CXXFLAGS)

clean:
	@echo "** Cleaning up the mess"
	$(RM) *.o airstrike-sfml
