#include <iostream>
#include <cstdio>
#include <ctime> // for calculating calculation speed
#include <cassert> // for testing
#include "sudoku.h"

using namespace std;

int main() {
  /*
  // PROGRAM FOR DEMONSTRATING FUNCTION:
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

  cout << "Total number of recursive calls to solve puzzle: " << get_global_count();
  cout << endl;

  cout << "Please enter a filename where you would like to save the solution: ";
  cin >> file;
  if (save_board(file, board))
    cout << "Save board to '" << file << "' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;
  */
  
  // PROGRAM FOR TESTING:
  int start, stop, count(1), recursive_calls(0);
  double total_time(0);
  char board[9][9];

  while(count <= 1)
    {
      load_board("easy.dat", board);
      display_board(board);
      start = clock(); // for calculating speed of execution
      solve_board(board);
      stop = clock(); // for calculating speed of execution
      total_time += ((stop - start) / double(CLOCKS_PER_SEC)*1000);
      count++;
    }
  cout << "Average number of recursive calls: " << (get_global_count() - 1) / (count - 1) << endl;
  cout << "Average execution time: " << total_time / (count - 1) << endl;
  display_board(board);


  return 0;
}


