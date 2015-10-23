#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
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



bool solve_board(char board[9][9])
{
  //Node_ptr possible_values[9][9];
  int row(0), column(0);
  //make_null(possible_values);  // sets all pointers to an initial value of NULL:

  //calculate_possible_values(possible_values, board); // calculates all possible values for each square based on numbers currently placed on board

  //print_possible_values(possible_values); // consider changing the names here and in fuction declarations / definitions

  //find_and_delete_node(possible_values[0][0],'1');

  //remove_values_from_peers - this is supposed to remove a value from squares peers if that square has only one possible value 

  
  if(is_complete(board))
    {
      save_board("easy-solution-AF.dat", board);
      return true;
    }

  get_next_empty_square(row, column, board);
  
  //if(row < 0 || column < 0 || row > 8 || column > 8)
  //exit(1);
  
  char position[] = {row + 'A', column + '1'};
  
  //cout << possible_values[row][column] -> value;
  //char attempt = possible_values[row][column] -> value;
  char attempt = '1';
  while(attempt <= '9')
    {
      if(make_move(position, attempt, board))
	{
	  if(solve_board(board))
	     return true;
	}
      attempt++;
    }

  if(attempt > '9')
    {
      board[row][column] = '.';
      return false;
    }




  //REMEMBER TO DELETE ELEMENTS IN LINKED LIST WHEN FINISHED USING


  return true;
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

Node_ptr assign_new_node(const char digit)
{
  Node_ptr new_node = new (nothrow) Node;
  if(new_node == NULL)
    {
      cout << "Error - no more memory left to assign Nodes";
      exit(1);
    }
  new_node -> value = digit;
  new_node -> ptr_to_next_node = NULL;
}

void add_to_rear(Node_ptr &front, const char digit)
{
  Node_ptr new_last_node = assign_new_node(digit);
  Node_ptr previous_last_node = front;
  
  if (!front) // i.e. if there are no Nodes currently in the list
    {
      front = new_last_node;
      return;
    }

  // default case for existing list:
  while((previous_last_node -> ptr_to_next_node) != NULL)
    previous_last_node = previous_last_node -> ptr_to_next_node;

  previous_last_node -> ptr_to_next_node = new_last_node;
}

void find_and_delete_node(Node_ptr &front, char digit) // finds a Node with a particular value and deletes it from that linked list (if it exists)
{
  Node_ptr node_before = front, node_to_delete = front;
  
  while(node_to_delete != NULL)
    {
      if(digit == (node_to_delete -> value))
	{
	  if(node_to_delete == front)
	    front = node_to_delete -> ptr_to_next_node;
	  else
	    node_before -> ptr_to_next_node = node_to_delete -> ptr_to_next_node;
	  delete node_to_delete;
	  return;
	}
      node_before = node_to_delete;
      node_to_delete = node_to_delete -> ptr_to_next_node;
    }
}


void print_linked_list(const Node_ptr front)
{
  for (Node_ptr current = front; current; current = current -> ptr_to_next_node)
    {
      cout << current -> value;
    }
}

void print_possible_values(Node_ptr possible_values[9][9])
{
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	{
	  print_linked_list(possible_values[r][c]);
	  cout << " ";
	}
      cout << endl;
    }  
}

void make_null(Node_ptr array[9][9])
{
  for(int r=0; r<9; r++)
    for(int c=0; c<9; c++)
      array[r][c] = NULL;
}

void calculate_possible_values(Node_ptr possible_values[9][9], char board[9][9])
{
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	{
	  if(isdigit(board[r][c]))
	    add_to_rear(possible_values[r][c], board[r][c]);
	  else
	    {
	      char test_value = '1';
	      while(test_value <= '9')
		{
		  if(check_valid(r, c, test_value, board))
		    {
		      add_to_rear(possible_values[r][c], test_value);
		    }
		  test_value++;
		}
	    }
	}
    }
}

void get_next_empty_square(int &row, int &column, char board[9][9])
{
  while(isdigit(board[row][column]) && row < 9)
    {
      row++;
      if(row == 9 && column < 9)
	{
	  row = 0;
	  column++;
	}
      //cout << row <<  column << " "; // for testing
    }
}


/*
void remove_values_from_peers(Node_ptr possible_values[9][9])
{
  char test;
  int row(0), column(0);

  while(possible_values[r][c] != NULL)
    {
      test = possible_values -> value;

}
*/




//FOR ALL FUNCTION DECLARATIONS, NEED TO CHANGE 2D ARRAYS WITH [9][9] to [9][] AND INCLUDE THE OTHER DIMENSION AS A SEPARATE VARIABLE


//DO UNIT TESTS FOR ALL OF THE INDIVIDUAL FUNCTIONS
