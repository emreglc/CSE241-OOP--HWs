#include "tetris.h"
#include "tetromino.h"

using namespace tetris;

#include <chrono>
#include <thread>

using namespace std;

// constructor for the tetris class
Tetris::Tetris(const int height, const int width){

	this->height = height;
	this->width = width;

	this->board = new char*[this->height];
	for (int i = 0; i < this->height; i++)
		this->board[i] = new char[this->width];
	
	createBoard();
	drawBoard();
	
}

// no parameter constructor to use in driver1
Tetris::Tetris(){
	this->board = new char*[15];
	for (int i = 0; i < 15; i++)
		this->board[i] = new char[25];
}

//	destructor
Tetris::~Tetris(){
	for (int i = 0; i < this->height; i++)
		delete [] this->board[i];
	delete [] this->board;
}

// initializes the board
void Tetris::createBoard(){

	for (int r = 0; r < this->height; r++){
		for (int c = 0; c < this->width; c++){
			if(c == 0 || r == 0 || c == this->width-1 || r == this->height-1) board[r][c] = '#';
			else board[r][c] = ' ';
		}
	}

}

// getter function for the xPos variable
const int Tetris::getxPos() const{
	return this->xPos;
}

// getter function for the yPos variable
const int Tetris::getyPos() const{
	return this->yPos;
}

const int Tetris::getWidth() const{
	return this->width;
}

const int Tetris::getHeight() const{
	return this->height;
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

	this->xPos = (this->width - tetro.getWidth())/2;
	this->yPos = 1;

	cout << "\033[" + to_string(this->height + 1) + "A";

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
	//tetro.print();
	//exit(1);
	xPos = (this->width - tetro.getWidth())/2;

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

	cout << "\033[" + to_string(this->height + 2) + "A";
	drawBoard();
	
	this_thread::sleep_for(chrono::milliseconds(50));// sleep function which is the delay between each cycle
	
	// lowering the tetromino
	/*for(int i = 1; i < this->height - 2 && canFall(tetro); i++, this->yPos++)
	{
		this_thread::sleep_for(chrono::milliseconds(50));
		for (int k = i + tetro.getHeight() - 1; k >= i && k < this->height - 2; k--)
		{
			for (int j = xPos; j < xPos + tetro.getWidth(); j++)
			{
				swap(board[k][j], board[k+1][j]);
			}
		}

		cout << "\033[" + to_string(this->height) + "A";
		drawBoard();

	}*/

	while (canFall(tetro))
	{
		this_thread::sleep_for(chrono::milliseconds(50));
		for (int i = yPos; i < tetro.getHeight()+yPos; i++)
			for (int j = xPos; j < tetro.getWidth() + xPos; j++)
				board[i][j] = ' ';

		this->yPos++;

		for (int i = 0; i < tetro.getHeight(); i++)
			for (int j = 0; j < tetro.getWidth(); j++)
				if(board[i+yPos][j+xPos] == ' ')
					board[i+yPos][j+xPos] = tetro.getTetro()[i][j];

		cout << "\033[" + to_string(this->height) + "A";
		drawBoard();		

	}
	

}

bool Tetris::canFall(Tetromino &tetro) const{

	int c;

	/*for (int i = 0, c = 0; i < tetro.getWidth(); i++){
		if(this->board[this->yPos + tetro.getHeight()][xPos + i] == ' ') 
			c++;
		if(c == tetro.getWidth()) 
			return true;
	}*/

	for (int i = 0, c = 0; i < tetro.getWidth(); i++)
	{
		if (tetro.getTetro()[tetro.getHeight()-1][i] == ' ')
		{
			c++;
		}
		else if(this->board[this->yPos + tetro.getHeight()][xPos+i] == ' '){
			c++;
		}
		if (c == tetro.getWidth())
			return true;
		
	}

	return false;

}

// function to draw the board on terminal
void Tetris::drawBoard() const{

	for (int i = 0; i < this->height; i++){
		for (int j = 0; j < this->width; j++)
			cout << this->board[i][j];
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

	for (int i = 0; i < tetro.getHeight(); i++)
		for (int j = 0; j < tetro.getWidth(); j++)
			board[i+1][j+(this->width - tetro.getWidth())/2] = tetro.getTetro()[i][j];	

}

// removes tetromino from the board, takes place parameter
// place shows that either the tetromino will be removed from top or bottom
void Tetris::removeTetromino(Tetromino &tetro, const int x, const string place){

	if(place == "top"){
		for (int i = 0; i < tetro.getHeight(); i++)
			for (int j = x; j < tetro.getWidth() + x; j++)
				board[i+1][j] = ' ';
	}
	else if(place == "bottom"){
		for (int i = 0; i < tetro.getHeight(); i++)
			for (int j = x; j < tetro.getWidth()+x; j++)
				board[this->height - 2 -i][j] = ' ';

	}

}

// moves the tetromino at the top before it falls
void Tetris::moveTetromino(Tetromino &tetro, const int x){

	for (int i = 0; i < tetro.getHeight(); i++)
		for (int j = 0; j < tetro.getWidth(); j++)
			board[i+1][j+x] = tetro.getTetro()[i][j];

}

// checks if the board is full, returns true if so
const bool Tetris::isGameOver(Tetromino &tetro){

	for (int i = 1; i < tetro.getHeight(); i++)
		for (int j = 1; j < this->width - 1; j++)
			if(this->board[i][j] != ' ') return true;

	return false;
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