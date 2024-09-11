# Advanced Tic-Tac-Toe

This is an advanced version of Tic-Tac-Toe implemented in C, featuring a 9x9 grid where each 3x3 sub-grid functions as a traditional Tic-Tac-Toe game.

## Features
- **Ultimate Tic-Tac-Toe:** Each player must win individual sub-grids to control the larger grid.
- **Computer Opponent:** The program includes a basic AI that competes against the player.
- **Interactive Gameplay:** Players take turns to mark sub-grids, and the game updates dynamically.

## How to Play
1. The game will prompt you to pick a sub-grid and square.
2. After your move, the computer will choose a square in the same sub-grid.
3. The game continues until either player wins a sub-grid or the sub-grid ends in a tie.
4. Players must win multiple sub-grids to control the main grid and win the game.

## Compilation and Execution
Compile the program using `gcc`:
```bash
make
./exec
