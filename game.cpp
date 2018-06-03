#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct cell
{
	int level;
	string tbs;
	char pos;
	char val;
};

cell board[24] = { 
	{0, "T", 'L', '+'}, //0
	{0, "T", 'M', '+'}, //1
	{0, "T", 'R', '+'}, //2
	{0, "SL", 'M', '+'}, //3
	{0, "SR", 'M', '+'}, //4
	{0, "B", 'L', '+'}, //5
	{0, "B", 'M', '+'}, //6
	{0, "B", 'R', '+'}, //7
	{1, "T", 'L', '+'}, //8
	{1, "T", 'M', '+'}, //9
	{1, "T", 'R', '+'}, //10
	{1, "SL", 'M', '+'}, //11
	{1, "SR", 'M', '+'}, //12
	{1, "B", 'L', '+'}, //13
	{1, "B", 'M', '+'}, //14
	{1, "B", 'R', '+'}, //15
	{2, "T", 'L', '+'}, //16
	{2, "T", 'M', '+'}, //17
	{2, "T", 'R', '+'}, //18
	{2, "SL", 'M', '+'}, //19
	{2, "SR", 'M', '+'}, //20
	{2, "B", 'L', '+'}, //21
	{2, "B", 'M', '+'}, //22
	{2, "B", 'R', '+'} //23
};

int coinA = 9, coinB = 9, gameEnd = 0, winner = 0, colorCode;

string printPiece(int i) {
	const string cyan = "\u001b[46;1m";
	const string yellow = "\u001b[43;1m";
	const string reset = "\u001b[0m";
	if (board[i].val == 'A') {
		return cyan + board[i].val + reset;
	} else if (board[i].val == 'B') {
		return yellow + board[i].val + reset;
	}
	return reset + board[i].val + reset; // ugly hack for converting to string
}

void drawBoard()
{
	cout << endl;
	cout << printPiece(0) << "(00)----------------------" << printPiece(1) << "(01)----------------------" << printPiece(2) <<"(02)" << endl;
	cout << "|                           |                           |" << endl;
	cout << "|                           |                           |" << endl;
	cout << "|       " << printPiece(8) << "(08)--------------" << printPiece(9) << "(09)--------------" << printPiece(10) << "(10)     |" << endl;
	cout << "|       |                   |                    |      |" << endl;
	cout << "|       |                   |                    |      |" << endl;
	cout << "|       |        " << printPiece(16) << "(16)-----" << printPiece(17) << "(17)-----" << printPiece(18) << "(18)       |      |" << endl;
	cout << "|       |         |                   |          |      |" << endl;
	cout << "|       |         |                   |          |      |" << endl;
	cout << printPiece(3) << "(03)---" << printPiece(11) << "(11)----" << printPiece(19) << "(19)               " << printPiece(20) << "(20)----" << printPiece(12) << "(12)---" << printPiece(4) << "(04)" << endl;
	cout << "|       |         |                   |          |      |" << endl;
	cout << "|       |         |                   |          |      |" << endl;
	cout << "|       |        " << printPiece(21) << "(21)-----" << printPiece(22) << "(22)-----" << printPiece(23) << "(23)       |      |" << endl;
	cout << "|       |                   |                    |      |" << endl;
	cout << "|       |                   |                    |      |" << endl;
	cout << "|       " << printPiece(13) << "(13)--------------" << printPiece(14) << "(14)--------------" << printPiece(15) << "(15)     |" << endl;
	cout << "|                           |                           |" << endl;
	cout << "|                           |                           |" << endl;
	cout << printPiece(5) << "(05)----------------------" << printPiece(6) << "(06)----------------------" << printPiece(7) << "(07)" << endl;
}

bool check(int a, int b, int c)
{
	if((board[a].val == board[b].val) && (board[b].val == board[c].val))
		return 1;
	else
		return 0;
}

bool evaluate(char val, int a)
{
	if(board[a].pos == 'L')
	{
		if(check(a, a+1, a+2))
			return 1;
		if(board[a].tbs == "T" && check(a, a+3, a+5))
			return 1;
		if(board[a].tbs == "B" && check(a, a-2, a-5))
			return 1;
	}
	if(board[a].pos == 'R')
	{
		if(check(a, a-1, a-2))
			return 1;
		if(board[a].tbs == "T" && check(a, a+2, a+5))
			return 1;
		if(board[a].tbs == "B" && check(a, a-3, a-5))
			return 1;
	}	
	if(board[a].pos == 'M')
	{
		if(board[a].tbs == "T" || board[a].tbs == "B")
			if(check(a-1, a, a+1))
				return 1;
		if(board[a].tbs == "SL")
			if(check(a-3, a, a+2))
				return 1;
		if(board[a].tbs == "SR")
			if(check(a-2, a, a+3))
				return 1;
		if(board[a].level == 0 && check(a, a+8, a+16))
			return 1;
		if(board[a].level == 1 && check(a-8, a, a+8))
			return 1;
		if(board[a].level == 2 && check(a-16, a-8, a))
			return 1;
	}
	return 0;
}

void decrementCoins(int val)
{
	int a;
	if(val == 'A')
	{
		cout << "\nPlayer 1, which coin of player 2 do you wish to eliminate? :))) ";
		cin >> a;
		while(board[a].val == 'A' || board[a].val == '+' || evaluate(board[a].val, a))
		{
			cout << "\nPlease enter an index of PLAYER 2'S coin that's NOT a part of an existing triplet: ";
			cin >> a;
		}
		coinB--;
	}
	else
	{
		cout << "\nPlayer 2, which coin of player 1 do you wish to eliminate? :))) ";
		cin >> a;
		while(board[a].val == 'B' || board[a].val == '+' || evaluate(board[a].val, a))
		{
			cout << "\nPlease enter an index of PLAYER 1'S coin that's NOT a part of an existing triplet: ";
			cin >> a;
		}
		coinA--;
	}
	board[a].val = '+';
	if(coinB <=2)
	{
		gameEnd = 1;
		winner = 1;
	}
	else if(coinA <=2)
	{
		gameEnd = 1;
		winner = 2;
	}
}

void place(char val, int a)
{
	while(board[a].val != '+')
	{
		cout << "\nPlease enter an EMPTY cell index: ";
		cin >> a;
	}
	board[a].val = val;
	if(evaluate(val, a))
		decrementCoins(val);
	drawBoard();
}

void makeMove(char val, int a, int b)
{
	while(board[b].val != '+' && board[a].val != '+')
	{
		cout << "\nPlease make sure you're moving YOUR coin into an EMPTY cell: ";
	}
	board[b].val = '+';
	place(val, a);
}

int main()
{
	drawBoard();
	int iniMoves = 9;
	while(!gameEnd && iniMoves >=1)
	{
		int a;
		cout << "\nPlayer 1, please enter cell number: ";
		cin >> a;
		place('A', a);
		cout << "\nPlayer 2, please enter cell number: ";
		cin >> a;
		place('B', a);
		iniMoves--;
	}
	while(!gameEnd)
	{
		int a, b;
		cout << "\nPlayer 1, please enter from cell number and to cell number: ";
		cin >> a >> b;
		makeMove('A', a, b);
		cout << "\nPlayer 2, please enter from cell number and to cell number: ";
		cin >> a >> b;
		makeMove('B', a, b);
	}

	cout << "\nCongratulations, player" << winner << " !You won the game :)";
	
	return 0;
}
