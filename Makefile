CC=g++
CDFLAGS=-c -Wall -Wextra
LDFLAGS=
SOURCES=game.cpp troll.cpp food.cpp terminal.cpp
# Substitution variable that turns a list of *.cpp to *.o
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=da_game

all: $(SOURCES) $(EXECUTABLE)

# $@ expands to prerequisities
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Implicit rule (http://www.gnu.org/software/make/manual/make.html#Implicit-Rules)
.cpp.o:
	$(CC) $(CDFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)

run: all
	./$(EXECUTABLE)

