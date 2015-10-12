
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: sfml-app

main.o: main.cpp
	@echo "** Compiling the game"
	g++ -c "main.cpp" -o main.o

sfml-app: main.o
	@echo "** Building the game"
	g++ -o sfml-app main.o $(LIBS)

clean:
	@echo "** Cleaning up working directory"
	rm -f sfml-app *.o
