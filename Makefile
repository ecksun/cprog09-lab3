FILES=game.cpp
FLAGS=-o da_game

all: compile clean

compile:
	g++ $(FILES) $(FLAGS)

clean:
	rm -f *.gch

run: all
	./da_game
