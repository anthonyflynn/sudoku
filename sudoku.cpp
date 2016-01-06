#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include "sudoku.h"

using namespace std;

int global_count(-1); // counts number of recursive calls for solution

void load_board(const char *filename, char board[9][9]) {
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

bool is_complete(const char board[9][9]) {
  for (int r=0; r<9; r++)
    {
      for (int c=0; c<9; c++) 
	{
	  if (board[r][c] == '0' || !isdigit(board[r][c]))
	    return false;  // false if no digit in square or if digit is '0'
	}
    }
  return true; // returns true if all squares contain digits
}

bool make_move(const char *position, const char digit, char board[9][9])
{
  int row = position[0] - 'A'; //Converts 1st char in 'position' to row index
  int column = position[1] - '1';//Converts 2nd char in 'position' to col index

  if (!check_valid(row, column, digit, board)) // checks move is valid
    return false;

  board[row][column] = digit; //if move is valid, updates board with move
  return true;

}

bool save_board(const char *filename, const char board[9][9]) {
  ofstream out(filename);
  int row = 0;

  if (!out)
    return false;  //No assert as no need to exit the program if save fails

  while (out && row < 9) {
    for (int n=0; n<9; n++)
      out.put(board[row][n]);
    out.put('\n');
    row++;
  }

  out.close();
  return ((row == 9) ? true : false);
}

bool solve_board(char board[9][9])
{
  bool solution_found(false); //Value will be set to true if a solution exists

  save_board("temp.dat", board); //Original board saved in case no solution
  
  deduce_digits(board); //Make any deductions possible
  
  solution_found = fill_next_square(board); 
  // returns true (if board is complete) or false (if no solution found)

  if(!solution_found) // Return board to initial state if no solution found
    load_board("temp.dat", board);

  return solution_found;
}

bool fill_next_square(char board[9][9])
{
  global_count++; // counter for number of times recursive function called
  int row(0), column(0);
  char position[2];
  char attempt = '1'; // start search with digit '1'

  if(is_complete(board))
    {
      return true;
    }

  get_next_empty_square(row, column, board);//sets row/col of next empty square

  //Convert next empty square row/col to string for input to make_move(..):
  position[0] = row + 'A';
  position[1] = column + '1';

  while(attempt <= '9')
    {
      if(make_move(position, attempt, board))//if digit can be validly placed
	{
	  if(fill_next_square(board)) // move onto the next square
	     return true;
	}
      attempt++;
    }

  if(attempt > '9') // no valid digits can be placed, set square set to blank
    {
      board[row][column] = '.';
      return false; // moves back to previous cell filled
    }
}

bool invalid_digit(const char digit)
{
  // '1' = 49 (ASCII), '9' = 57 (ASCII)
  if (static_cast<int>(digit) > 57 || static_cast<int>(digit) < 49)
    return true;
  else
    return false;
}

bool out_of_range(const int row, const int column)
{
  if ((row > 8 || row < 0) || (column > 8 || column < 0))
    return true;
  else
    return false;
}

bool duplicate_digit_in_row(const int row, const char digit, char board[9][9])
{
  for (int c = 0; c < 9; c++)
    {
      if (board[row][c] == digit)
	return true;
    }
  return false;
}

bool duplicate_digit_in_column(const int column, const char digit, char board[9][9])
{
  for (int r = 0; r < 9; r++)
    {
      if (board[r][column] == digit)
	return true;
    }
  return false;
}

bool duplicate_digit_in_box(const int row, const int column, const char digit, char board[9][9])
{
  int test_row = (row / 3) * 3; // converts row to 0, 3 or 6
  int test_column = (column / 3) * 3; // converts column to 0, 3 or 6

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
	  row = 0; // when no more rows, increment column and reset row
	  column++;
	}
    }
}

void fill_with_false(bool valid_digits[9][9][9])
{
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	{
	  for(int d=0; d<9; d++) // d represent digits '1' to '9'
	    valid_digits[r][c][d] = false;
	}
    }
}

void calculate_valid_digits(bool valid_digits[9][9][9], char board[9][9])
{
  int digit_position;
  // Represents array position of digit (in 3rd dimension).
  // e.g digit '1' occupies space 0, up to digit '9' in space 8

  char test_value;
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	{
	  if(isdigit(board[r][c]))//if square in board already contains a digit
	    {
	      digit_position = board[r][c] - '1';
	      valid_digits[r][c][digit_position] = true; 
	      //set corresponding boolean in valid_digits to true
	    }
	  else
	    {
	      test_value = '1';
	      while(test_value <= '9')
		{
		  if(check_valid(r, c, test_value, board))
		    {
		      digit_position = test_value - '1';
		      valid_digits[r][c][digit_position] = true; 
		      // set all valid digits to true
		    }
		  test_value++; 
		}
	    }
	}
    }
}

void deduce_digits(char board[9][9])
{
  int board_sum_before = sum_board(board);
  int board_sum_after(0), difference(0);

  do
    {
      deduce_in_row(board);
      deduce_in_column(board);
      deduce_in_box(board);
      deduce_from_valid_digits(board);

      board_sum_after = sum_board(board);
      difference = board_sum_after - board_sum_before; //check if any changes
      board_sum_before = board_sum_after;
    } while(!is_complete(board) && difference != 0); 
}

void deduce_in_row(char board[9][9])
{
  char digit;
  int position(0), count(0);
  bool valid_digits[9][9][9]; 
  // 1st 2 dimensions represent row and column (of the Sudoku board).  
  // 3rd dimension represents the digits '1' to '9'

  fill_with_false(valid_digits);
  calculate_valid_digits(valid_digits, board);

  for(int d=0; d<9; d++)
    {
      for(int r=0; r<9; r++)
	{
	  digit = d + '1'; // convert d to equivalent char (e.g d = 0 -> '1')
	  if(!duplicate_digit_in_row(r, digit, board)) //test if row contains
	    {
	      for(int c=0; c<9; c++)
		{
		  count += valid_digits[r][c][d];
		  if(valid_digits[r][c][d])
		    position = c;//note column of square that can hold digit
		} 
	      if(count == 1) //if only one valid position in row for the digit
		board[r][position] = digit; // assign square the digit
	      position = 0;
	      count = 0;	      
	    }
	}
    }
}

void deduce_in_column(char board[9][9])
{
  char digit;
  int position(0), count(0);
  bool valid_digits[9][9][9];

  fill_with_false(valid_digits);
  calculate_valid_digits(valid_digits, board);

  for(int d=0; d<9; d++)
    {
      for(int c=0; c<9; c++)
	{
	  digit = d + '1'; // convert d to equivalent char (e.g d = 0 -> '1')
	  if(!duplicate_digit_in_column(c, digit, board))//test if column has
	    {
	      for(int r=0; r<9; r++)
		{
		  count += valid_digits[r][c][d];
		  if(valid_digits[r][c][d])
		    position = r; //note row of square that can hold digit
		} 
	      if(count == 1) //if only one valid position in col for the digit
		board[position][c] = digit; // assign square the digit
	      position = 0;
	      count = 0;	      
	    }
	}
    }
}

void deduce_in_box(char board[9][9])
{
  char digit;
  int row_position(0), column_position(0), count(0);
  int test_row(0), test_column(0);
  bool valid_digits[9][9][9];

  fill_with_false(valid_digits); 
  calculate_valid_digits(valid_digits, board);

  //starting at top left square of each box
  for(int test_row = 0; test_row < 9; test_row = test_row + 3)
    {
      for(int test_column = 0; test_column < 9; test_column = test_column + 3)
	{
	  for(int d=0; d<9; d++)
	    {
	      digit = d + '1';
	      if(!duplicate_digit_in_box(test_row, test_column, digit, board))
		{
		  for(int r = test_row; r < test_row + 3; r++)
		    {
		      for(int c = test_column; c < (test_column + 3); c++)
			{
			  count += valid_digits[r][c][d];
			  if(valid_digits[r][c][d])
			    {
			      row_position = r;
			      column_position = c;//note square which can hold
			    }
			}
		    }
		  if(count == 1)//if only one valid position in box for digit
		    board[row_position][column_position] = digit;
		  row_position = column_position = 0;
		  count = 0;	      
		}
	    }
	}
    }
}		

void deduce_from_valid_digits(char board[9][9])
{
  char digit;
  int position(0), count(0);
  bool valid_digits[9][9][9];

  fill_with_false(valid_digits); 
  calculate_valid_digits(valid_digits, board); 

  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	{
	  if(!isdigit(board[r][c])) //tests if square already contains a digit
	    {
	      for(int d=0; d<9; d++)
		{
		  count += valid_digits[r][c][d];
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

int get_global_count()
{
  return global_count;
}


