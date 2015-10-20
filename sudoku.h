void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(char board[9][9]);
bool make_move(const char *position, char digit, char board[9][9]);
bool save_board(const char *filename, char board[9][9]);

bool out_of_range(int row, int column);
bool duplicate_digit_in_row(int row, char digit, char board[9][9]);
bool duplicate_digit_in_column(int column, char digit, char board[9][9]);
bool duplicate_digit_in_box(int row, int column, char digit, char board[9][9]);
bool check_valid(int row, int column, char digit, char board[9][9]);
