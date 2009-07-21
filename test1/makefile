OBJECTS = wordstat.o word.o list.o

wordstat : $(OBJECTS)
	cc -o wordstat $(OBJECTS)

wordstat.o : helpdoc.h word.h list.h
word.o : word.h list.h
list.o : list.h

.PHONY : clean
clean :
	rm $(OBJECTS)
