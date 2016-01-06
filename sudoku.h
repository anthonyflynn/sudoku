/* function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9]);

/* function to display a Sudoku board */
void display_board(const char board[9][9]);

/* function which returns true if all Sudoku board positions are occupied by 
digits, and false otherwise.  No check for logical validity of digits. */
bool is_complete(const char board[9][9]);

/* function which attempts to place a digit onto the board at a given position 
(consisting of a 2 character string denoting row & column coordinates, e.g.I8).
Returns true if the placing of the digit at position is valid (and updates 
board), otherwise returns false (and board is unchanged). */
bool make_move(const char *position, const char digit, char board[9][9]);

/* function which outputs the 2D character array board to a file with name 
'filename'.  Returns true if file written successfully, otherwise false. */
bool save_board(const char *filename, const char board[9][9]);

/* function which attempts to solve the Sudoku puzzle board.  Return value is 
true if a solution exists (and board contains final solution) or false if no 
solution exists (board unchanged).  */
bool solve_board(char board[9][9]);

/* function which tests if board is complete (returns true), and if not, 
attempts to fill the next empty square */
bool fill_next_square(char board[9][9]);

/* function returns true if digit invalid (i.e. not a char between 1 and 9) */
bool invalid_digit(const char digit);

/* function returns true if test coordinate is out of range */
bool out_of_range(const int row, const int column);

/* function returns true if digit already appears in the same row */
bool duplicate_digit_in_row(const int row, const char digit, char board[9][9]);

/* function returns true if digit already appears in the same column */
bool duplicate_digit_in_column(const int column, const char digit, char board[9][9]);

/* function returns true if digit already appears in the same 3x3 box */
bool duplicate_digit_in_box(const int row, const int column, const char digit, char board[9][9]);

/* function returns true if digit can be validly placed in the square 
indicated by row and column in board.  Otherwise returns false. */
bool check_valid(const int row, const int column, const char digit, char board[9][9]);

/* function returns the row and column coordinates of the next square of the
board which does not contain a digit */
void get_next_empty_square(int &row, int &column, char board[9][9]);

/* function initialises all position in a 3D boolean array to false */
void fill_with_false(bool valid_digits[9][9][9]);

/* function sets values in the 3D array valid_digits to true based based on 
whether the digit could be validly placed (based on existing state of board).*/
void calculate_valid_digits(bool valid_digits[9][9][9], char board[9][9]);

/* function assigns valid digits to squares by making deductions (row, column,
box and square) until either the board is complete or no further deductions 
are possible. */
void deduce_digits(char board[9][9]);

/* function updates the board for any values which can be deduced on a row 
by row basis. Each digit is considered in turn and, for each row, if there is 
only one square which can be validly hold that digit, the board is updated to 
reflect this */
void deduce_in_row(char board[9][9]);

/* function updates the board for any values which can be deduced on a column 
by column basis. Each digit is considered in turn and, for each column, if 
there is only one square which can be validly hold that digit, the board is 
updated to reflect this */
void deduce_in_column(char board[9][9]);

/* function updates the board for any values which can be deduced on a box 
by box basis. Each digit is considered in turn and, for each box, if there is 
only one square which can be validly hold that digit, the board is updated to 
reflect this */
void deduce_in_box(char board[9][9]);

/* function updates the board for any values which can be deduced on a square 
by square basis. For each square in turn, the potentially valid digits are 
calculated.  If there is only one valid digit for that square, the board is 
updated to reflect this */
void deduce_from_valid_digits(char board[9][9]);

/* function sums total value of characters in the board & returns this value */
int sum_board(const char board[9][9]);

/* function returns the total number of recursive calls to reach a solution */
int get_global_count();
