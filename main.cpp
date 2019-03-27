#include<bits/stdc++.h>

using namespace std;

char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int game_mod, bot_mod, bot_move;

void clearScreen() {
    system("cls");
}

void colorChange(unsigned int n) {
    char color[7] = {'C', 'O', 'L', 'O', 'R', ' '};
    color[6] = n + '0'; // make color command (win edition)
    system(color);
}

void waitFor(unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop
}

void bot_rand() { // rand for harmless bot
    int tmp = rand() % 9;
    while (board[tmp] == 'O' || board[tmp] == 'X')
        tmp = rand() % 9;
    bot_move = tmp;
}


bool isFull() {
    for (int i = 0; i < 9; i++)
        if (board[i] != 'X')
            if (board[i] != 'O')
                return false;
    return true;
}

void print() { // print
    clearScreen();
    cout << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << endl;
    cout << "     |     |     " << endl << endl;
}

void setgame() { // set game mode
    char n;
    cout << "PLZ select :" <<
         endl << "	1 - P V P" <<
         endl << " 	2 - P V Bot \n";
    cin >> n;
    while (n != '1' && n != '2') {
        clearScreen();
        colorChange(4);
        cout << "Wrong selection \n";
        waitFor(2);
        clearScreen();
        colorChange(7);
        cout << "Plz select between 1 and 2 :" <<
             endl << "	1 - P V P" <<
             endl << " 	2 - P V Bot \n";
        cin >> n;
        clearScreen();
    }
    game_mod = int(n - '1');
    clearScreen();
}

void botset() { // set bot mode
    char n;
    cout << "PLZ select :" <<
         endl << "	1 - Harmless bot" <<
         endl << " 	2 - bot AI \n";
    cin >> n;
    while (n != '1' && n != '2') {
        clearScreen();
        colorChange(4);
        cout << "Wrong selection \n";
        waitFor(2);
        clearScreen();
        colorChange(7);
        cout << "Plz select between 1 and 2 :" <<
             endl << "	1 - Harmless bot" <<
             endl << " 	2 - bot AI \n";
        cin >> n;
        clearScreen();
    }
    bot_mod = int(n - '1');
    clearScreen();
}

int check() {
    for (int i = 0; i < 9; i += 3) {
        if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2]) && (board[i] == 'O'))
            return 1;
    }
    for (int i = 0; i < 3; i++) {
        if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]) && (board[i] == 'O'))
            return 1;
    }
    if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == 'O')) {
        return 1;
    }
    if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == 'O')) {
        return 1;
    }
    // P 2
    for (int i = 0; i < 9; i += 3) {
        if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2]) && (board[i] == 'X'))
            return -1;
    }
    for (int i = 0; i < 3; i++) {
        if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]) && (board[i] == 'X'))
            return -1;
    }
    if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == 'X')) {
        return -1;
    }
    if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == 'X')) {
        return -1;
    }
    return 0;
}

int minimax(bool flag) {
    int maxi = -1000, mini = 1000;
    int value = 1;
    if (check() == 1) return 10;
    else if (check() == -1) return -10;
    else if (isFull()) return 0;
    int emp[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'O' && board[i] != 'X') {
            if (mini > maxi) {
                if (flag == true) {
                    board[i] = 'O';
                    value = minimax(false);
                } else {
                    board[i] = 'X';
                    value = minimax(true);
                }
                board[i] = i + '1';
                emp[i] = value;
            }
        }
    }
    if (flag == true) {
        maxi = -1000;
        for (int i = 0; i < 9; i++) {
            if (emp[i] > maxi && emp[i] != 1) {
                maxi = emp[i];
                bot_move = i;
            }
        }
        return maxi;
    } else {
        mini = 1000;
        for (int i = 0; i < 9; i++) {
            if (emp[i] < mini && emp[i] != 1) {
                mini = emp[i];
                bot_move = i;
            }
        }
        return mini;
    }
}

int input() {
    int n;
    cin >> n;
    while ((n < 1 && n > 9) || board[n - 1] == 'O' || board[n - 1] == 'X') {
        clearScreen();
        colorChange(4);
        cout << "Wrong selection \n";
        waitFor(2);
        clearScreen();
        colorChange(7);
        print();
        cout << "plz Select your move :" << endl;
        cin >> n;
        clearScreen();
    }
    return n;
}

int main() {
    setgame();
    int turn = 1;
    char mark = 'X';
    if (game_mod) {
        botset();
        if (bot_mod) {
            while (true) {
                clearScreen();
                print();
                cout << "AI Turn : " << endl;
                minimax(true);
                board[bot_move] = 'O';
                clearScreen();
                print();
                if (check() == 1)
                    return cout << "YOU Lose - AI WINS" << endl, 0;
                if (isFull())
                    return cout << "Draw" << endl, 0;
                int tmp = 0;
                cout << "Your Turn : " << endl;
                tmp = input();
                board[--tmp] = 'X';
                clearScreen();
                print();
                if (check() == -1)
                    return cout << "YOU Win - AI Loses (impossible)" << endl, 0;
                if (isFull())
                    return cout << "Draw" << endl, 0;
            }
        } else {
            while (true) {
                clearScreen();
                print();
                cout << "HL Turn : " << endl;
                bot_rand();
                board[bot_move] = 'O';
                clearScreen();
                print();
                if (check() == 1)
                    return cout << "YOU Lose - HL WINS (RLY?)" << endl, 0;
                if (isFull())
                    return cout << "Draw" << endl, 0;
                int tmp = 0;
                cout << "Your Turn : " << endl;
                tmp = input();
                board[--tmp] = 'X';
                clearScreen();
                print();
                if (check() == -1)
                    return cout << "YOU Win - HL Loses" << endl, 0;
                if (isFull())
                    return cout << "Draw" << endl, 0;
            }
        }
    } else {
        while (true) {
            turn = 1;
            mark = 'O';
            
            clearScreen();
            print();
            
			cout << "Player " << turn << " " << mark << " Turn : " << endl;
            
            int tmp = 0;
            tmp = input();
            board[--tmp] = mark;
            
            turn = 2;
            mark = 'X';
            
            clearScreen();
			print();
			
            cout << "Player " << turn << " " << mark << " Turn : " << endl;
            
			tmp = input();
			board[--tmp] = mark;
            
			clearScreen();
            print();
            if (check() == -1)
                return cout << "player 1 Wins" << endl, 0;
            if (check() == 1)
                return cout << "player 2 wins" << endl, 0;
            if (isFull())
                return cout << "Draw" << endl, 0;
        }
    }
}
