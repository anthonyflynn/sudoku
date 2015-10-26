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
  if (!out)
    return false;  // No assert as no need to exit the program if the file save not successful

  int row = 0;
  while (out && row < 9) {
    for (int n=0; n<9; n++)
      out.put(board[row][n]); // No assert as no need to exit the program if the file save not successful
    out.put('\n');
    row++;
  }
  return ((row == 9) ? true : false);
}



bool solve_board(char board[9][9])
{
  Node_ptr possible_values[9][9];
  make_null(possible_values);  // sets all pointers to an initial value of NULL:
  calculate_possible_values(possible_values, board); // calculates all possible values for each square based on numbers currently placed on board

  //print_possible_values(possible_values); // consider changing the names here and in fuction declarations / definitions

  //find_and_delete_node(possible_values[0][0],'1');

  //remove_values_from_peers - this is supposed to remove a value from squares peers if that square has only one possible value 
  
  helper_function(board, possible_values, NULL);

}


bool helper_function(char board[9][9], Node_ptr possible_values[9][9], Node_ptr last_node_tested) // RENAME THIS FUNCTION - NOT REPRESENTATIVE
{
  int row(0), column(0);
  //print_possible_values(possible_values);
  //display_board(board);
  if(is_complete(board))
    {
      save_board("easy-solution-AF.dat", board);
      return true;
    }

  get_next_empty_square(row, column, board);
  //if(row < 0 || column < 0 || row > 8 || column > 8)
  //exit(1);
  
  char position[] = {row + 'A', column + '1'};
  Node_ptr current_ptr;

  if(last_node_tested == NULL)
    current_ptr = possible_values[row][column];
  else
    current_ptr = last_node_tested -> ptr_to_next_node; // Declare current_ptr above
  //char attempt = '1';

  while(current_ptr != NULL)
    {
      char attempt = current_ptr -> value;
      if(make_move(position, attempt, board))
	{
	  if(helper_function(board, possible_values, NULL)) // RENAME
	     return true;
	}
      current_ptr = current_ptr -> ptr_to_next_node;
    }

  if(current_ptr == NULL)
    {
      board[row][column] = '.';
      return false;
    }
  //REMEMBER TO DELETE ELEMENTS IN LINKED LIST WHEN FINISHED USING

}





bool invalid_digit(const char digit) // returns true if the digit is invalid (i.e. not a char between 1 and 9)
{
  if (static_cast<int>(digit) > 57 || static_cast<int>(digit) < 49) // '1' = 49 (ASCII), '9' = 57 (ASCII)
    return true;
  else
    return false;
}

bool out_of_range(const int row, const int column) // returns true if test coordinate is out of range
{
  if ((row > 8 || row < 0) || (column > 8 || column < 0))
    return true;
  else
    return false;
}

bool duplicate_digit_in_row(const int row, const char digit, char board[9][9]) // returns true if digit already appears in the same row
{
  for (int c = 0; c < 9; c++)
    {
      if (board[row][c] == digit)
	return true;
    }
  return false;
}

bool duplicate_digit_in_column(const int column, const char digit, char board[9][9]) // returns true if digit already appears in the same column
{
  for (int r = 0; r < 9; r++)
    {
      if (board[r][column] == digit)
	return true;
    }
  return false;
}

bool duplicate_digit_in_box(const int row, const int column, const char digit, char board[9][9]) // returns true if digit already appears in the same 3x3 box
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

bool check_valid(const int row, const int column, const char digit, char board[9][9])// returns true if digit can be validly placed in the square indicated by row and column in board.  Otherwise returns false.
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

/* function which returns the row and column coordinates of the next square of board which does not contain a digit */
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

void print_linked_list(const Node_ptr front)
{
  for (Node_ptr current = front; current; current = current -> ptr_to_next_node)
    {
      cout << current -> value;
    }
}

void print_possible_values(Node_ptr possible_values[9][9]) // CAN DELETE WHEN FINISHED TESTING
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

Node_ptr find_node(const Node_ptr front, const char digit) // finds a Node with a particular value...think about what to do if the searched value is not found.
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

  //THIS IS NOT VERY GOOD - IMPROVE:
  cout << "Error - value not found";
  exit(1);
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



//UNIT TEST FUNCTIONS:
void unit_test_is_complete()
{
  char test_board[9][9];
  
  //BOARD EMPTY:
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	test_board[r][c] = ' ';
    }
  
  assert(!is_complete(test_board));
  
  //BOARD FULL OF DIGITS
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	test_board[r][c] = '1';
    }
  assert(is_complete(test_board));
  
  test_board[0][0] = '0'; //BOARD CONTAINS A ZERO CHARACTER - NOT ALLOWED
  assert(!is_complete(test_board));
  
  test_board[0][0] = 'A'; //BOARD CONTAINS A NON-DIGIT - NOT ALLOWED
  assert(!is_complete(test_board));
  
  int test_number = 1;
  test_board[0][0] = test_number; // BOARD CONTAINS AN INTEGER - NOT ALLOWED
  assert(!is_complete(test_board));
  
  test_board[0][0] = '1';
  test_board[0][8] = 'A'; // TESTING EXTREME OF COLUMNS
  assert(!is_complete(test_board));
  
  test_board[0][8] = '1';
  test_board[8][8] = 'A'; // TESTING EXTREME OF COLUMNS AND ROWS
  assert(!is_complete(test_board));
  
  test_board[8][8] = '1';
  test_board[8][0] = 'A'; // TESTING EXTREME OF ROWS
  assert(!is_complete(test_board));
  
  cout << "Unit test completed successfully - is_complete(...)" << endl;
}

void unit_test_invalid_digit() // should return true if the digit is invalid (i.e. not a char between 1 and 9)
{
  int test_int = 1;

  //tests invalid digits return true:
  assert(invalid_digit(test_int));
  assert(invalid_digit('0'));
  assert(invalid_digit('a'));
  assert(invalid_digit('A'));
  assert(invalid_digit('z'));
  assert(invalid_digit('.'));

  // tests all valid digit return false:
  char test = '1';
  while (test <= '9')
    {
      assert(!invalid_digit(test));
      test++;
    }

  cout << "Unit test completed successfully - invalid_digit(...)" << endl;
}

void unit_test_out_of_range() // should return true if test coordinate is out of range
{
  for (int row = 0; row < 9; row++)
    {
      for (int column = 0; column < 9; column++)
	assert(!out_of_range(row,column));
    }

  assert(!out_of_range(0,0));
  assert(!out_of_range(8,0));
  assert(!out_of_range(0,8));
  assert(!out_of_range(8,8));
  assert(out_of_range(9,0));
  assert(out_of_range(0,9));
  assert(out_of_range(9,9));

  cout << "Unit test completed successfully - out_of_range(...)" << endl;
}

void unit_test_duplicate_digit_in_row() // should return true if digit already appears in the same row
{
  char test_board[9][9];

  for(int r=0; r<9; r++)
    {
	test_board[r][0] = '1';
	test_board[r][8] = '1';
    }
  
  assert(duplicate_digit_in_row(0,'1',test_board));
  assert(!duplicate_digit_in_row(0,'2',test_board));

  test_board[0][0] = '2';
  assert(duplicate_digit_in_row(0,'1',test_board));
  assert(duplicate_digit_in_row(0,'2',test_board));

  test_board[0][0] = 2;
  assert(!duplicate_digit_in_row(0,'2',test_board));

  assert(!duplicate_digit_in_row(8,'2',test_board));
  test_board[8][8] = '2';
  assert(duplicate_digit_in_row(8,'2',test_board));

  cout << "Unit test completed successfully - duplicate_digit_in_row(...)" << endl;
}


void unit_test_duplicate_digit_in_column()
{
  char test_board[9][9];

  for(int c=0; c<9; c++)
    {
	test_board[0][c] = '1';
	test_board[8][c] = '1';
    }
  
  assert(duplicate_digit_in_column(0,'1',test_board));
  assert(!duplicate_digit_in_column(0,'2',test_board));

  test_board[0][0] = '2';
  assert(duplicate_digit_in_column(0,'1',test_board));
  assert(duplicate_digit_in_column(0,'2',test_board));

  test_board[0][0] = 2;
  assert(!duplicate_digit_in_column(0,'2',test_board));

  assert(!duplicate_digit_in_column(8,'2',test_board));
  test_board[8][8] = '2';
  assert(duplicate_digit_in_column(8,'2',test_board));

  cout << "Unit test completed successfully - duplicate_digit_in_column(...)" << endl;
}


void unit_test_duplicate_digit_in_box()
{
  char test_board[9][9];

  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	test_board[r][c] = '1';
    }

  test_board[0][0] = '2'; //Test top left box
  assert(duplicate_digit_in_box(0,0,'2',test_board));
  assert(duplicate_digit_in_box(0,2,'2',test_board));
  assert(duplicate_digit_in_box(2,0,'2',test_board));
  assert(duplicate_digit_in_box(2,2,'2',test_board));

  assert(!duplicate_digit_in_box(0,3,'2',test_board));
  assert(!duplicate_digit_in_box(0,5,'2',test_board));
  assert(!duplicate_digit_in_box(0,6,'2',test_board));
  assert(!duplicate_digit_in_box(0,8,'2',test_board));

  assert(!duplicate_digit_in_box(3,0,'2',test_board));
  assert(!duplicate_digit_in_box(3,2,'2',test_board));
  assert(!duplicate_digit_in_box(3,3,'2',test_board));
  assert(!duplicate_digit_in_box(3,5,'2',test_board));
  assert(!duplicate_digit_in_box(3,6,'2',test_board));
  assert(!duplicate_digit_in_box(3,8,'2',test_board));

  assert(!duplicate_digit_in_box(5,0,'2',test_board));
  assert(!duplicate_digit_in_box(5,2,'2',test_board));
  assert(!duplicate_digit_in_box(5,3,'2',test_board));
  assert(!duplicate_digit_in_box(5,5,'2',test_board));
  assert(!duplicate_digit_in_box(5,6,'2',test_board));
  assert(!duplicate_digit_in_box(5,8,'2',test_board));

  assert(!duplicate_digit_in_box(6,0,'2',test_board));
  assert(!duplicate_digit_in_box(6,2,'2',test_board));
  assert(!duplicate_digit_in_box(6,3,'2',test_board));
  assert(!duplicate_digit_in_box(6,5,'2',test_board));
  assert(!duplicate_digit_in_box(6,6,'2',test_board));
  assert(!duplicate_digit_in_box(6,8,'2',test_board));

  assert(!duplicate_digit_in_box(8,0,'2',test_board));
  assert(!duplicate_digit_in_box(8,2,'2',test_board));
  assert(!duplicate_digit_in_box(8,3,'2',test_board));
  assert(!duplicate_digit_in_box(8,5,'2',test_board));
  assert(!duplicate_digit_in_box(8,6,'2',test_board));
  assert(!duplicate_digit_in_box(8,8,'2',test_board));

  test_board[3][3] = '3'; //Test middle box
  assert(!duplicate_digit_in_box(0,0,'3',test_board));
  assert(!duplicate_digit_in_box(0,2,'3',test_board));
  assert(!duplicate_digit_in_box(2,0,'3',test_board));
  assert(!duplicate_digit_in_box(2,2,'3',test_board));

  assert(!duplicate_digit_in_box(0,3,'3',test_board));
  assert(!duplicate_digit_in_box(0,5,'3',test_board));
  assert(!duplicate_digit_in_box(0,6,'3',test_board));
  assert(!duplicate_digit_in_box(0,8,'3',test_board));

  assert(!duplicate_digit_in_box(3,0,'3',test_board));
  assert(!duplicate_digit_in_box(3,2,'3',test_board));
  assert(duplicate_digit_in_box(3,3,'3',test_board));
  assert(duplicate_digit_in_box(3,5,'3',test_board));
  assert(!duplicate_digit_in_box(3,6,'3',test_board));
  assert(!duplicate_digit_in_box(3,8,'3',test_board));

  assert(!duplicate_digit_in_box(5,0,'3',test_board));
  assert(!duplicate_digit_in_box(5,2,'3',test_board));
  assert(duplicate_digit_in_box(5,3,'3',test_board));
  assert(duplicate_digit_in_box(5,5,'3',test_board));
  assert(!duplicate_digit_in_box(5,6,'3',test_board));
  assert(!duplicate_digit_in_box(5,8,'3',test_board));

  assert(!duplicate_digit_in_box(6,0,'3',test_board));
  assert(!duplicate_digit_in_box(6,2,'3',test_board));
  assert(!duplicate_digit_in_box(6,3,'3',test_board));
  assert(!duplicate_digit_in_box(6,5,'3',test_board));
  assert(!duplicate_digit_in_box(6,6,'3',test_board));
  assert(!duplicate_digit_in_box(6,8,'3',test_board));

  assert(!duplicate_digit_in_box(8,0,'3',test_board));
  assert(!duplicate_digit_in_box(8,2,'3',test_board));
  assert(!duplicate_digit_in_box(8,3,'3',test_board));
  assert(!duplicate_digit_in_box(8,5,'3',test_board));
  assert(!duplicate_digit_in_box(8,6,'3',test_board));
  assert(!duplicate_digit_in_box(8,8,'3',test_board));

  test_board[6][6] = '4'; //Test bottom right box
  assert(!duplicate_digit_in_box(0,0,'4',test_board));
  assert(!duplicate_digit_in_box(0,2,'4',test_board));
  assert(!duplicate_digit_in_box(2,0,'4',test_board));
  assert(!duplicate_digit_in_box(2,2,'4',test_board));

  assert(!duplicate_digit_in_box(0,3,'4',test_board));
  assert(!duplicate_digit_in_box(0,5,'4',test_board));
  assert(!duplicate_digit_in_box(0,6,'4',test_board));
  assert(!duplicate_digit_in_box(0,8,'4',test_board));

  assert(!duplicate_digit_in_box(3,0,'4',test_board));
  assert(!duplicate_digit_in_box(3,2,'4',test_board));
  assert(!duplicate_digit_in_box(3,3,'4',test_board));
  assert(!duplicate_digit_in_box(3,5,'4',test_board));
  assert(!duplicate_digit_in_box(3,6,'4',test_board));
  assert(!duplicate_digit_in_box(3,8,'4',test_board));

  assert(!duplicate_digit_in_box(5,0,'4',test_board));
  assert(!duplicate_digit_in_box(5,2,'4',test_board));
  assert(!duplicate_digit_in_box(5,3,'4',test_board));
  assert(!duplicate_digit_in_box(5,5,'4',test_board));
  assert(!duplicate_digit_in_box(5,6,'4',test_board));
  assert(!duplicate_digit_in_box(5,8,'4',test_board));

  assert(!duplicate_digit_in_box(6,0,'4',test_board));
  assert(!duplicate_digit_in_box(6,2,'4',test_board));
  assert(!duplicate_digit_in_box(6,3,'4',test_board));
  assert(!duplicate_digit_in_box(6,5,'4',test_board));
  assert(duplicate_digit_in_box(6,6,'4',test_board));
  assert(duplicate_digit_in_box(6,8,'4',test_board));

  assert(!duplicate_digit_in_box(8,0,'4',test_board));
  assert(!duplicate_digit_in_box(8,2,'4',test_board));
  assert(!duplicate_digit_in_box(8,3,'4',test_board));
  assert(!duplicate_digit_in_box(8,5,'4',test_board));
  assert(duplicate_digit_in_box(8,6,'4',test_board));
  assert(duplicate_digit_in_box(8,8,'4',test_board));

  cout << "Unit test completed successfully - duplicate_digit_in_box(...)" << endl;
}

void unit_test_make_move()
{
  char test_board[9][9];

  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	test_board[r][c] = '.';
    }

  test_board[0][0] = '1';

  assert(!make_move("A3", '1', test_board)); // invalid move
  assert(test_board[0][2] == '.'); // should be no change to board
  assert(make_move("A3", '2', test_board)); // valid move
  assert(test_board[0][2] == '2'); // board should be updated

  cout << "Unit test completed successfully - make_move(...)" << endl;
}


void unit_test_save_board()
{
  char original_board[9][9], saved_board[9][9];
  load_board("easy-solution.dat", original_board);
  save_board("saved-board.dat", original_board);
  load_board("saved-board.dat", saved_board);
  
  for(int r=0; r<9; r++)
    {
      for(int c=0; c<9; c++)
	assert(original_board[r][c] == saved_board[r][c]);
    }

  cout << "Unit test completed successfully - save_board(...)" << endl;
}

void unit_test_get_next_empty_square()
{
  char test_board[9][9];
  int row(1), column(1);

  for(int r=0; r<9; r++) // fills test_board with '.' characters
    {
      for(int c=0; c<9; c++)
	test_board[r][c] = '.';
    }
  
  get_next_empty_square(row, column, test_board);
  assert((row == 0) && (column == 0)); // should start with top left

  test_board[0][0] = '1'; // fills top left square with a digit

  get_next_empty_square(row, column, test_board);
  assert((row == 1) && (column == 0)); // should return coordinates of second row in first column

  for(int r=1; r<8; r++) // fills the first column with digits except for the last row
    test_board[r][0] = '1';

  get_next_empty_square(row, column, test_board);
  assert((row == 8) && (column == 0)); // should return bottom left square

  test_board[8][0] = '1'; // fills bottom left square with a digit

  get_next_empty_square(row, column, test_board);
  assert((row == 0) && (column == 1)); // should return coordinates of first row in second column

  for(int r=0; r<9; r++) // fills test_board with digits until the bottom right square
    {
      for(int c=0; c<9; c++)
	test_board[r][c] = '1';
    }
  test_board[8][8] = '.';

  get_next_empty_square(row, column, test_board);
  assert((row == 8) && (column == 8)); // should return coordinates of the bottom right square

  cout << "Unit test completed successfully - get_next_empty_square(...)" << endl;
}




/*
void unit_test_()
{
  cout << "Unit test completed successfully - (...)" << endl;
}

*/



/*
GENERAL QUESTIONS:
1) Unit tests - should I include this in my interface file?
2) For main file, do we just want a file which has an interface and which allows you to input a file name and get a solution out?  Or should we demonstrate how it looks when things (i) do work and (ii) don't work?
3) Inputting 2D arrays of characters as function parameters - why are we not just including the first of the two array sizes?  Why not [9][] and include the other dimension as a separate variable?
4) Not using the function to save file - I have still written it, but this seems surprising?
5)_ Why am I getting different times for each execution fo the program?
*/

