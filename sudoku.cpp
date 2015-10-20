#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* function which returns true if all Sudoku board positions are occupied by digits, and false otherwise.  N.B: no check for whether digits are logically valid. */
bool is_complete(char board[9][9]) {
  for (int r=0; r<9; r++) // for each row
    {
      for (int c=0; c<9; c++) // for each column
	{
	  if (!isdigit(board[r][c]))  
	    return false;  // returns false if position does not hold a digit
	}
    }
  return true; // returns true if all of the columns and rows have been tested and all contain digits
}
//TEST FUNCTION ON BOUNDARIES - MISSING VALUES IN COLUMNS AND ROWS 0 AND 9


bool make_move(const char *position, char digit, char board[9][9])
{
  int row = position[0] - 'A'; // Converts the first char in position to row array index
  int column = position[1] - '1'; // Converts the second char in position to column array index

  if (!check_valid(row, column, digit, board))
    return false;

  board[row][column] = digit;
  return true;

}

bool save_board(const char *filename, char board[9][9]) {
  ofstream out(filename);
  if (!out)
    return false;  // No assert as no need to exit the program if the file save not successful

  int row = 0;
  while (out && row < 9) {
    for (int n=0; n<9; n++)
      out.put(board[row][n]); // No assert as no need to exit the program if the file save not successful
    out.put('\n');
    row++;
  }
  // NEED TO CHECK 9 COLUMNS?  HOW DO WE TEST THAT THIS IS A TRUE COPY WITHIN THE CODE?
  return ((row == 9) ? true : false);
}



bool solve_board(char board[9][9]) // tests coordinates not out of range
{
  char test_number = '1';
  const char *test_position = "A1";
  make_move(test_position, test_number, board);
} 



bool invalid_digit(char digit) // returns true if the digit is invalid (i.e. not between 1 and 9)
{
  if (static_cast<int>(digit) > 57 || static_cast<int>(digit) < 49) // '1' = 49 (ASCII), '9' = 57 (ASCII)
    return true;
  else
    return false;
}


bool out_of_range(int row, int column) // returns true if test coordinate is out of range
{
  if ((row > 8 || row < 0) || (column > 8 || column < 0))
    return true;
  else
    return false;
}

bool duplicate_digit_in_row(int row, char digit, char board[9][9]) // returns true if digit already appears in the same row
{
  for (int c = 0; c < 9; c++)
    {
      if (board[row][c] == digit)
	return true;
    }
  return false;
}

bool duplicate_digit_in_column(int column, char digit, char board[9][9]) // returns true if digit already appears in the same column
{
  for (int r = 0; r < 9; r++)
    {
      if (board[r][column] == digit)
	return true;
    }
  return false;
}

bool duplicate_digit_in_box(int row, int column, char digit, char board[9][9]) // returns true if digit already appears in the same 3x3 box
{
  row = (row / 3) * 3; // converts row to a value of either 0, 3 or 6 to test box
  column = (column / 3) * 3; // converts column to a value of either 0, 3 or 6 to test box

  for (int r = row; r < (row + 3); r++)
    {
      for (int c = column; c < (column + 3); c++)
	{
	  if (board[r][c] == digit)
	    return true;
	}
    }
  return false;

}

bool check_valid(int row, int column, char digit, char board[9][9])
{
  if (invalid_digit(digit))
    return false;

  if(out_of_range(row, column))
    return false;

  if(duplicate_digit_in_row(row, digit, board))
    return false;

  if(duplicate_digit_in_column(column, digit, board))
    return false;

  if(duplicate_digit_in_box(row, column, digit, board))
    return false;

  return true;

}
