#include <iostream>
#include <fstream>
#include <string>

void end();
void run();

using namespace std;

int getMenu() {
	int menu;
	char a;
	cout << "Welcome To Tic-tac-toe game! Play with your way!"<<endl;
	do {
		cout << "\t---Menu---" << endl;
		cout << "1. Play Game" << endl;
		cout << "2. Replay Game" << endl;
		cout << "0. Exit" << endl << "Your input: ";
		cin >> a;
		menu = (int)a - 48;
		if (menu < 0 || menu> 2) cout << "Invalid Input"<<endl;
	} while (menu< 0 || menu> 2);
	return menu;
}

char* getName(int index) {
	char *name = new char[100];
	cout << "Input player " << index << " name : ";
	if (index == 1)cin.ignore();
	cin.getline(name,100);
	return name;
}

template <size_t size_x, size_t size_y>

void printBoard(char (&board)[size_x][size_y]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
}

template <size_t size_x, size_t size_y>

bool checkWin(char(&board)[size_x][size_y]) {
	for (int i = 0; i < 3; i++) if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != '-') return true;
	for (int i = 0; i < 3; i++) if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != '-') return true;
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != '-')return true;
	if (board[0][2] == board[1][1] && board[2][0] == board[1][1] && board[1][1] != '-')return true;
	return false;
}

template <size_t size_x, size_t size_y>

bool checkValid(char(&board)[size_x][size_y],int pos) {
	int col = pos % 10;
	int row = (pos - col) / 10;
	if (col > 3 || col < 1)return false;
	if (row > 3 || row < 1)return false;
	if (board[row-1][col-1] != '-') return false;
	return true;
}

template <size_t size_x, size_t size_y>

void update(char(&board)[size_x][size_y], int pos, int round) {
	int col = pos % 10;
	int row = (pos - col) / 10;
	if (round % 2 == 1)	board[row-1][col-1] = 'X';
	else board[row-1][col-1] = 'O';
}

template <size_t size_x, size_t size_y>

void writeFile(char(&board)[size_x][size_y],ofstream &myfile) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			myfile << board[i][j];
		}
		myfile << endl;
	}
	myfile << endl;
}

void play() {
	ofstream myfile;
	myfile.open("save.txt", std::fstream::out | std::fstream::trunc);

	char board[3][3];
	int round = 0;
	memset(board, '-', 3 * 3 * sizeof(char));
	char *player1;
	char *player2;
	player1 = getName(1);
	do {
		player2 = getName(2);
	} while (strcmp(player2, player1)==0);

	do {
		int pos;
		do {
			if (round % 2 == 1)	cout << "Your turn " << player1 << ": ";
			else cout << "Your turn " << player2 << ": ";
			cin >> pos;
		} while (!checkValid(board, pos));
		update(board, pos, round);
		writeFile(board,myfile);
		printBoard(board);
		round++;
	} while (!checkWin(board) && round != 9);
	if (round == 9)cout << "Draw!!" << endl;
	else if (round % 2 == 1)	cout << "Player " << player2 << " win!!!" << endl;
	else cout << "Player " << player1 << " win!!!" << endl;
	myfile.close();
}

void replay() {
	string line;
	ifstream myfile("save.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}

	else cout << "Unable to open file";
}

void run() {
	int menu;
	do {
		switch (menu = getMenu()) {
		case 1:
			play();
			menu = 0;
			break;
		case 2:
			replay();
			menu = 0;
			break;
		}

	} while (menu != 0);
	end();
}

void end() {
	char a;
	do {
		cout << "Do you want to countinue?" << endl << "Your input(Y/N): ";
		cin >> a;
		if (a == 'Y' || a == 'y') {
			run();
		}
		else if (a == 'N' || a == 'n') {
			return;
		}
		else {
			cout << "Invalid Input" << endl;
		}
	} while (1);
}

int main() {

	run();

	getchar();
	return 0;
}