#include <iostream>
#include <time.h>
 
using namespace std;
 
#define BOARD_SIZE 10
#define BOMBS 10
 
char player_board[BOARD_SIZE][BOARD_SIZE];
char game_board[BOARD_SIZE][BOARD_SIZE];
int seen[BOARD_SIZE][BOARD_SIZE];
 
//0-8 means the amount of bombs around the spot
//b means the spot has a bomb
 
int flags = BOMBS;
int bombs_flagged = 0;
 
char symbol;
bool board_generated = false;
 
void input_symbol();
void check_cell();
void generate_board();
int neighbors(int, int);
void setup_player_board();
void reveal(int, int);

time_t time_at_start = time(0);
time_t elapsed;
 
//flag functions
void place_flags();
void flags_left();
 
void print_board();
void print_player_board();
 
int main()
{
    srand(time(NULL));
    elapsed = time(0);
 
    setup_player_board();
 
    while(true) input_symbol();
}
 
void flags_left()
{
    cout << "You have " << flags << " flags left to place\n" << endl;
}
 
void place_flags()
{
    int i = -1, j = -1;
    while(i < 0 || i > BOARD_SIZE - 1 || j < 0 || j > BOARD_SIZE - 1)
    {
        cin >> i >> j;
    }
 
    if(seen[i][j] == 0)
    {
        if(player_board[i][j] == '*') {
            if(flags > 0) {
                player_board[i][j] = 'F';
                flags--;
 
                if(game_board[i][j] == 'B') {
                    bombs_flagged++;
                }
            }
            else {
                cout << "You have no flags left to place! Try removing some first." << endl;
            }
        }
        else if(player_board[i][j] == 'F') {
            player_board[i][j] = '*';
            flags++;
 
            if(game_board[i][j] == 'B') {
                bombs_flagged--;
            }
        }
    }
 
    print_player_board();
}
 
void setup_player_board()
{
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            seen[i][j] = 0;
            player_board[i][j] = '*';
        }
}
 
void print_board()
{
    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << game_board[i][j] << " ";
        }
        cout << endl;
    }
}
 
 
void print_player_board()
{
    cout << "∆  ";
    for(int i = 0; i < BOARD_SIZE; i++)
        cout << i << " ";
 
    cout << " " << endl;
    for(int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
        if(i < 10)
            cout << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            if(j > 9)
                cout << " ";
            if(player_board[i][j] == '0')
                cout << "  ";
            else
                cout << player_board[i][j] << " ";
        }
        cout << endl;
    }
}
 
void check_cell()
{
    int i = -1, j = -1;
    while(i < 0 || i > BOARD_SIZE - 1 || j < 0 || j > BOARD_SIZE - 1)
    {
        cin >> i >> j;
    }
 
    if(!board_generated)
    {
        if(i + 1 <= BOARD_SIZE - 1 && j + 1 <= BOARD_SIZE - 1)
            game_board[i + 1][j + 1] = 'x';
        if(i + 1 <= BOARD_SIZE - 1)
            game_board[i + 1][j] = 'x';
        if(i + 1 <= BOARD_SIZE - 1 && j - 1 >= 0)
            game_board[i + 1][j - 1] = 'x';
        if(i - 1 >= 0 && j + 1 <= BOARD_SIZE - 1)
            game_board[i - 1][j + 1] = 'x';
        if(i - 1 >= 0)
            game_board[i - 1][j] = 'x';
        if(i - 1 >= 0 && j - 1 >= 0)
            game_board[i - 1][j - 1] = 'x';
        if(j + 1 <= BOARD_SIZE - 1)
            game_board[i][j + 1] = 'x';
        if(j - 1 >= 0)
            game_board[i][j - 1] = 'x';
 
        game_board[i][j] = 'x';
 
        generate_board();
        board_generated = true;
    }
 
    reveal(i, j);
    print_player_board();
}
 
void reveal(int i, int j)
{
    if(game_board[i][j] == 'B') {
        print_board();
        cout << "\n\nYou lose! Better luck next time." << endl;
        exit(0);
    }
    else {
        player_board[i][j] = game_board[i][j];    
 
        if(game_board[i][j] == '0' && seen[i][j] == 0) {
            seen[i][j] = 1;
 
            if(i + 1 <= BOARD_SIZE - 1 && j + 1 <= BOARD_SIZE - 1)
                reveal(i + 1, j + 1);
            if(i + 1 <= BOARD_SIZE - 1)
                reveal(i + 1, j);
            if(i + 1 <= BOARD_SIZE - 1 && j - 1 >= 0)
                reveal(i + 1, j - 1);
            if(i - 1 >= 0 && j + 1 <= BOARD_SIZE - 1)
                reveal(i - 1, j + 1);
            if(i - 1 >= 0)
                reveal(i - 1, j);
            if(i - 1 >= 0 && j - 1 >= 0)  
                reveal(i - 1, j - 1);    
            if(j + 1 <= BOARD_SIZE - 1)  
                reveal(i, j + 1);
            if(j - 1 >= 0)
                reveal(i, j - 1);
        }
        else seen[i][j] = 1;
    }
}
 
void generate_board()
{
    int counter = BOMBS;
 
    while(counter > 0)
    {
        int xc = rand() % BOARD_SIZE;
        int yc = rand() % BOARD_SIZE;
 
        if(game_board[xc][yc] != 'B' && game_board[xc][yc] != 'x')
        {
            game_board[xc][yc] = 'B';
            counter--;
        }
    }
 
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(game_board[i][j] != 'B')
                game_board[i][j] = '0' + neighbors(i, j);
        }
    }
}  
 
//function that will return how many bombs are around a given coordinate
int neighbors(int i, int j)
{
    int bombs_around_spot = 0;
 
    if(i + 1 <= BOARD_SIZE - 1 && j + 1 <= BOARD_SIZE - 1)
        if(game_board[i + 1][j + 1] == 'B')
            bombs_around_spot++;
 
    if(i + 1 <= BOARD_SIZE - 1)
        if(game_board[i + 1][j] == 'B')
            bombs_around_spot++;
 
    if(i + 1 <= BOARD_SIZE - 1 && j - 1 >= 0)
        if(game_board[i + 1][j - 1] == 'B')
            bombs_around_spot++;
 
    if(i - 1 >= 0 && j + 1 <= BOARD_SIZE - 1)
        if(game_board[i - 1][j + 1] == 'B')
            bombs_around_spot++;
 
    if(i - 1 >= 0)
        if(game_board[i - 1][j] == 'B')
            bombs_around_spot++;
 
    if(i - 1 >= 0 && j - 1 >= 0)
        if(game_board[i - 1][j - 1] == 'B')
            bombs_around_spot++;
 
    if(j + 1 <= BOARD_SIZE - 1)
        if(game_board[i][j + 1] == 'B')
            bombs_around_spot++;
 
    if(j - 1 >= 0)
        if(game_board[i][j - 1] == 'B')
            bombs_around_spot++;
 
    return bombs_around_spot;
}
 
void input_symbol()
{
    if(bombs_flagged == BOMBS)
    {
        elapsed = time(0);
        elapsed = elapsed - time_at_start;
        cout << "\n\nYou won in " << elapsed << " seconds. Thanks for playing!" << endl;
        exit(0);
    }
 
 
    cout << "Press c to check a cell, f to place a flag," << endl;
    cout << "n to see how many flags you have left, or q to quit.\n" << endl;
 
    cin >> symbol;
    switch(symbol) {
        case 'c': check_cell(); break;
        case 'f': place_flags(); break;
        case 'n': flags_left(); break;
        case 'q': cout << "Thanks for playing!" << endl; exit(0);
        default: {
            cout << "Please provide valid input." << endl;
            input_symbol();
        }
    }
}
