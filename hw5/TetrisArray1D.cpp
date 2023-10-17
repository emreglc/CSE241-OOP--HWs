#include "AbstractTetris.h"
#include "TetrisArray1D.h"
using namespace tetris;

// constructor for the tetris class
TetrisArray1D::TetrisArray1D(const int height, const int width){

	this->height = height;
	this->width = width;

	this->board = new char[this->height * this->width];
	
	createBoard();
	drawBoard();
	
}

// no parameter constructor to use in driver1
TetrisArray1D::TetrisArray1D(){

	this->height = 15;
	this->width = 25;
	this->board = new char[15*25];
	createBoard();

}

//	destructor
TetrisArray1D::~TetrisArray1D(){

	if(this->board != nullptr) delete [] this->board;
}

// initializes the board
void TetrisArray1D::createBoard(){

	for (auto i = 0; i < this->width * this->height; i++)
	{
		if (i < this->width || i % this->width == 0 || i % this->width == this->width - 1 || i >= this->width * (this->height-1))
			this->board[i] = '#';
		else 
			this->board[i] = ' ';	
		
	}

}

// // animate function is the main cycle function which is the base of many operations
// // it rotates and lowers the tetromino one step repeatedly until is hits bottom
void TetrisArray1D::animate(Tetromino &tetro, char shape){

	string dirR, dirM;
	int countR, countM;

	this->xPos = (this->width - tetro.getTetro()[0].size())/2;
	this->yPos = 1;

	cout << "\033[" + to_string(this->height + 1) + "A";

	drawBoard();
	removeTetromino(tetro, xPos, "top");

	cout << "\033[s" << "\033[K";
	cout << "Please enter the direction of rotation(right or left): ";
	cin >> dirR;
	cout << "\033[u" << "\033[K";
	cout << "Please enter how many times tetromino will be rotated: ";
	cin >> countR;

	for (int i = 0; i < countR; i++) tetro.rotate(dirR);
	xPos = (this->width - tetro.getTetro()[0].size())/2;

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
				this->board[i * this->width + j] = ' ';

		this->yPos++;

		for (int i = 0; i < tetro.getTetro().size(); i++)
			for (int j = 0; j < tetro.getTetro()[0].size(); j++)
				if(board[(i+yPos) * this->width + j+xPos] == ' ')
					board[(i+yPos) * this->width + j+xPos] = tetro.getTetro()[i][j];

		cout << "\033[" + to_string(this->height) + "A";
		drawBoard();		

	}

	this->setLastMove(shape, dirR, countR, dirM, countM);
	

}

// modified animate function to use in test driver
void TetrisArray1D::animate(Tetromino &tetro){

	string dirR, dirM;
	int countR, countM;

	//this->xPos = (this->width - tetro.getTetro()[0].size())/2;
	this->yPos = 1;

	// cout << "\033[" + to_string(this->height + 1) + "A";

	// drawBoard();
	// removeTetromino(tetro, xPos, "top");

	// cout << "\033[s" << "\033[K";
	// cout << "Please enter the direction of rotation(right or left): ";
	// cin >> dirR;
	// cout << "\033[u" << "\033[K";
	// cout << "Please enter how many times tetromino will be rotated: ";
	// cin >> countR;

	// for (int i = 0; i < countR; i++) tetro.rotate(dirR);
	// xPos = (this->width - tetro.getTetro()[0].size())/2;

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
				this->board[i * this->width + j] = ' ';

		this->yPos++;

		for (int i = 0; i < tetro.getTetro().size(); i++)
			for (int j = 0; j < tetro.getTetro()[0].size(); j++)
				if(board[(i+yPos) * this->width + j+xPos] == ' ')
					board[(i+yPos) * this->width + j+xPos] = tetro.getTetro()[i][j];

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
bool TetrisArray1D::canFall(Tetromino &tetro) const{

	int c;

	for (int i = 0, c = 0; i < tetro.getTetro()[0].size(); i++)
	{
		if (this->board[(this->yPos + tetro.getTetro().size()-1) * this->width + xPos+i] == ' ')
		{
			c++;
		}
		else if(this->board[(this->yPos + tetro.getTetro().size()) * this->width + this->xPos+i] == ' ' &&
				this->board[(this->yPos + tetro.getTetro().size()-1) * this->width + this->xPos+i] == tetro.getTetro()[tetro.getTetro().size()-1][i]){
			c++;
		}
		if (c == tetro.getTetro()[0].size())
			return true;
		
	}

	return false;

}

// function to draw the board on terminal
void TetrisArray1D::drawBoard() const{

	for (int i = 0; i < this->height * this->width; i++){
		if(i % this->width == 0 && i != 0) cout << endl;
		cout << this->board[i];
	}
	cout << endl;

}

// // placing the tetromino on top middle of the board
void TetrisArray1D::placeTetromino(Tetromino &tetro){

	for (int i = 0; i < tetro.getTetro().size(); i++)
		for (int j = 0; j < tetro.getTetro()[0].size(); j++)
			board[(i+1) * this->width + j + (this->width - tetro.getTetro()[i].size())/2] = tetro.getTetro()[i][j];

}

// // removes tetromino from the board, takes place parameter
// // place shows that either the tetromino will be removed from top or bottom
void TetrisArray1D::removeTetromino(Tetromino &tetro, const int x, const string place){

	if(place == "top"){
		for (int i = 0; i < tetro.getTetro().size(); i++)
			for (int j = x; j < tetro.getTetro()[0].size() + x; j++)
				board[(i+1) * this->width + j] = ' ';
	}
	else if(place == "bottom"){
		for (int i = 0; i < tetro.getTetro().size(); i++)
			for (int j = x; j < tetro.getTetro()[0].size()+x; j++)
				board[(this->height - 2 -i) * this->width + j] = ' ';

	}

}

// moves the tetromino at the top before it falls
void TetrisArray1D::moveTetromino(Tetromino &tetro, const int x){

	for (int i = 0; i < tetro.getTetro().size(); i++)
		for (int j = 0; j < tetro.getTetro()[0].size(); j++)
			board[(i+1) * this->width + j+x] = tetro.getTetro()[i][j];

}

// checks if the board is full, returns true if so
const bool TetrisArray1D::isGameOver(Tetromino &tetro){

	for (int i = 1; i < tetro.getTetro().size(); i++)
		for (int j = 1; j < this->width - 1; j++)
			if(this->board[(i * this->width) + j] != ' ') return true;

	return false;

}

void TetrisArray1D::writeToFile(fstream &file){

	file << "Total moves: " << to_string(total_move) << endl;
	file << this->lastMove() << endl;
	for (auto i = 0; i < this->height; i++)
	{
		for (auto j = 0; j < this->width; j++)
		{
			if(this->board[i*this->width + j] == ' ') file << '-';
			else file << this->board[i*this->width + j];
		}
		if(i != this->height - 1) file << endl;
	}

}

void TetrisArray1D::readFromFile(fstream &file){

	string buffer;

	getline(file, buffer);
	total_move = stoi(buffer);
	int j = 0;
	while(!file.eof()){
		getline(file, buffer);
		for (auto i = 0; i < buffer.size(); i++)
		{
			this->board[j*this->width + i] = buffer[i];
		}
		j++;
	}

}