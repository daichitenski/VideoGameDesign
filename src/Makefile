CC=g++ -std=c++0x
INCLUDES=-I../includes
CFLAGS=-O0 $(INCLUDES) -g -Wall -Wextra
LPATHS=
LDFLAGS:=-lSDL -lSDL_mixer -lSDL_ttf
SOURCES=BackgroundImage.cpp Board.cpp Button.cpp Card.cpp CardImage.cpp Computer.cpp Deck.cpp Discard.cpp Game.cpp Hand.cpp LuckyB.cpp Player.cpp Slider.cpp SlidingCard.cpp sound.cpp TextImage.cpp
OBJECTS=$(SOURCES:.c=.o)
BINARY=cards_n_stuff

all: $(BINARY) $(OBJECTS)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	 $(CC) $(CFLAGS) $(LPATHS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm -v $(BINARY) *.o
