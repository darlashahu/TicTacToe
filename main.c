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
  printf("-------------\n");
  for (int i = 0; i < 3; i++) {
    printf("|");
    for (int j = 0; j < 3; j++) {
      printf(" %c |", board[i][j]);
    }
    printf("\n-------------\n");
  }
}

char win() {
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
      return board[i][0];
    if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
      return board[0][i];
  }
  if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    return board[0][0];
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    return board[1][1];
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
  printf("Invalid move! Try again!\n");
  return 0;
}

void getHumanMove(char playerSymbol) {
  printf("%c's turn!\n", playerSymbol);
  int row;
  int col;
  do {
    printf("Enter row (1-3): ");
    scanf("%d", &row);
    printf("Enter column (1-3): ");
    scanf("%d", &col);
  } while (!tryMove(row - 1, col - 1, playerSymbol));
  printBoard();
}

void getComputerMove(char playerSymbol) {
  printf("%c's turn!\n", playerSymbol);
  int row, col;

  for (row = 0; row < 3; row++) {
    for (col = 0; col < 3; col++) {
      if (board[row][col] == ' ') {
        board[row][col] = playerSymbol;
        if (win() == playerSymbol) {
          printf("Computer chose (%d, %d)\n", row + 1, col + 1);
          printBoard();
          return;
        }
        board[row][col] = ' ';
      }
    }
  }

  char opponentSymbol = (playerSymbol == 'X') ? 'O' : 'X';
  for (row = 0; row < 3; row++) {
    for (col = 0; col < 3; col++) {
      if (board[row][col] == ' ') {
        board[row][col] = opponentSymbol;
        if (win() == opponentSymbol) {
          board[row][col] = playerSymbol;
          printf("Computer chose (%d, %d)\n", row + 1, col + 1);
          printBoard();
          return;
        }
        board[row][col] = ' ';
      }
    }
  }

  if (board[1][1] == ' ') {
    board[1][1] = playerSymbol;
    printf("Computer chose (2, 2)\n");
    printBoard();
    return;
  }

  int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
  for (int i = 0; i < 4; i++) {
    row = corners[i][0];
    col = corners[i][1];
    if (board[row][col] == ' ') {
      board[row][col] = playerSymbol;
      printf("Computer chose (%d, %d)\n", row + 1, col + 1);
      printBoard();
      return;
    }
  }

  int edges[4][2] = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};
  for (int i = 0; i < 4; i++) {
    row = edges[i][0];
    col = edges[i][1];
    if (board[row][col] == ' ') {
      board[row][col] = playerSymbol;
      printf("Computer chose (%d, %d)\n", row + 1, col + 1);
      printBoard();
      return;
    }
  }
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
