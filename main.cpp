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
  //TESTS FROM ORIGINAL MAIN FILE:
  char board[9][9];

  load_board("easy.dat", board);
  assert(!is_complete(board));
  assert(make_move("I8", '1', board));
  assert(save_board("easy-copy.dat", board));

  load_board("easy-solution.dat", board);
  assert (is_complete(board));
  */

  int start, stop, count(1);
  double total_time(0);
  char board[9][9];

  while(count <= 100)
    {
      load_board("mystery3.dat", board);
      start = clock(); // for calculating speed of execution
      solve_board(board);
      stop = clock(); // for calculating speed of execution
      total_time += ((stop - start) / double(CLOCKS_PER_SEC)*1000);
      count++;
    }
  cout << count << endl;
  cout << "Average execution time (Easy): " << total_time / (count - 1) << endl;
  display_board(board);

  

  return 0;
}


