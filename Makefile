<<<<<<< HEAD:Makefile
CC=g++
CDFLAGS=-c -Wall -Wextra
LDFLAGS=
SOURCES=game.cpp troll.cpp food.cpp
# Substitution variable that turns a list of *.cpp to *.o
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=da_game

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Implicit rule (http://www.gnu.org/software/make/manual/make.html#Implicit-Rules)
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

# $@ expands to prerequisities
