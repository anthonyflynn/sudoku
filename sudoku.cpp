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


bool make_move(const char *position, char digit, char board[9][9]) // SHOULD POSITION BE 2 OR 3?  3 GIVEN '\0' AT END?
{
  int row = position[0] - 'A'; // Converts the first char in position to row array index
  int column = position[1] - '1'; // Converts the second char in position to column array index

  if (static_cast<int>(digit) > 57 || static_cast<int>(digit) < 49) // 49 is the ASCII value for character 1, 57 is the ASCII character for 9 
    return false; // tests that digit is an appropriate value (i.e. between 1 and 9)

  if ((row > 8 || row < 0) || (column > 8 || column < 0)) // tests coordinates not out of range
    return false;

  for (int c = 0; c < 9; c++) // tests digit does not appear in the same column
    {
      if (board[row][c] == digit)
	return false;
    }

  for (int r = 0; r < 9; r++) // tests digit does not appear in the same row
    {
      if (board[r][column] == digit)
	return false;
    }

  int box_row = (row / 3) * 3; // converts row to a value or either 0, 3 or 6 to test box
  int box_column = (column / 3) * 3; // converts column to a value or either 0, 3 or 6 to test box

  for(int r = box_row; r < (box_row + 3); r++)
    {
      for(int c = box_column; c < (box_column + 3); c++)
	{
	  if(board[r][c] == digit)
	    return false;
	}
    }

  board[row][column] = digit;
  return true;

}


