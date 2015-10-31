#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include "sudoku.h"

using namespace std;

int global_count(0); // counts the number of times the recursive function is called to reach a solution

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
bool is_complete(const char board[9][9]) {
  for (int r=0; r<9; r++) // for each row
    {
      for (int c=0; c<9; c++) // for each column
	{
	  if (board[r][c] == '0' || !isdigit(board[r][c]))
	    return false;  // returns false if position does not hold a digit or if digit is '0' (not permitted)
	}
    }
  return true; // returns true if all of the columns and rows have been tested and all contain digits
}

/* function which attempts to place a digit onto a Sudoku board at a given position (consisting of a 2 character string denoting row and column coordinates).  Returns true if the placing of the digit at position is valid (and updates board), otherwise returns false (and board is unaltered)*/
bool make_move(const char *position, const char digit, char board[9][9])
{
  int row = position[0] - 'A'; // Converts the first char in 'position' to integer row array index
  int column = position[1] - '1'; // Converts the second char in 'position' to integer column array index

  if (!check_valid(row, column, digit, board)) // checks move is valid
    return false;

  board[row][column] = digit; //if move is valid, updates board with move
  return true;

}

/* function which outputs the 2D character array board to a file with name 'filename'.  Return true if file written successfully, otherwise false */
bool save_board(const char *filename, const char board[9][9]) {
  ofstream out(filename);
  int row = 0;

  if (!out)
    return false;  // No assert as no need to exit the program if the file save not successful

  while (out && row < 9) {
    for (int n=0; n<9; n++)
      out.put(board[row][n]); // No assert as no need to exit the program if the file save not successful
    out.put('\n');
    row++;
  }

  out.close();
  return ((row == 9) ? true : false);
}


/* function which attempts to solve the Sudoku puzzle in board.  Return value is true if a solution is found (and board contains final solution) or false if no solution exists (board unchanged)  */
bool solve_board(char board[9][9])
{
  bool solution_found(false); // returns true if there is a potential solution, otherwise false
  int board_sum_before = sum_board(board);
  int board_sum_after(0), difference(0);

  save_board("temp.dat", board); // Needed in case no solution found (so board to returned to unchanged state)
  
  do
    {
      deduce_digits(board);
      board_sum_after = sum_board(board);
      difference = board_sum_after - board_sum_before;
      board_sum_before = board_sum_after;
    } while(!is_complete(board) && difference != 0); // keep trying to make deductions until either the board is complete or there are no further deductions possible
  
  solution_found = fill_next_square(board); // call fill_next_square(..) which will either return true (if board is complete) or false (if no solution found)

  if(!solution_found) // Return board to initial state if no solution found
    load_board("temp.dat", board);

  return solution_found;
}

/* function which tests if board is complete (returns true), and if not, attempts to fill the next empty square */
bool fill_next_square(char board[9][9])
{
  global_count++; // counter for number of times recursive function called
  int row(0), column(0);
  char position[2];
  char attempt = '1'; // start search with digit '1'

  if(is_complete(board)) // tests if the board is complete - if so, solution found, return true
    {
      return true;
    }

  get_next_empty_square(row, column, board); // finds the row and column of the next empty square

  position[0] = row + 'A';
  position[1] = column + '1'; // Begin search in the top left square

  while(attempt <= '9')
    {
      if(make_move(position, attempt, board)) //tests if the digit can be validly placed in the square
	{
	  if(fill_next_square(board)) // if valid, move onto the next square
	     return true;
	}
      attempt++;
    }

  if(attempt > '9') // if no valid digits can be placed in the board, square set to blank
    {
      board[row][column] = '.';
      return false; // moves back to previous cell filled
    }
}

/* function returns true if the digit is invalid (i.e. not a char between 1 and 9) */
bool invalid_digit(const char digit)
{
  if (static_cast<int>(digit) > 57 || static_cast<int>(digit) < 49) // '1' = 49 (ASCII), '9' = 57 (ASCII)
    return true;
  else
    return false;
}

/* function returns true if test coordinate is out of range */
bool out_of_range(const int row, const int column)
{
  if ((row > 8 || row < 0) || (column > 8 || column < 0))
    return true;
  else
    return false;
}

/* function returns true if digit already appears in the same row */
bool duplicate_digit_in_row(const int row, const char digit, char board[9][9])
{
  for (int c = 0; c < 9; c++)
    {
      if (board[row][c] == digit)
	return true;
    }
  return false;
}

/* function returns true if digit already appears in the same column */
bool duplicate_digit_in_column(const int column, const char digit, char board[9][9])
{
  for (int r = 0; r < 9; r++)
    {
      if (board[r][column] == digit)
	return true;
    }
  return false;
}

/* function returns true if digit already appears in the same 3x3 box */
bool duplicate_digit_in_box(const int row, const int column, const char digit, char board[9][9])
{
  int test_row = (row / 3) * 3; // converts row to a value of either 0, 3 or 6 to test box
  int test_column = (column / 3) * 3; // converts column to a value of either 0, 3 or 6 to test box

  for (int r = test_row; r < (test_row + 3); r++)
    {
      for (int c = test_column; c < (test_column + 3); c++)
	{
	  if (board[r][c] == digit)
	    return true;
	}
    }
  return false;
}

/* function returns true if digit can be validly placed in the square indicated by row and column in board.  Otherwise returns false. */
bool check_valid(const int row, const int column, const char digit, char board[9][9])
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

/* function returns the row and column coordinates of the next square of board which does not contain a digit */
void get_next_empty_square(int &row, int &column, char board[9][9])
{
  if(!isdigit(board[0][0])) // case where top left square is empty
    {
      row = column = 0;
      return;
    }

  while(isdigit(board[row][column]) && row < 9)
    {
      row++; // if square contains a digit, and row < 9, increment row
      if(row == 9 && column < 9)
	{
	  row = 0; // one the end of the rows reaches, increment column and reset row
	  column++;
	}
    }
}

/* function initialises a 3D boolean array to false throughout */
void fill_with_false(bool valid_digits[9][9][9])
{
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	{
	  for(int d=0; d<9; d++) // for all digits
	    valid_digits[r][c][d] = false;
	}
    }
}

/* function sets values in the 3D array valid_digits to true based based on whether the digit could be validly placed (based on existing state of board). */
void calculate_valid_digits(bool valid_digits[9][9][9], char board[9][9])
{
  int digit_position; // represents the position in the array of digit (in the third dimension). E.g digit '1' occupies space 0, up to digit '9' in space 8
  char test_value;
  for(int r=0; r<9; r++) // for each row
    {
      for(int c=0; c<9; c++) // for each column
	{
	  if(isdigit(board[r][c])) // if board already contains a value
	    {
	      digit_position = board[r][c] - '1';
	      valid_digits[r][c][digit_position] = true; // set corresponding position in third dimension to true (represents that digit)
	    }
	  else
	    {
	      test_value = '1';
	      while(test_value <= '9') // otherwise, iterate through possible digits and set valid ones to true in the third dimension of the 3D array for that row & column
		{
		  if(check_valid(r, c, test_value, board))
		    {
		      digit_position = test_value - '1';
		      valid_digits[r][c][digit_position] = true; // set appropriate digit position to true
		    }
		  test_value++; // test next digit, until '9' reached
		}
	    }
	}
    }
}

/* function tests whether digits can be added to the board through deduction */
void deduce_digits(char board[9][9])
{
  deduce_in_row(board);
  deduce_in_column(board);
  deduce_in_box(board);
  deduce_from_valid_digits(board);
}

/* function updates the board for any values which can be deduced on a row by row basis. Each digit is considered in turn and, for each row, if there is only one square which can be validly hold that digit, the board is updated to reflect this */
void deduce_in_row(char board[9][9])
{
  char digit;
  int position(0), count(0);
  bool valid_digits[9][9][9]; // a 3D array: the first two dimensions represent row and column (of the Sudoku board) and the third dimension represents the digits '1' to '9'

  fill_with_false(valid_digits);
  calculate_valid_digits(valid_digits, board);

  for(int d=0; d<9; d++)
    {
      for(int r=0; r<9; r++)
	{
	  digit = d + '1'; // convert d to an equivalent char (i.e. d = 0 implies char '1')
	  if(!duplicate_digit_in_row(r, digit, board)) // tests if row already contains that digit
	    {
	      for(int c=0; c<9; c++)
		{
		  count += valid_digits[r][c][d]; // count number of squares in row which can validly hold digit
		  if(valid_digits[r][c][d])
		    position = c; // remember the column of the last square which can validly hold digit
		} 
	      if(count == 1) // if only one valid position in the row for the digit
		board[r][position] = digit;
	      position = 0;
	      count = 0;	      
	    }
	}
    }
}

/* function updates the board for any values which can be deduced on a column by column basis. Each digit is considered in turn and, for each column, if there is only one square which can be validly hold that digit, the board is updated to reflect this */
void deduce_in_column(char board[9][9])
{
  char digit;
  int position(0), count(0);
  bool valid_digits[9][9][9]; // a 3D array: the first two dimensions represent row and column (of the Sudoku board) and the third dimension represents the digits '1' to '9'

  fill_with_false(valid_digits);
  calculate_valid_digits(valid_digits, board);

  for(int d=0; d<9; d++)
    {
      for(int c=0; c<9; c++)
	{
	  digit = d + '1'; // convert d to an equivalent char (i.e. d = 0 implies char '1')
	  if(!duplicate_digit_in_column(c, digit, board)) // tests if column already contains that digit
	    {
	      for(int r=0; r<9; r++)
		{
		  count += valid_digits[r][c][d]; // count number of squares in column which can validly hold digit
		  if(valid_digits[r][c][d])
		    position = r; // remember the row of the last square which can validly hold digit
		} 
	      if(count == 1) // if only one valid position in the column for the digit
		board[position][c] = digit;
	      position = 0;
	      count = 0;	      
	    }
	}
    }

}


/* function updates the board for any values which can be deduced on a box by box basis. Each digit is considered in turn and, for each box, if there is only one square which can be validly hold that digit, the board is updated to reflect this */
void deduce_in_box(char board[9][9])
{
  char digit;
  int row_position(0), column_position(0), count(0);
  int test_row(0), test_column(0);
  bool valid_digits[9][9][9]; // a 3D array: the first two dimensions represent row and column (of the Sudoku board) and the third dimension represents the digits '1' to '9'

  fill_with_false(valid_digits); 
  calculate_valid_digits(valid_digits, board);

  for(int test_row = 0; test_row < 9; test_row = test_row + 3) // top left row of each box
    {
      for(int test_column = 0; test_column < 9; test_column = test_column + 3) // top left column of each box
	{
	  for(int d=0; d<9; d++)
	    {
	      digit = d + '1'; // convert d to an equivalent char (i.e. d = 0 implies char '1')
	      if(!duplicate_digit_in_box(test_row, test_column, digit, board)) // tests if box already contains that digit
		{
		  for(int r = test_row; r < test_row + 3; r++)
		    {
		      for(int c = test_column; c < (test_column + 3); c++)
			{
			  count += valid_digits[r][c][d]; // count number of squares in box which can validly hold digit
			  if(valid_digits[r][c][d])
			    {
			      row_position = r;
			      column_position = c; // remember row and column of last square which can validly hold digit
			    }
			}
		    }
		  if(count == 1) // if only one valid position in the box for the digit
		    board[row_position][column_position] = digit;
		  row_position = column_position = 0;
		  count = 0;	      
		}
	    }
	}
    }
}		

/* function updates the board for any values which can be deduced on a square by square basis. For each square in turn, the potentially valid digits are calculated.  If there is only one valid digit for that square, the board is updated to reflect this */
void deduce_from_valid_digits(char board[9][9])
{
  char digit;
  int position(0), count(0);
  bool valid_digits[9][9][9]; // a 3D array: the first two dimensions represent row and column (of the Sudoku board) and the third dimension represents the digits '1' to '9'

  fill_with_false(valid_digits); 
  calculate_valid_digits(valid_digits, board); 

  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	{
	  if(!isdigit(board[r][c])) // tests if square already contains a digit
	    {
	      for(int d=0; d<9; d++)
		{
		  count += valid_digits[r][c][d]; // count number of digits which can validly inserted into square
		  if(valid_digits[r][c][d])
		    position = d; // remember the last valid digit
		}
	      if(count == 1) // if only one valid digit
		board[r][c] = position + '1';
	      position = 0;
	      count = 0;
	    }
	}
    }
}

/* function sums to total value of characters in the board and returns this value */
int sum_board(const char board[9][9])
{
  int sum(0);
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	sum += board[r][c];
    }

  return sum;
}

/* function returns the total number of recursive calls to reach a solution */
int get_global_count()
{
  return global_count;
}


