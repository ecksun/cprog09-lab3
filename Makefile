all: compile clean

compile:
	g++ actor.h container.h environment.h human.h inside.h object.h outside.h room.h troll.h wizard.h
clean:
	rm *.gch
