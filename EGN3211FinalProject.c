/* This code is the final project for EGN3211. The goal is to create a
fully autonomous battleship game with 2 playmodes. The first playmode
should have random placements and random targeting for both players.
The second playmode should use random placements and random targeting for
player 1 and random placement and logical targeting for player 2. Playmode1
should print the boards and the results of one game and also how many moves
it took. Playmode2 only needs to display metrics.
The author is Isaac Bennett
Created 4/4/2026 - Created board design, board matrix, and functions for playmodes.
4/5/2026 - Finished initial function to ask for playmode.
4/7/2026 - Created and finished initialize board and shortened main.
4/11/2026 - Created print board and shortened main. Also created ships placement function.
4/14/2026 - Finished print board and ships placement functions.
4/19/2026 - Created and finished random shot function. Finished playmode1.
4/25/2026 - Created and finished count remaining ships function and finished playmode2.
4/27/2026 - Added comments.
Compiled in Microsoft Visual Studio */
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

struct BoardMatrix { // Define structure.
    char board[10][10]; // Declare board array.
};

void initialize_board(struct BoardMatrix* b); // Function to initialize board.
void print_board(struct BoardMatrix* b); // Function to print board.
int ships_placement(struct BoardMatrix* b, int row, int col, int size, int direction); // Function to place ships.
void PlayMode(void); // Function to select play mode.
void PlayMode1(void); // Function for playmode 1.
void PlayMode2(void); // Function for playmode 2.
int count_remaining_ships(struct BoardMatrix* b); // Function to count ships.
void random_shot(struct BoardMatrix* b, int* col, int* row); // Function to generate random shot.

int main(void) { // Function main begins program execution.
    struct BoardMatrix board; // Declare board variable.
    srand((unsigned)time(NULL)); // Initialize random number generator.
    PlayMode(); // Call play mode function.
    return 0;
}

void PlayMode(void) { // Function to select playmode.
    int input = 0; // Initialize input.
    while (1) { // Loop until valid input.
        printf("Please input 1 or 2 for respective Playmodes: "); // Display to user.
        if (scanf_s("%d", &input) != 1) { // Gather input from keyboard.
            int c; // Initialize c.
            while ((c = getchar()) != EOF && c != '\n'); // Delete invalid input.
            continue;
        }
        if (input == 1) { // Determine if input is 1.
            PlayMode1(); // Call PlayMode1.
            break;
        }
        else if (input == 2) { // Determine if input is 2.
            PlayMode2(); // Call PlayMode2.
            break;
        }
        else {
            printf("Only 1 or 2 may be input.\n"); // Display to user.
        }
    }
}

void PlayMode1(void) { // Function for playmode 1.
    struct BoardMatrix board1; // Declare board1.
    struct BoardMatrix board2; // Declare board2.
    initialize_board(&board1); // Initialize board1.
    initialize_board(&board2); // Initialize board2.
    // srand calls ships placement and determines random numbers for ships placement until  
    // board matrix is full. Each while statement is for each individual ships based on length 
    // and the rest are parameters (to keep the inputs between 0-9). Time library is used for
    // randomness at every compilation. 
    while (!ships_placement(&board1, rand() % 10, rand() % 6, 5, rand() % 2)) {} // Place ships.
    while (!ships_placement(&board1, rand() % 10, rand() % 7, 4, rand() % 2)) {}
    while (!ships_placement(&board1, rand() % 10, rand() % 8, 3, rand() % 2)) {}
    while (!ships_placement(&board1, rand() % 10, rand() % 8, 3, rand() % 2)) {}
    while (!ships_placement(&board1, rand() % 10, rand() % 9, 2, rand() % 2)) {}
    while (!ships_placement(&board2, rand() % 10, rand() % 6, 5, rand() % 2)) {} // Place ships.
    while (!ships_placement(&board2, rand() % 10, rand() % 7, 4, rand() % 2)) {}
    while (!ships_placement(&board2, rand() % 10, rand() % 8, 3, rand() % 2)) {}
    while (!ships_placement(&board2, rand() % 10, rand() % 8, 3, rand() % 2)) {}
    while (!ships_placement(&board2, rand() % 10, rand() % 9, 2, rand() % 2)) {}
    int remaining1 = count_remaining_ships(&board1); // Initialize remaining ships for board1.
    int remaining2 = count_remaining_ships(&board2); // Initialize remaining ships for board2.
    int turn = 0; // Initialize turn.
    int rounds = 0; // Initialize rounds.
    printf("\nPlayMode1\n"); // Display to user.
    printf("----------------------------------------------------------------------------------------\n"); // Display to user.
    printf("Initial Friendly board:\n"); // Display to user.
    printf("---------1-------2-------3-------4-------5-------6-------7-------8-------9-------10-----\n"); // Display to user.
    print_board(&board1); // Function to print board.
    printf("----------------------------------------------------------------------------------------\n"); // Display to user.
    printf("Initial Enemy board:\n"); // Display to user.
    printf("---------1-------2-------3-------4-------5-------6-------7-------8-------9-------10-----\n"); // Display to user.
    print_board(&board2); // Function to print board.
    printf("----------------------------------------------------------------------------------------\n"); // Display to user.
    while (remaining1 > 0 && remaining2 > 0) { // Loop until game ends.
        int row; // Declare row.
        int col; // Declare column.
        if (turn == 0) { // Determine turn.
            random_shot(&board2, &col, &row); // Generate random shot.
            if (board2.board[row][col] == '|') { // Determine hit.
                board2.board[row][col] = 'X'; // Store hit.
                --remaining2; // Decrement ships.
            }
            else {
                board2.board[row][col] = '0'; // Store miss. 
            }
        }
        else {
            random_shot(&board1, &col, &row); // Generate random shot.
            if (board1.board[row][col] == '|') { // Determine hit.
                board1.board[row][col] = 'X'; // Store hit.
                --remaining1; // Decrement ships.
            }
            else {
                board1.board[row][col] = '0'; // Store miss. 
            }
        }
        turn = 1 - turn; // Alternate turn.
        ++rounds; // Increment rounds.
    }
    printf("\nGame finished in %d moves.\n\n", rounds); // Display to user.
    if (remaining1 == 0 && remaining2 == 0) { printf("\nTie.\n\n"); } // Display to user.
    else if (remaining2 == 0) { printf("\nPlayer 1 wins.\n\n"); } // Display to user.
    else { printf("\nPlayer 2 wins.\n"); } // Display to user.
    printf("----------------------------------------------------------------------------------------\n"); // Display to user.
    printf("Final Friendly board:\n"); // Display to user.
    printf("---------1-------2-------3-------4-------5-------6-------7-------8-------9-------10-----\n"); // Display to user.
    print_board(&board1); // Function to print board.
    printf("----------------------------------------------------------------------------------------\n"); // Display to user.
    printf("Final Enemy board:\n"); // Display to user.
    printf("---------1-------2-------3-------4-------5-------6-------7-------8-------9-------10-----\n"); // Display to user.
    print_board(&board2); // Function to print board.
    printf("----------------------------------------------------------------------------------------\n"); // Display to user.
}

void PlayMode2(void) { // Function for playmode 2.
    int p1_wins = 0; // Initialize p1_wins.
    int p2_wins = 0; // Initialize p2_wins.
    int total_moves = 0; // Initialize total_moves.
    int games = 100; // Initialize games.
    for (int g = 0; g < games; g++) {
        struct BoardMatrix board1; // Declare board1.
        struct BoardMatrix board2; // Declare board2.
        initialize_board(&board1); // Initialize board1.
        initialize_board(&board2); // Initialize board2.
        while (!ships_placement(&board1, rand() % 10, rand() % 6, 5, rand() % 2)) {} // Place ships.
        while (!ships_placement(&board1, rand() % 10, rand() % 7, 4, rand() % 2)) {}
        while (!ships_placement(&board1, rand() % 10, rand() % 8, 3, rand() % 2)) {}
        while (!ships_placement(&board1, rand() % 10, rand() % 8, 3, rand() % 2)) {}
        while (!ships_placement(&board1, rand() % 10, rand() % 9, 2, rand() % 2)) {}
        while (!ships_placement(&board2, rand() % 10, rand() % 6, 5, rand() % 2)) {} // Place ships.
        while (!ships_placement(&board2, rand() % 10, rand() % 7, 4, rand() % 2)) {}
        while (!ships_placement(&board2, rand() % 10, rand() % 8, 3, rand() % 2)) {}
        while (!ships_placement(&board2, rand() % 10, rand() % 8, 3, rand() % 2)) {}
        while (!ships_placement(&board2, rand() % 10, rand() % 9, 2, rand() % 2)) {}
        char track[10][10]; // Declare track array.
        for (int i = 0; i < 10; i++) { // Initialize rows.
            for (int j = 0; j < 10; j++) { // Initialize columns.
                track[i][j] = ' '; // Store blank space.
            }
        }
        int remaining1 = count_remaining_ships(&board1); // Initialize remaining ships.
        int remaining2 = count_remaining_ships(&board2); // Initialize remaining ships.
        int turn = 0; // Initialize turn.
        int rounds = 0; // Initialize rounds.
        while (remaining1 > 0 && remaining2 > 0) { // Loop until game ends.
            int row; // Declare row.
            int col; // Declare column.
            if (turn == 0) { // Determine turn.
                random_shot(&board2, &col, &row); // Generate random shot.
                if (board2.board[row][col] == '|') { board2.board[row][col] = 'X'; --remaining2; }
                else { board2.board[row][col] = '0'; }
            }
            else {
                int shot = 0; // Initialize shot.
                for (int r = 0; r < 10 && !shot; r++) { // Loop rows.
                    for (int c = 0; c < 10 && !shot; c++) { // Loop columns.
                        if (track[r][c] != ' ') continue;
                        row = r; col = c;
                        if (board1.board[row][col] == '|') { board1.board[row][col] = 'X'; track[row][col] = 'X'; --remaining1; }
                        else { board1.board[row][col] = '0'; track[row][col] = '0'; }
                        shot = 1; // Mark shot.
                    }
                }
            }
            turn = 1 - turn; // Take turns.
            rounds++; // Increment rounds.
        }
        if (remaining2 == 0) p1_wins++; else p2_wins++;
        total_moves += rounds;
    }
    printf("\nGames: %d\n", games); // Display to user.
    printf("\nPlayer 1 Wins: %d", p1_wins); // Display to user.
    printf("\nPlayer 2 Wins: %d", p2_wins); // Display to user. 
    printf("\nAverage Moves: %d\n", total_moves / games); // Display to user.
}

void initialize_board(struct BoardMatrix* b) { // Function to initialize board.
    for (int row = 0; row < 10; row++) { // Initialize rows.
        for (int col = 0; col < 10; col++) { // Initialize columns.
            b->board[row][col] = ' '; // Store blank space.
        }
    }
}

int ships_placement(struct BoardMatrix* b, int row, int col, int size, int direction) { // Function to place ships.
    if (direction) { // Determine direction.
        if (col + size > 10) return 0;
        for (int i = 0; i < size; i++) { if (b->board[row][col + i] != ' ') return 0; }
        for (int i = 0; i < size; i++) {
            b->board[row][col + i] = '|'; // Store values.
        }
    }
    else { // Determine opposite direction.
        if (row + size > 10) return 0;
        for (int i = 0; i < size; i++) { if (b->board[row + i][col] != ' ') return 0; }
        for (int i = 0; i < size; i++) {
            b->board[row + i][col] = '|'; // Store values.
        }
    }
    return 1;
}

int count_remaining_ships(struct BoardMatrix* b) { // Function to count ships.
    int count = 0; // Initialize count.
    for (int row = 0; row < 10; row++) { // Loop rows.
        for (int col = 0; col < 10; col++) { // Loop columns.
            if (b->board[row][col] == '|') { // Determine ship.
                count++; // Increment.
            }
        }
    }
    return count;
}

void random_shot(struct BoardMatrix* b, int* col, int* row) { // Function to generate random shot.
    int r; // Declare row.
    int c; // Declare column.
    do {
        r = rand() % 10; c = rand() % 10; // Generate row and column.
    } while (b->board[r][c] == 'X' || b->board[r][c] == '0'); // New shot.
    *row = r; // Store row.
    *col = c; // Store column.
}

void print_board(struct BoardMatrix* b) { // Function to print board.
    for (int row = 0; row < 10; row++) { // Loop rows.
        char label = 'A' + row; // Initialize label.
        printf("|%c\t", label); // Display to user.
        for (int col = 0; col < 10; col++) { // Loop columns.
            printf("[%c]\t", b->board[row][col]); // Display to user.
        }
        printf("|\n"); // Display to user.
    }
}