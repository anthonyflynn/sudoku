#include <iostream>
#include <cstdio>
#include <ctime> // for calculating calculation speed
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */

  /*
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  
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
  
  // write tests for this

  
  cout << "====================== Question 4 ======================" << endl << endl;

  */

  load_board("easy.dat", board);
  //display_board(board);
  int start_easy = clock(); // for calculating speed of execution
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    //display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  int stop_easy = clock(); // for calculating speed of execution

  load_board("medium.dat", board);
  //display_board(board);
  int start_med = clock(); // for calculating speed of execution
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    //display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  int stop_med = clock(); // for calculating speed of execution

  load_board("mystery1.dat", board);
  //display_board(board);
  int start_mys1 = clock(); // for calculating speed of execution
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    //display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  int stop_mys1 = clock(); // for calculating speed of execution

  load_board("mystery2.dat", board);
  //display_board(board);
  int start_mys2 = clock(); // for calculating speed of execution
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << endl;
    //display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  int stop_mys2 = clock(); // for calculating speed of execution

  load_board("mystery3.dat", board);
  //display_board(board);
  int start_mys3 = clock(); // for calculating speed of execution
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << endl;
    //display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  int stop_mys3 = clock(); // for calculating speed of execution


  cout << "Execution time (easy): " << (stop_easy - start_easy) / double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "Execution time (medium): " << (stop_med - start_med) / double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "Execution time (mystery1): " << (stop_mys1 - start_mys1) / double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "Execution time (mystery2): " << (stop_mys2 - start_mys2) / double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "Execution time (mystery3): " << (stop_mys3 - start_mys3) / double(CLOCKS_PER_SEC)*1000 << endl;


  /*

	// write more tests

  cout << "====================== Question 5 ======================" << endl << endl;

	// write more tests
  */
   
  return 0;
}
