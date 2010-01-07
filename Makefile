SHELL=/bin/sh
CC=g++
CDFLAGS=-c -Wall -Wextra
LDFLAGS=
SOURCES=actor.cpp bag.cpp default_weapon.cpp environment.cpp evil_lair.cpp exit.cpp food.cpp game.cpp game_commands.cpp inside.cpp key.cpp light_saber.cpp object.cpp player.cpp room.cpp terminal.cpp troll.cpp vampire.cpp vampire_factory.cpp weapon.cpp
OBJECTS=$(SOURCES:.cpp=.o) # Substitution variable that turns a list of *.cpp to *.o
EXECUTABLE=da_game

all: $(SOURCES) $(EXECUTABLE)

# $@ expands to the file name of the target
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Implicit rule (http://www.gnu.org/software/make/manual/make.html#Implicit-Rules)
# Double-suffix rule (old-fashioned way of implicit rules)
.cpp.o:
	$(CC) $(CDFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)

run: all
	./$(EXECUTABLE)

