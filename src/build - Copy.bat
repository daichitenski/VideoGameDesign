#set path=%~d0\mingw\bin;.;
g++ -w -enable-auto-import LuckyB.cpp StateBasedGame.cpp MainMenu.cpp Button.cpp BackgroundImage.cpp -o ../bin/cards_n_stuff.exe -I headers -L ../bin -L C:\Libraries\ -lmingw32 -lSDLmain -lSDL -lSDL_ttf 
pause
