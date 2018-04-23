
g++ -c -Iinclude ../../src/*.cpp ../../src/ECS/*.cpp
g++ -o main.exe *.o -Llib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -llua53
pause
