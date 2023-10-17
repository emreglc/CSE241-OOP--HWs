#include "TetrisVector.h"
#include "AbstractTetris.h"
using namespace tetris;

// constructor for the TetrisVector class
TetrisVector::TetrisVector(const int height, const int width){
	board.resize(height, vector<char>(width));
	this->height = height;
	this->width = width;
	createBoard();
	drawBoard();
}

// no parameter constructor
TetrisVector::TetrisVector(){
	this->height = 15;
	this->width = 25;
	board.resize(this->height, vector<char>(this->width));
	createBoard();
}

// initializes the board
void TetrisVector::createBoard(){
	for (int r = 0; r < board.size(); r++){
		for (int c = 0; c < board[0].size(); c++){
			if(c == 0 || r == 0 || c == board[0].size()-1|| r == board.size()-1) board[r][c] = '#';
			else board[r][c] = ' ';
		}
	}
}

// placing the tetromino on top middle of the board
void TetrisVector::placeTetromino(Tetromino &tetro){
	for (int i = 0; i < tetro.getTetro().size(); i++)
		for (int j = 0; j < tetro.getTetro()[i].size(); j++)
			board[i+1][j+(board[i].size() - tetro.getTetro()[i].size())/2] = tetro.getTetro()[i][j];
}

// removes tetromino from the board, takes place parameter
// place shows that either the tetromino will be removed from top or bottom
void TetrisVector::removeTetromino(Tetromino &tetro, const int x, const string place){
	if(place == "top"){
		for (int i = 0; i < tetro.getTetro().size(); i++)
			for (int j = x; j < tetro.getTetro()[i].size()+x; j++)
				this->board[i+1][j] = ' ';
	}
	else if(place == "bottom"){
		for (int i = 0; i < tetro.getTetro().size(); i++)
			for (int j = x; j < tetro.getTetro()[i].size()+x; j++)
				this->board[this->board.size() - 2 -i][j] = ' ';
	}
}

// moves the tetromino at the top before it falls
void TetrisVector::moveTetromino(Tetromino &tetro, const int x){
	for (int i = 0; i < tetro.getTetro().size(); i++)
		for (int j = 0; j < tetro.getTetro()[i].size(); j++)
			board[i+1][j+x] = tetro.getTetro()[i][j];
}

// function to draw the board on terminal
void TetrisVector::drawBoard() const{
	for(auto a : board){
		for(auto b : a){
			cout << b;
		}
		cout << endl;
	}
}

// animate function is the main cycle function which is the base of many operations
// it rotates and lowers the tetromino one step repeatedly until is hits bottom
void TetrisVector::animate(Tetromino &tetro, char shape){

	string dirR, dirM;
	int countR, countM;

	this->xPos = (this->width - tetro.getTetro()[0].size())/2;
	this->yPos = 1;

	cout << "\033[" + to_string(this->height + 1) + "A";
	drawBoard();
	removeTetromino(tetro, this->xPos, "top");
	// cout << endl;
	cout << "\033[s" << "\033[K";
	cout << "Please enter the direction of rotation(right or left): ";
	cin >> dirR;
	cout << "\033[u" << "\033[K";
	cout << "Please enter how many times tetromino will be rotated: ";
	cin >> countR;

	for (int i = 0; i < countR; i++) tetro.rotate(dirR);

	this->xPos = (this->width - tetro.getTetro()[0].size())/2;

	cout << "\033[u" << "\033[K";
	cout << "Please enter the direction of movement(right or left): ";
	cin >> dirM;
	cout << "\033[u" << "\033[K";
	cout << "Please enter how many times tetromino will be moved: ";
	cin >> countM;

	if(dirM == "left") countM *= -1;
	if(dirM == "left" || dirM == "right"){
		xPos += countM;
		moveTetromino(tetro, xPos);
	}

	cout << "\033[" + to_string(this->height + 1) + "A";
	drawBoard();
	
	this_thread::sleep_for(chrono::milliseconds(50));// sleep function which is the delay between each cycle

	while (canFall(tetro))
	{
		this_thread::sleep_for(chrono::milliseconds(50));
		for (int i = yPos; i < tetro.getTetro().size()+yPos; i++)
			for (int j = xPos; j < tetro.getTetro()[0].size() + xPos; j++)
				board[i][j] = ' ';

		this->yPos++;

		for (int i = 0; i < tetro.getTetro().size(); i++)
			for (int j = 0; j < tetro.getTetro()[0].size(); j++)
				if(board[i+yPos][j+xPos] == ' ')
					board[i+yPos][j+xPos] = tetro.getTetro()[i][j];

		cout << "\033[" + to_string(this->height) + "A";
		drawBoard();		

	}

	this->setLastMove(shape, dirR, countR, dirM, countM);
	
}

// modified animate function to use in test driver
void TetrisVector::animate(Tetromino &tetro){

	string dirR, dirM;
	int countR, countM;

	//this->xPos = (this->width - tetro.getTetro()[0].size())/2;
	this->yPos = 1;

	// // cout << "\033[" + to_string(this->height + 1) + "A";
	// // drawBoard();
	// removeTetromino(tetro, this->xPos, "top");
	// // cout << endl;
	// cout << "\033[s" << "\033[K";
	// cout << "Please enter the direction of rotation(right or left): ";
	// cin >> dirR;
	// cout << "\033[u" << "\033[K";
	// cout << "Please enter how many times tetromino will be rotated: ";
	// cin >> countR;

	// for (int i = 0; i < countR; i++) tetro.rotate(dirR);

	// this->xPos = (this->width - tetro.getTetro()[0].size())/2;

	// cout << "\033[u" << "\033[K";
	// cout << "Please enter the direction of movement(right or left): ";
	// cin >> dirM;
	// cout << "\033[u" << "\033[K";
	// cout << "Please enter how many times tetromino will be moved: ";
	// cin >> countM;

	// if(dirM == "left") countM *= -1;
	// if(dirM == "left" || dirM == "right"){
	// 	xPos += countM;
	// 	moveTetromino(tetro, xPos);
	// }

	// cout << "\033[" + to_string(this->height + 1) + "A";
	drawBoard();
	
	this_thread::sleep_for(chrono::milliseconds(50));// sleep function which is the delay between each cycle

	while (canFall(tetro))
	{
		this_thread::sleep_for(chrono::milliseconds(50));
		for (int i = yPos; i < tetro.getTetro().size()+yPos; i++)
			for (int j = xPos; j < tetro.getTetro()[0].size() + xPos; j++)
				board[i][j] = ' ';

		this->yPos++;

		for (int i = 0; i < tetro.getTetro().size(); i++)
			for (int j = 0; j < tetro.getTetro()[0].size(); j++)
				if(board[i+yPos][j+xPos] == ' ')
					board[i+yPos][j+xPos] = tetro.getTetro()[i][j];

		cout << "\033[" + to_string(this->height) + "A";
		drawBoard();		

	}

	char shape;

	for (int i = 0; i < tetro.getTetro().size(); i++)
		for (int j = 0; j < tetro.getTetro()[0].size(); j++)
			if(tetro.getTetro()[i][j] != ' ') shape = tetro.getTetro()[i][j];

	this->setLastMove(shape, "left", 1, "left", 3);

}

// canFall function checks whether tetromino can be lowered one row or not
bool TetrisVector::canFall(Tetromino &tetro) const{

	int c;

	for (int i = 0, c = 0; i < tetro.getTetro()[0].size(); i++)
	{
		if (this->board[this->yPos + tetro.getTetro().size()-1][xPos+i] == ' ')
		{
			c++;
		}
		else if(this->board[this->yPos + tetro.getTetro().size()][xPos+i] == ' ' &&
				this->board[this->yPos + tetro.getTetro().size()-1][xPos+i] == tetro.getTetro()[tetro.getTetro().size()-1][i]){
			c++;
		}
		if (c == tetro.getTetro()[0].size())
			return true;
		
	}

	return false;

}

// checks if the board is full, returns true if so
const bool TetrisVector::isGameOver(Tetromino &tetro){

	for (int i = 1; i < tetro.getTetro().size(); i++)
		for (int j = 1; j < this->width - 1; j++)
			if(this->board[i][j] != ' ') return true;

	return false;

}

void TetrisVector::writeToFile(fstream &file){

	file << "Total moves: " << to_string(total_move) << endl;
	file << this->lastMove() << endl;
	for (auto i = 0; i < this->height; i++)
	{
		for (auto j = 0; j < this->width; j++)
		{
			file << this->board[i][j];
		}
		if(i != this->height - 1) file << endl;
	}

}

void TetrisVector::readFromFile(fstream &file){

	string buffer;

	file.seekg(0, ios::beg);

	getline(file, buffer);
	this->total_move = stoi(buffer.substr(13, buffer.find('\0')));
	getline(file, buffer);
	this->lm = buffer;
	int j = 0;
	while(!file.eof()){
		getline(file, buffer);
		j++;
	}

	this->width = buffer.size();
	this->height = j;

	board.resize(this->height);
	for(int i=0; i<this->height; i++) board[i].resize(this->width);

	file.seekg(0, ios::beg);
	getline(file, buffer);
	getline(file, buffer);

	for (int i = 0; i < this->height; i++)
	{
		getline(file, buffer);
		for (int j = 0; j < this->width; j++)
		{
			if(buffer[j] == '-') this->board[i][j] = ' ';
			else this->board[i][j] = buffer[j];
		}
	}

}
