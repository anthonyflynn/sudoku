struct Node;
typedef Node *Node_ptr;

struct Node
{
  char value;
  Node_ptr ptr_to_next_node;
};

void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]);
bool make_move(const char *position, const char digit, char board[9][9]);
bool save_board(const char *filename, const char board[9][9]);
bool solve_board(char board[9][9]);
bool fill_next_square(char board[9][9], Node_ptr possible_values[9][9], Node_ptr last_node_tested);

// Helper functions:
bool invalid_digit(const char digit);
bool out_of_range(const int row, const int column);
bool duplicate_digit_in_row(const int row, const char digit, char board[9][9]);
bool duplicate_digit_in_column(const int column, const char digit, char board[9][9]);
bool duplicate_digit_in_box(const int row, const int column, const char digit, char board[9][9]);
bool check_valid(const int row, const int column, const char digit, char board[9][9]);
void get_next_empty_square(int &row, int &column, char board[9][9]);
int get_global_count();

// Functions related to linked list:
Node_ptr assign_new_node(const char digit);
void add_to_rear(Node_ptr &front, const char digit);
void make_null(Node_ptr array[9][9]);
void calculate_valid_digits(Node_ptr valid_digits[9][9], char board[9][9]);
Node_ptr find_node(const Node_ptr front, const char digit);
void delete_linked_list_array(Node_ptr valid_digits[9][9]);
void print_linked_list(const Node_ptr front);
void print_valid_digits(Node_ptr valid_digits[9][9]);
