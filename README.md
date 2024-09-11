# Advanced Tic-Tac-Toe

This is an advanced version(Somehow) of Tic-Tac-Toe implemented in C, featuring a 9x9 grid where each 3x3 sub-grid functions as a traditional Tic-Tac-Toe game.

## Features
- **Ultimate Tic-Tac-Toe:** Each player must win individual sub-grids to control the larger grid.
- **Computer Opponent:** The program includes a basic AI that competes against the player.
- **Interactive Gameplay:** Players take turns to mark sub-grids, and the game updates dynamically.

## How to Play
1. The game will prompt you to pick a square inside a sub-grid at first.
2. After your move, the computer should choose a square in the sub-grid which was chosen by the previous player move.
3. For example: if player choose the the middle square in a sub-grid, next player (Computer here) should choose a square in the middle sub-grid, and the same goes for Player.
4. Players must win multiple sub-grids to control the main grid and win the game.

## Compilation and Execution
Compile the program using `gcc`:
```bash
make # or gcc -o xo XO.c
./xo
