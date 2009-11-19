all: compile clean

compile:
	g++ actor.h container.h envoirement.h human.h inside.h Object.h outside.h room.h troll.h wizzard.h
clean:
	rm *.gch
