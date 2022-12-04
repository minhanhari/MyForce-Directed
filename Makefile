CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=$(wildcard include/*.c) main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=MyForce

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS)