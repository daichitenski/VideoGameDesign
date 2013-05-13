set path=%~d0\mingw\bin;.;
g++ -w -enable-auto-import CardImage.cpp TextImage.cpp BackgroundImage.cpp Card.cpp Deck.cpp Discard.cpp Hand.cpp LuckyB.cpp Board.cpp Slider.cpp Button.cpp SlidingCard.cpp Player.cpp Computer.cpp Game.cpp StateBasedGame.cpp MainMenu.cpp  -o ../bin/cards_n_stuff.exe -I headers -L ../bin -L C:\Libraries\ -lmingw32 -lSDLmain -lSDL -lSDL_ttf 
pause
