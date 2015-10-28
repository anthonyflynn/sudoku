#include <iostream>
#include <cassert> // for testing
#include "sudoku.h"

using namespace std;

void unit_test_is_complete();
void unit_test_invalid_digit();
void unit_test_out_of_range();
void unit_test_duplicate_digit_in_row();
void unit_test_duplicate_digit_in_column();
void unit_test_duplicate_digit_in_box();
void unit_test_make_move();
void unit_test_save_board();
void unit_test_get_next_empty_square();

int main()
{
  unit_test_is_complete();
  unit_test_invalid_digit();
  unit_test_out_of_range();
  unit_test_duplicate_digit_in_row();
  unit_test_duplicate_digit_in_column();
  unit_test_duplicate_digit_in_box();
  unit_test_make_move();
  unit_test_save_board();
  unit_test_get_next_empty_square();

  cout << "All unit tests completed successfully." << endl;

  return 0;
}

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
