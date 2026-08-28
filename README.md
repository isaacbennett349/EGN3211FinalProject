# EGN3211FinalProject
# EGN3211 Final Project: Autonomous Battleship Game

## Project Goal
The goal of this project is to create a fully autonomous Battleship game with 2 different playmodes. It was written in standard C and compiled using Microsoft Visual Studio.

## How the Playmodes Work
* **Playmode 1:** Uses random ship placements and random targeting for both players. It prints out the boards to the screen, shows the results of one game, and displays how many moves it took to finish.
* **Playmode 2:** Uses random ship placements and random targeting for Player 1, but uses random placement and logical targeting for Player 2. It runs 100 games back-to-back and only displays the final metrics (total wins and average moves).

## C Features Used
* **Structures (`struct BoardMatrix`):** Used to declare the 10x10 board arrays so they can be managed easily.
* **Pointers:** Used to pass the board structures into functions by reference (like `&board1`) to update the grids without wasting memory.
* **Random Numbers (`rand` & `time.h`):** Seeds the random number generator using the time library so the placements and shots change every time you compile the code.
* **Input Cleaning Loop:** Uses a `while` loop with `getchar()` to clear out invalid inputs if a user accidentally types something other than 1 or 2.

## How to Run It
1. Open **Microsoft Visual Studio**.
2. Create a project and add `main.c`.
3. Make sure your project settings are set to compile as C code.
4. Click **Local Windows Debugger** to run the program.
  
