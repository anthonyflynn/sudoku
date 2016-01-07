# sudoku
Sudoku solver in C++

The program solves a Sudoku in two distinct sequential phases: (1)
deduction and (2) recursion.  

During the deduction phase, The board is modelled as a 3D array of
booleans representing row, column and possible digits (in that order).
The function calculate_valid_digits(..) assigns a value of true to
digits that can be validly placed in each square, with invalid digits
marked false. For each row, column, box and square in turn, the board
is updated to reflect digits which can only validly be placed in one
square.  This process is repeated until no more deductions are
possible, at which point the board is passed into the recursive
function fill_next_square(..) to test if it is complete or requires
guessing.

During the recursive phase, the program attempts to fill all remaining
empty squares with a valid digit.  The function get_next_square(..) is
used to find the next empty square, which is then assigned the value
of the lowest digit that can be validly placed in it.  The function
fill_next_square(..) is then called again.  This is repeated until
either (i) the board is complete (function returns true) or (ii) there
are no digits which can be validly placed in a particular square,
indicating a mistake in an earlier digit assignemnt.  In the case of
the latter, the program moves back to the most recently assigned
square and attempts to places the next highest valid digit in that
square (if there is one). If there is no valid solution, the function
returns false (when there are no more valid digits that can be place
in square [0][0]).
