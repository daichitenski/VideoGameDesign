CC=g++
INCLUDES=-I../includes
CFLAGS=-O0 $(INCLUDES) -g -Wall -Wextra
LPATHS=-L../lib/linux/
LDFLAGS:=-lSDL -lSDL_mixer -lSDL_ttf
SOURCES=cards.cpp sound.cpp
OBJECTS=$(SOURCES:.c=.o)
BINARY=cards_n_stuff

all: $(BINARY) $(OBJECTS)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	 $(CC) $(CFLAGS) $(LPATHS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm -v $(BINARY) *.o
