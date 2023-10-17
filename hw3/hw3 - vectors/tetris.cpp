#include "tetris.h"
#include "tetromino.h"
#include <chrono>
#include <thread>

using namespace std;

// constructor for the tetris class
Tetris::Tetris(const int height, const int width){

	board.resize(height, vector<char>(width));
	createBoard();
	drawBoard();
	
}

// no parameter constructor to use in driver1
Tetris::Tetris(){
	board.resize(15, vector<char>(25));
}

// initializes the board
void Tetris::createBoard(){

	for (int r = 0; r < board.size(); r++){
		for (int c = 0; c < board[0].size(); c++){
			if(c == 0 || r == 0 || c == board[0].size()-1|| r == board.size()-1) board[r][c] = '#';
			else board[r][c] = ' ';
		}
	}
	
}

// getter function for the board vector
vector<vector<char>> const Tetris::getBoard(){
	return this->board;
}

// getter function for the xPos variable
const int Tetris::getxPos(){
	return this->xPos;
}

// converts letters to uppercase for dynamic input using their ASCII codes
const char Tetris::upperCase(int letter){

	if(letter <= 122 && letter >= 97) return static_cast<char>(letter-32);
	else return letter;

}

// animate function is the main cycle function which is the base of many operations
// it rotates and lowers the tetromino one step repeatedly until is hits bottom
void Tetris::animate(Tetromino &tetro){

	string dir;
	int count;

	xPos = (board[0].size() - tetro.getTetro()[0].size())/2;

	cout << "\033[" + to_string(board.size() + 1) + "A";

	drawBoard();
	removeTetromino(tetro, xPos, "top");

	cout << endl;
	cout << "\033[s" << "\033[K";
	cout << "Please enter the direction of rotation(right or left): ";
	cin >> dir;
	cout << "\033[u" << "\033[K";
	cout << "Please enter how many times tetromino will be rotated: ";
	cin >> count;

	for (int i = 0; i < count; i++) tetro.rotate(dir);
	xPos = (board[0].size() - tetro.getTetro()[0].size())/2;

	cout << "\033[u" << "\033[K";
	cout << "Please enter the direction of movement(right or left): ";
	cin >> dir;
	cout << "\033[u" << "\033[K";
	cout << "Please enter how many times tetromino will be moved: ";
	cin >> count;

	if(dir == "left") count *= -1;
	if(dir == "left" || dir == "right"){
		xPos += count;
		moveTetromino(tetro, xPos);
	}

	cout << "\033[" + to_string(board.size() + 2) + "A";
	drawBoard();
	this_thread::sleep_for(chrono::milliseconds(50));// sleep function which is the delay between each cycle
	
	// lowering the tetromino
	for(int i = 1; i < board.size() - 2; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(50));
		for (int k = i + tetro.getTetro().size() - 1; k >= i && k < board.size() - 2; k--)
		{
			for (int j = xPos; j < xPos + tetro.getTetro()[0].size(); j++)
			{
				swap(board[k][j], board[k+1][j]);
			}
		}

		cout << "\033[" + to_string(board.size()) + "A";
		drawBoard();

	}

}

// function to draw the board on terminal
void Tetris::drawBoard() const{

	for(auto a : board){
		for(auto b : a){
			cout << b;
		}
		cout << endl;
	}

}

// overloaded += operator to add a tetromino at the top row in the middle
Tetris& Tetris::operator+=(Tetromino& tetro){

	this->placeTetromino(tetro);
	return *this;

}

// placing the tetromino on top middle of the board
void Tetris::placeTetromino(Tetromino &tetro){

	for (int i = 0; i < tetro.getTetro().size(); i++)
		for (int j = 0; j < tetro.getTetro()[i].size(); j++)
			board[i+1][j+(board[i].size() - tetro.getTetro()[i].size())/2] = tetro.getTetro()[i][j];
	if(tetrominos.size() == 0) tetrominos.push_back(Tetrominos::J);
	tetrominos.push_back(tetro);

}

// removes tetromino from the board, takes place parameter
// place shows that either the tetromino will be removed from top or bottom
void Tetris::removeTetromino(Tetromino &tetro, const int x, const string place){

	if(place == "top"){
		for (int i = 0; i < tetro.getTetro().size(); i++)
			for (int j = x; j < tetro.getTetro()[i].size()+x; j++)
				board[i+1][j] = ' ';
	}
	else if(place == "bottom"){
		for (int i = 0; i < tetro.getTetro().size(); i++)
			for (int j = x; j < tetro.getTetro()[i].size()+x; j++)
				board[board.size() - 2 -i][j] = ' ';
	}

}

// moves the tetromino at the top before it falls
void Tetris::moveTetromino(Tetromino &tetro, const int x){

	for (int i = 0; i < tetro.getTetro().size(); i++)
		for (int j = 0; j < tetro.getTetro()[i].size(); j++)
			board[i+1][j+x] = tetro.getTetro()[i][j];

}

// checks if the board is full, returns true if so
const bool Tetris::isGameOver(){

	if(xPos == board[0].size() - 1 || xPos + tetrominos[tetrominos.size() - 1].getTetro()[0].size() > board[0].size() - 1)
		return true;
	else return false;

}

// selects a random shape for the tetromino
const char Tetris::randShape(){

	int shape;

	srand(time(NULL));
	shape = rand() % 7 + 1;

	switch (shape)
	{
	case 1:
		return 'I';
		break;
	case 2:
		return 'O';
		break;
	case 3:
		return 'T';
		break;
	case 4:
		return 'J';
		break;
	case 5:
		return 'L';
		break;
	case 6:
		return 'S';
		break;
	case 7:
		return 'Z';
		break;						
	}

	return 'Q';

}