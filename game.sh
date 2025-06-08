g++ -c -w main.cpp
g++ main.o -o game_executable -lsfml-graphics -lsfml-window -lsfml-system
./game_executable
rm main.o
rm game_executable