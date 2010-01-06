SHELL=/bin/sh
CC=g++
CDFLAGS=-c -Wall -Wextra
LDFLAGS=
SOURCES=bag.cpp food.cpp game.cpp game_commands.cpp player.cpp room.cpp terminal.cpp troll.cpp object.cpp actor.cpp environment.cpp inside.cpp evil_lair.cpp vampire_factory.cpp vampire.cpp weapon.cpp default_weapon.cpp light_saber.cpp
# Substitution variable that turns a list of *.cpp to *.o
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=da_game

all: $(SOURCES) $(EXECUTABLE)

# $@ expands to the file name of the target
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Implicit rule (http://www.gnu.org/software/make/manual/make.html#Implicit-Rules)
.cpp.o:
	$(CC) $(CDFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)

run: all
	./$(EXECUTABLE)

