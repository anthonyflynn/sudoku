#include <iostream>
#include <cstdio>
#include <ctime> // for calculating calculation speed
#include <cassert> // for testing
#include "sudoku.h"

using namespace std;

int main() {

  // FILE FOR DEMONSTRATING PROGRAM: 
  /*
  char board[9][9];
  char file[80]; // max filename of 79 charaters
  
  cout << "This is a program which finds the solution to Sudoku puzzles." << endl;
  cout << "Please enter the filename of the Sudoku which you'd like to solve: ";
  cin >> file;
  
  load_board(file, board);
  cout << "\nThe original unsolved puzzle is: " << endl;
  display_board(board);

  if (solve_board(board)) {
    cout << "\nThe board '" << file << "' has a solution:" << endl;
    display_board(board);
  } else 
    cout << "\nA solution cannot be found." << endl;

  cout << "Please enter a filename where you would like to save the solution: ";
  cin >> file;
  if (save_board(file, board))
    cout << "Save board to '" << file << "' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;
  */
  

  /*
  cout << "====================== Question 1 ======================" << endl << endl;

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  cout << "====================== Question 2 ======================" << endl << endl;

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

	// write more tests
  cout << "====================== Question 3 ======================" << endl << endl;

  load_board("easy.dat", board);
  display_board(board);
  
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  cout << "====================== Question 4 ======================" << endl << endl;

  load_board("easy.dat", board);
  int start_easy = clock(); // for calculating speed of execution
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  int stop_easy = clock(); // for calculating speed of execution
  
  */
  int start, stop;
  char board[9][9];

  load_board("easy.dat", board);
  start = clock(); // for calculating speed of execution
  if (solve_board(board)) {
    stop = clock(); // for calculating speed of execution
    cout << "Execution time (Easy): " << (stop - start) / double(CLOCKS_PER_SEC)*1000 << endl;
    display_board(board);
  } else 
    cout << "Easy: A solution cannot be found." << endl;


  load_board("medium.dat", board);
  start = clock(); // for calculating speed of execution
  if (solve_board(board)) {
    stop = clock(); // for calculating speed of execution
    cout << "Execution time (Medium): " << (stop - start) / double(CLOCKS_PER_SEC)*1000 << endl;
    display_board(board);
  } else 
    cout << "Medium: A solution cannot be found." << endl;

  load_board("mystery1.dat", board);
  start = clock(); // for calculating speed of execution
  if (solve_board(board)) {
    stop = clock(); // for calculating speed of execution
    cout << "Execution time (Mystery1): " << (stop - start) / double(CLOCKS_PER_SEC)*1000 << endl;
    display_board(board);
  } else 
    cout << "Mystery1: A solution cannot be found." << endl;

  load_board("mystery2.dat", board);
  start = clock(); // for calculating speed of execution
  if (solve_board(board)) {
    stop = clock(); // for calculating speed of execution
    cout << "Execution time (Mystery2): " << (stop - start) / double(CLOCKS_PER_SEC)*1000 << endl;
    display_board(board);
  } else 
    cout << "Mystery2: A solution cannot be found." << endl;

  load_board("mystery3.dat", board);
  start = clock(); // for calculating speed of execution
  if (solve_board(board)) {
    stop = clock(); // for calculating speed of execution
    cout << "Execution time (Mystery3): " << (stop - start) / double(CLOCKS_PER_SEC)*1000 << endl;
    display_board(board);
  } else 
    cout << "Mystery3: A solution cannot be found." << endl;




  /*
  unit_test_is_complete();
  unit_test_invalid_digit();
  unit_test_out_of_range();
  unit_test_duplicate_digit_in_row();
  unit_test_duplicate_digit_in_column();
  unit_test_duplicate_digit_in_box();
  unit_test_make_move();
  unit_test_save_board();
  unit_test_get_next_empty_square();
  */

  return 0;
}


