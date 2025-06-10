# Snake
A snake game written in c using ncurses.

## Gameplay
Simply use the w, a, s, and d keys to navigate  the snake around the terminal and try not to hit yourself or the walls. Eat the food that randomly spawns in to increase the length of your snake.

## Build
To build the game, execute the following commands within the source directory:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```
This produces an executable by the name of 'snake' in the build directory.