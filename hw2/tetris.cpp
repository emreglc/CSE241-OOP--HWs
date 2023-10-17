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
	xPos = 1;
}

// no parameter constructor to use in driver1
Tetris::Tetris(){
	board.resize(15, vector<char>(25));
	xPos = 1;
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

	int flag = 0;// flag to detect if tetromino can be moved to left to make the best fit

	cout << "\033[" + to_string(board.size()+1) + "A";// moving the cursor to the start of the board before each draw operation
	drawBoard();
	this_thread::sleep_for(chrono::milliseconds(50));// sleep function which is the delay between each cycle
	
	fitTetromino(tetro, flag);// preparing tetromino to be fit before lowering it
	
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

	// checking if tetromino can be moved to left
	if(flag == 1){
		joinTetromino(tetro);
		cout << "\033[" + to_string(board.size()) + "A";
		drawBoard();
	} 
		

	// updating posX which is the x index to place tetrominos
	this->xPos += tetro.getTetro()[0].size();

}

// function to draw the board on terminal
void Tetris::drawBoard(){
	for(auto a : board){
		for(auto b : a){
			cout << b;
		}
		cout << endl;
	}
	cout << "\033[s";
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

// fit function which rotates and moves the tetromino at the top before
// it falls in order to obtain best fit 
void Tetris::fitTetromino(Tetromino &tetro, int &flag){

	int mid = (board[0].size() - tetro.getTetro()[0].size())/2;

	removeTetromino(tetro, mid, "top");
	
	// canFit function takes a parameter to decide which operation will be done
	// 0 for checking if tetromino can move left
	// 1 for checking if tetromino can fit
	for (int i = 0; i < 4; i++)
	{
		if (!tetrominos[tetrominos.size()-2].canFit(tetro, 0)){
			tetro.rotate("right");
			tetrominos[tetrominos.size()-1] = tetro;
		} 
		else{
			flag = 1;// tetromino can move left
			break;
		} 
	}

	if (flag == 0)
	{
		for (int i = 0; i < 4; i++){
			if (!tetrominos[tetrominos.size()-2].canFit(tetro, 1)){
				tetro.rotate("right");
				tetrominos[tetrominos.size()-1] = tetro;
			} 
			else break;
		}
	}
	moveTetromino(tetro);
}

// moves the tetromino at the top before it falls
void Tetris::moveTetromino(Tetromino &tetro){
	for (int i = 0; i < tetro.getTetro().size(); i++)
		for (int j = 0; j < tetro.getTetro()[i].size(); j++)
			board[i+1][j+xPos] = tetro.getTetro()[i][j];
}

// moves the tetromino left to join the other tetromino to create the best fit
void Tetris::joinTetromino(Tetromino &tetro){
	removeTetromino(tetro, xPos, "bottom");
	this_thread::sleep_for(chrono::milliseconds(50));
	xPos--;
	for (int i = 0; i < tetro.getTetro().size(); i++)
		for (int j = 0; j < tetro.getTetro()[i].size(); j++)
			if(board[board.size() - 2 - i][j+xPos] == ' ') board[board.size() - 2 - i][j+xPos] = tetro.getTetro()[tetro.getTetro().size() - 1 - i][j];
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