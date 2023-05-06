#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];

void initBoard() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[i][j] = ' ';
    }
  }
}

void printBoard() {
  printf("-------\n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("|%c", board[i][j]);
    }
    printf("|\n");
    printf("-------\n");
  }
}

char win() {
  if (board[0][0] == board[0][1] && board[0][0] == board[0][2])
    return board[0][0];
  if (board[1][0] == board[1][1] && board[1][0] == board[1][2])
    return board[1][0];
  if (board[2][0] == board[2][1] && board[2][0] == board[2][2])
    return board[2][0];
  if (board[0][0] == board[1][0] && board[0][0] == board[2][0])
    return board[0][0];
  if (board[0][1] == board[1][1] && board[0][1] == board[2][1])
    return board[0][1];
  if (board[0][2] == board[1][2] && board[0][2] == board[2][2])
    return board[0][2];
  if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    return board[0][0];
  if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    return board[0][2];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == ' ')
        return ' ';
    }
  }
  return 'T';
}

int tryMove(int row, int col, char playerSymbol) {
  if (row >= 0 && row <= 2 && col >= 0 && col <= 2) {
    if (board[row][col] == ' ') {
      board[row][col] = playerSymbol;
      return 1;
    }
  }
  return 0;
}

void getHumanMove(char playerSymbol) {
  printf("%c's turn!\n", playerSymbol);
  int row;
  int col;
  do {
    printf("Enter row (0-2): ");
    scanf("%d", &row);
    printf("Enter column (0-2): ");
    scanf("%d", &col);
  } while (!tryMove(row, col, playerSymbol));
  printBoard();
}

void getComputerMove(char playerSymbol) {
  printf("%c's turn!\n", playerSymbol);
  srand(time(NULL));
  printf("Computer's move!\n");
  int row;
  int col;
  do {
    row = rand() % 3;
    col = rand() % 3;
  } while (!tryMove(row, col, playerSymbol));
  printf("Computer chose (%d, %d)\n", row, col);
  printBoard();
}

int main(void) {
  printf("Welcome to TicTacToe!\n");
  printf("Choose game mode (1 for human vs human, 2 for human vs computer): ");
  char currentPlayer = 'X';
  int gameMode;
  scanf("%d", &gameMode);
  char humanSymbol = 'X';
  char computerSymbol;
  int isHumanVsHuman = 1;
  if (gameMode == 2) {
    printf("Do you want to play as X or O? ");
    scanf(" %c", &humanSymbol);
    humanSymbol = toupper(humanSymbol);
    computerSymbol = (humanSymbol == 'X') ? 'O' : 'X';
    isHumanVsHuman = 0;
  }
  initBoard();
  printBoard();
  do {
    if (isHumanVsHuman || currentPlayer == humanSymbol)
      getHumanMove(currentPlayer);
    else
      getComputerMove(currentPlayer);
    if (win() == 'T') {
      printf("It's a tie! ");
      return 0;
    }
    if (win() != ' ') {
      printf("%c won!", win());
      return 0;
    }
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
  } while (1);
  return 0;
}
