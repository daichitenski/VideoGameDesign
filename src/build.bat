set path=%~d0\mingw\bin;.;
g++ -enable-auto-import cards.cpp -o ../bin/cards_n_stuff.exe -I headers -L ../bin -lmingw32 -lSDLmain -lSDL -lSDL_ttf 
pause
