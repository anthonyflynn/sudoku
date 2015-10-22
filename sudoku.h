struct Node;
typedef Node *Node_ptr;

struct Node
{
  char value;
  Node_ptr ptr_to_next_node;
};


void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(char board[9][9]);
bool make_move(const char *position, char digit, char board[9][9]);
bool save_board(const char *filename, char board[9][9]);
bool solve_board(char board[9][9]);

bool out_of_range(int row, int column);
bool duplicate_digit_in_row(int row, char digit, char board[9][9]);
bool duplicate_digit_in_column(int column, char digit, char board[9][9]);
bool duplicate_digit_in_box(int row, int column, char digit, char board[9][9]);
bool check_valid(int row, int column, char digit, char board[9][9]);
Node_ptr assign_new_node(const char digit);
void add_to_rear(Node_ptr &front, const char digit);
void find_and_delete_node(Node_ptr &front, char digit);
void print_linked_list(const Node_ptr front);
void print_possible_values(Node_ptr possible_values[9][9]);
void make_null(Node_ptr array[9][9]);
void calculate_possible_values(Node_ptr possible_values[9][9], char board[9][9]);
