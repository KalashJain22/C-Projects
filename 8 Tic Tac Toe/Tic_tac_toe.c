#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

typedef struct {
    int player;
    int computer;
    int draw;
} Score;

int difficulty;
Score score = {.player = 0, .computer = 0, .draw = 0}; 

void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    system("cls");  //for clear screen
    printf("\nScore- Player: %d, Computer: %d, Draw: %d", score.player, score.computer, score.draw);
    printf("\n\nTic Tac Toe\n");
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if(j < BOARD_SIZE-1) {
                printf("|");
            }
        }
        if(i < BOARD_SIZE-1) {
            printf("\n---+---+---\n");
        }
    }
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for(int i = 0; i < BOARD_SIZE; i++) {
        if(board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return 1;
        }
        if(board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return 1;
        }
    }
    if((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board [1][1] == player && board[2][0] == player)) {
        return 1;
    }
    return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
    for(int i = 0; i< BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void play_game() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    char current_player = rand() % 2 == 0 ? X : O; //generates a random 1/0 

    print_board(board);
    while(1) {
        if(current_player == X) {
            player_move(board);
            print_board(board);
            if(check_win(board, X)) {
                score.player++;
                print_board(board);
                printf("\n\nCongratulations You Have Won !!!");
                break;
            }
            current_player = O;
        } else {
            computer_move(board);
            print_board(board);
            if(check_win(board, O)) {
                score.computer++;
                print_board(board);
                printf("\n\nI Won !!! But You Played Well ...");
                break;
            }
            current_player = X;
        }
        if(check_draw(board)) {
            score.draw++;
            print_board(board);
            printf("\n\nIts A Draw !! Lets Play Again"); 
            break;
        }
    }
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int column) {
    return !(row < 0 || column < 0 || 
            row > 2 || column > 2 || 
            board[row][column] != ' ');
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE]) {
    int count = 0, x, y;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j] == ' ') {
                count++;
                x = i;
                y = j;
            }
        }
    }

    if(count == 1) {
        board[x][y] = X;
        return;
    }

    int row, column;
    do {
        printf("\n\nPlayer X's Move");
        printf("\nEnter Row And Column (1-3) for X: ");
        scanf("%d %d", &row, &column);
        row--; column--;  //Converting to zero based
    } while(!is_valid_move(board, row, column));

    board[row][column] = X;

}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {
    //Play for immediate win
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j] == ' ') {
                board[i][j] = O;
                if(check_win(board, O)) {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    //Play for immediate block
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j] == ' ') {
                board[i][j] = X;
                if(check_win(board, X)) {
                    board[i][j] = O;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    //GOD mode
    if(difficulty == 2) {
        //Play centre if available
        if(board[1][1] == ' ') {
            board[1][1] = O;
            return;
        }

        //Play corner if available
        int corner[4][2] = {
            {0, 0},
            {0, 2},
            {2, 0},
            {2, 2}
        };
        for(int i = 0; i < 4; i++) {
            if(board[corner[i][0]][corner[i][1]] == ' '){
                board[corner[i][0]][corner[i][1]] = O;
                return;
            }
        }
    }

    //Play first available move
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j] == ' ') {
                board[i][j] = O;
                return;
            }
        }
    }

}

int main() {
    srand(time(NULL));
    int choice;
    printf("\n*** Welcome To Tic Tac Toe Game ***");
    while(1) {
        printf("\n\nSelect Difficulty Level:");
        printf("\n1. Human Mode (Standard)");
        printf("\n2. God Mode (Impossible to Win)");
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &difficulty);
        
        if(difficulty != 1 && difficulty != 2) {
            printf("Incorrect Choice Please Enter (1/2)");
        } else {
            break;
        }
    }
    do {
        play_game();
        printf("\nDo You Want To Play Again? (1 for Yes/ 0 for No): ");
        scanf("%d", &choice);
    } while(choice == 1);
    printf("\nThanks For Playing, Hope You Enjoyed");
}