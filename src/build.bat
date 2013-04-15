#set path=%~d0\mingw\bin;.;
g++ -enable-auto-import cards.cpp CardImage.cpp TextImage.cpp BackgroundImage.cpp Card.cpp Deck.cpp Discard.cpp Hand.cpp LuckyB.cpp -o ../bin/cards_n_stuff.exe -I headers -L ../bin -L C:\Libraries\ -lmingw32 -lSDLmain -lSDL -lSDL_ttf 
pause
