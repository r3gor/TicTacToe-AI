#include<bits/stdc++.h>

using namespace std;

#define AI_CH  'x'
#define OP_CH  'o'
#define EMPTY  '-'

const char get_winner(const array<array<char, 3>, 3> board) {

    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2]; 

    for (size_t i=0; i<3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }

    return EMPTY; // no winner
}

const bool is_full(const array<array<char, 3>, 3> board) {
    for(array<char, 3> row : board) {
        for (char c : row)
            if (c == EMPTY) return false;
    }
    return true;
}

const int minimax(array<array<char, 3>, 3> board, const int depth, const bool is_max) {
    char winner = get_winner(board);
    
    if (winner == AI_CH) return +10 - depth;
    if (winner == OP_CH) return -10 + depth;
    if (is_full(board)) return 0;

    if (is_max) {
        int best_val = -1000;  
        for (size_t i = 0; i < 3; i++){
            for (size_t j = 0; j<3; j++) {
                if (board[i][j] != EMPTY) continue;
                board[i][j] = AI_CH;
                best_val = max(best_val, minimax(board, depth+1, !is_max));
                board[i][j] = EMPTY;
            }
        }
        return best_val;
    }

    else {
        int best_val = +1000;  
        for (size_t i = 0; i < 3; i++){
            for (size_t j = 0; j<3; j++) {
                if (board[i][j] != EMPTY) continue;
                board[i][j] = OP_CH;
                best_val = min(best_val, minimax(board, depth+1, !is_max));
                board[i][j] = EMPTY;
            }
        }
        return best_val;
    }
}
    
const pair<int, int> get_best_move(array<array<char, 3>, 3> board) {
    int val_max = -1000, temp;
    pair<int, int> move {-1, -1};
    for (size_t i=0; i<3; i++) {
        for (size_t j=0; j<3; j++) {
            if (board[i][j] != EMPTY) continue;
            board[i][j] = AI_CH;
            temp = minimax(board, 0, false);
            board[i][j] = EMPTY;
            if (temp > val_max){
                move = make_pair(i, j);
                val_max = temp;
                }
       }
    }
    return move;
}

inline const void print(array<array<char, 3>, 3> board) {
    cout<<"\n ___________\n";
    for (size_t i = 0; i<3; i++) {
        cout<<"| ";
        for (size_t j = 0; j<3; j++) {
            cout<<board[i][j]<<" | ";
        }
        cout<<"\n|___|___|___|\n";
    }
}

const void new_game() {
    array<array<char, 3>, 3> board {{
        {EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY}
    }};
    
    int turn;
    
    cout<<"\t- choose first player -\n"
    <<"1. AI\n"
    <<"2. You\n";
    cin>>turn;
    
    int r = -1, c = -1;
    pair<int, int> ai_move {-1, -1};

    while(1) {

        if (turn % 2 == 0) {
            while(1){
                cout<<"- your move -\n";
                cout<<"row: "; cin>>r;
                cout<<"column: "; cin>>c;
                if (board[r][c] != EMPTY) {
                    cout<<"\t-invalid move!-\n";
                    continue;
                }
                board[r][c] = OP_CH;
                break;
            }
        }
        else if (turn % 2 == 1) {
            ai_move = get_best_move(board);
            cout<<"- AI move -\n";
            cout<<"row: "<<ai_move.first<<"\n";
            cout<<"column: "<<ai_move.second<<"\n";
            board[ai_move.first][ai_move.second] = AI_CH;
        }
        print(board);
        ++turn;

        char winner = get_winner(board);
        if (winner != EMPTY) {
            cout<<"\n\t:::: "<<(winner == AI_CH? "AI":"YOU")<<" win! ::::\n"
            <<"\t- in "<<turn/2<< " turns -\n";
            return;
        }
        else if (is_full(board)){
            cout<<"\n\t:::: T I E ::::\n";
            return;
        }
    }
}

int main() {

    char op = 'y';
    while(op == 'y') {
        cout<<"\n\n\t:: TicTacToe | YOU-vs-AI ::\n";
        new_game();
        cout<<"play again? (y/n)\n";
        cin>>op;
    }
    
    return 0;
}