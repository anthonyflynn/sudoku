void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]);
bool make_move(const char *position, const char digit, char board[9][9]);
bool save_board(const char *filename, const char board[9][9]);
bool solve_board(char board[9][9]);

// Helper functions:
bool fill_next_square(char board[9][9]);
bool invalid_digit(const char digit);
bool out_of_range(const int row, const int column);
bool duplicate_digit_in_row(const int row, const char digit, char board[9][9]);
bool duplicate_digit_in_column(const int column, const char digit, char board[9][9]);
bool duplicate_digit_in_box(const int row, const int column, const char digit, char board[9][9]);
bool check_valid(const int row, const int column, const char digit, char board[9][9]);
void get_next_empty_square(int &row, int &column, char board[9][9]);
void fill_with_false(bool valid_digits[9][9][9]);
void calculate_valid_digits(bool valid_digits[9][9][9], char board[9][9]);
void deduce_digits(char board[9][9]);
void deduce_in_row(char board[9][9]);
void deduce_in_column(char board[9][9]);
void deduce_in_box(char board[9][9]);
void deduce_from_valid_digits(char board[9][9]);
int sum_board(const char board[9][9]);
int get_global_count();
