CC = gcc
CFLAGS = -Wall -pg


OBJECTS = wordstat.o word.o list.o
TARGET = wordstat

default:$(TARGET)

SOURCE = 

wordstat : $(OBJECTS)
	$(CC) $(CFLAGS)  -o wordstat $(OBJECTS)

wordstat.o : helpdoc.h word.h list.h
word.o : word.h list.h
list.o : list.h

.PHONY : clean
clean :
	rm $(OBJECTS)
