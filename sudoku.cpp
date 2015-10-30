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
  Node_ptr valid_digits[9][9]; // will contain potential values for each square (based on start board)
  bool solution_found(false); // returns true if there is a potential solution, otherwise false
  make_null(valid_digits);  // sets all pointers to an initial value of NULL:
  calculate_valid_digits(valid_digits, board); // calculates all possible values for each square based on numbers placed on board at the start
  solution_found = fill_next_square(board, valid_digits, NULL);
  delete_linked_list_array(valid_digits); // delete linked list to free up memory
  return solution_found;
}


/* function which tests if board is complete (returns true), and if not finds the next empty square */
bool fill_next_square(char board[9][9], Node_ptr valid_digits[9][9], Node_ptr last_node_tested)
{
  global_count++;
  int row(0), column(0);
  char position[2];
  Node_ptr current_ptr;

  if(is_complete(board)) // tests if the board is complete - if so, solution found, return true
    {
      return true;
    }

  get_next_empty_square(row, column, board); // finds the row and column of the next empty square

  position[0] = row + 'A';
  position[1] = column + '1';

  if(last_node_tested == NULL) // true if is the first value digit being tested in square
    current_ptr = valid_digits[row][column]; // sets pointer to the node containing the first valid digit for the square
  else
    current_ptr = last_node_tested -> ptr_to_next_node; // moves the pointer onto the next valid digit

  while(current_ptr != NULL)
    {
      char attempt = current_ptr -> value;
      if(make_move(position, attempt, board)) //tests if the digit can be validly placed in the square
	{
	  if(fill_next_square(board, valid_digits, NULL)) // if valid, move onto the next square
	     return true;
	}
      current_ptr = current_ptr -> ptr_to_next_node;
    }

  if(current_ptr == NULL) // if no valid digits can be placed in the board, square set to blank
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

/* function to return the total number of recursive calls to reach a solution */
int get_global_count()
{
  return global_count;
}

/* function creates a new node and assigns its value as input parameter digit and the pointer to next node as NULL */
Node_ptr assign_new_node(const char digit)
{
  Node_ptr new_node = new (nothrow) Node;

  if(new_node == NULL) // checks if there is enough memory to generate a new node
    {
      cout << "Error - no more memory left to assign Nodes";
      exit(1);
    }

  new_node -> value = digit;
  new_node -> ptr_to_next_node = NULL;
}

/* function attaches a new node to the rear of a linked list with its value set as input parameter digit. */
void add_to_rear(Node_ptr &front, const char digit)
{
  Node_ptr new_last_node = assign_new_node(digit); // generates new node and assigns its value as digit
  Node_ptr previous_last_node = front;
  
  if (!front) // i.e. if there are no nodes currently in the list
    {
      front = new_last_node;
      return;
    }

  // default case for existing list:
  while((previous_last_node -> ptr_to_next_node) != NULL)
    previous_last_node = previous_last_node -> ptr_to_next_node;

  previous_last_node -> ptr_to_next_node = new_last_node; // adds the new node to the rear of the list
}

/* function sets the array of node pointers to null*/
void make_null(Node_ptr array[9][9])
{
  for(int r=0; r<9; r++)
    for(int c=0; c<9; c++)
      array[r][c] = NULL;
}

/* for each square, create a linked list of valid digits based on start board */
void calculate_valid_digits(Node_ptr valid_digits[9][9], char board[9][9])
{
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	{
	  if(isdigit(board[r][c])) // if board already contains a value at start
	    add_to_rear(valid_digits[r][c], board[r][c]);
	  else
	    {
	      char test_value = '1';
	      while(test_value <= '9') // iterate through possible digits and add valid ones to the array of valid digits
		{
		  if(check_valid(r, c, test_value, board))
		    {
		      add_to_rear(valid_digits[r][c], test_value);
		    }
		  test_value++;
		}
	    }
	}
    }
}

/* function finds a node with a particular value. */
Node_ptr find_node(const Node_ptr front, const char digit) 
{
  Node_ptr node_being_sought = front;
  
  while(node_being_sought != NULL)
    {
      if(digit == (node_being_sought -> value))
	{
	  return node_being_sought;
	}
      node_being_sought = node_being_sought -> ptr_to_next_node;
    }
}

/* function to delete a linked list */
void delete_linked_list_array(Node_ptr valid_digits[9][9])
{
  Node_ptr next_node;
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	{
	  while(valid_digits[r][c] != NULL)
	    {
	      next_node = valid_digits[r][c] -> ptr_to_next_node;
	      delete valid_digits[r][c];
	      valid_digits[r][c] = next_node;
	    }
	}
    }
}

/* function to print a linked list */
void print_linked_list(const Node_ptr front)
{
  for (Node_ptr current = front; current; current = current -> ptr_to_next_node)
    {
      cout << current -> value;
    }
}

/* function to print the list of valid digits */
void print_valid_digits(Node_ptr valid_digits[9][9])
{
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	{
	  print_linked_list(valid_digits[r][c]);
	  cout << " ";
	}
      cout << endl;
    }  
}

