// This program is a sudoku solver.

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <assert.h>


const int BOARD_LEN = 9;
const int SUB_BOARD_LEN = 3;
const int EMPTY = 0;


// structure to house the 2D array of the sudoku board
struct sudoku {
  int board[9][9];
};


struct sudoku sb = {
  {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9},
  }
};


// valid_row_col(board, row, col) checks if the board is valid at row and col.
bool valid_row_col(struct sudoku *sb, int row, int col) {
  assert(sb);
  int num = sb->board[row][col];
  for (int i = 0; i < BOARD_LEN; ++i) {

    if (col != i && num == sb->board[row][i]) {
      return false;
    }
    if (row != i && num == sb->board[i][col]) {
      // int val = sb->board[i][col];
      return false;
    }
  }
  return true;
}


// valid_sub(board, row, col) checks if the board is valid at row and col, 
//   in regards to the sub cell.
bool valid_sub(struct sudoku *sb, int row, int col) {
  assert(sb);
  int num = sb->board[row][col];
  // determines which sub cell we are in
  int sub_row = (row / SUB_BOARD_LEN) * SUB_BOARD_LEN;
  int sub_col = (col / SUB_BOARD_LEN) * SUB_BOARD_LEN;

  for (int i = sub_row; i < sub_row + SUB_BOARD_LEN; ++i) {
    for (int j = sub_col; j < sub_col + SUB_BOARD_LEN; ++j) {
      if (!(i == row && j == col) && sb->board[i][j] == num) {
        return false;
      }
    }
  }
  return true;
}


// valid_board(board) determines if the board at (row, col) is valid within 
//   the board.
bool valid_board(struct sudoku *sb, int row, int col) {
  assert(sb);
  return (valid_row_col(sb, row, col)) && (valid_sub(sb, row, col));
}


// initial_valid_board(board) determines if the initial setup of the board 
//   is valid to begin with.
bool initial_valid_board(struct sudoku *sb) {
  assert(sb);
  for (int i = 0; i < BOARD_LEN; ++i) {
    for (int j = 0; j < BOARD_LEN; ++j) {
      if ((sb->board[i][j] != 0) && (!(valid_board(sb, i, j)))) {
        return false;
      }
    }
  }
  return true;
}


// solve_cells(board, row, col) solves each individual cell
bool solve_cells(struct sudoku *sb) {
  assert(sb);
  /*
  // base cases: when we reach the end of the row
  if (col >= BOARD_LEN) {
    // when we have reached the end of the board
    if (row + 1 == BOARD_LEN) {
      return true;
    } else {
      solve_cells(sb, row + 1, 0);
      return false;
    }
  }

  if (sb->board[row][col] == EMPTY) {
    // brute forcing the potential solutions be adding nums
    for (int num = 1; num <= BOARD_LEN; ++num) {
      sb->board[row][col] = num; // inserting a potential num to a blank spot
      if (valid_board(sb, row, col)) {
        if (solve_cells(sb, row, col + 1)) {
          return true;
        }
        sb->board[row][col] = EMPTY; // when none of the numbers work
      }
    }
    return false;
  }
  solve_cells(sb, row, col + 1);
  return true;
  */
  for (int row = 0; row < BOARD_LEN; ++row) {
    for (int col = 0; col < BOARD_LEN; ++col) {
      if (sb->board[row][col] == EMPTY) {
        for (int num = 1; num <= 9; ++num) {
          sb->board[row][col] = num; // inserting a potential num
          if (valid_board(sb, row, col)) {
            if (solve_cells(sb)) {
              return true;
            } else {
              sb->board[row][col] = EMPTY; 
            }
          } else {
            sb->board[row][col] = EMPTY; 
          }
        }
        return false;
      }
    }
  }
  return true;
}


// solve(board) solves the 9x9 sudoku board. Returns the solved board in a 
//   2-D array. Returns NULL if no solution
struct sudoku *solve_sudoku(struct sudoku *sb) {
  assert(sb);
  if (initial_valid_board(sb)) {
    if (solve_cells(sb)) {
      return sb;
    }
  }
  return NULL;
}


void print_board(struct sudoku *sb) {
  assert(sb);
  for (int i = 0; i < BOARD_LEN; ++i) {
    if (i % 3 == 0) {
      printf("\n");
    }
    for (int j = 0; j < BOARD_LEN; ++j) {
      if (j % 3 == 0) {
        printf("   ");
      }
      printf("%d|", sb->board[i][j]);
    }
    printf("\n");
  }
}


int main(void) {
  // print_board(&sb);
  struct sudoku *solved_board = solve_sudoku(&sb);
  print_board(solved_board);
  return 0;
}