#include "tetromino.h"

using namespace tetris;

//	constructor
Tetromino::Tetromino(Tetrominos shape)
{
	init(shape);
	shapeName = shape;
}

//	destructor
Tetromino::~Tetromino(){
	if(tetro != nullptr){
		for (int i = 0; i < height; i++)
			delete[] tetro[i];
		delete[] tetro;
		tetro = nullptr;
	}
}

//	rotate function takes direction as a parameter and rotates the tetromino
//  90 degrees in given direction
void Tetromino::rotate(string dir)
{
	
	if(dir == "right")
	{
	
		char ** temp;
		temp = new char*[this->width];
		for (int i = 0; i < this->width; i++)
		{
			temp[i] = new char[this->height];
		}

		for (int row = 0; row < this->height; row++)
		{
			for (int col = 0; col < this->width; col++)
			{
				temp[col][row] = this->tetro[row][col];
			}
			
		}

		for (int row = 0; row < this->width; row++)
		{
			for (int col = 0; col < this->height/2; col++)
			{
				swap(temp[row][col], temp[row][this->height - col - 1]);
			}
			
		}

		for (int i = 0; i < width; i++)
			delete[] tetro[i];
		delete[] tetro;
		tetro = nullptr;

		swap(this->width, this->height);

		tetro = new char*[this->height];
		for (int i = 0; i < this->height; i++)
		{
			tetro[i] = new char[this->width];
		}

		for (int i = 0; i < this->height; i++)
		{
			for (int j = 0; j < this->width; j++)
			{
				this->tetro[i][j] = temp[i][j];
			}
			
		}

		for (int i = 0; i < width; i++)
		{
			delete[] temp[i];
		}
		
		delete[] temp;
		temp = nullptr;

	}
	if(dir == "left")
	{

		char ** temp;

		for (int row = 0; row < this->height; row++)
		{
			for (int col = 0; col < this->width/2; col++)
			{
				swap(this->tetro[row][col], this->tetro[row][this->width - col - 1]);
			}
				
		}

		temp = new char*[this->width];
		for (int i = 0; i < this->width; i++)
			temp[i] = new char[this->height];

		for (int row = 0; row < this->width; row++)
			for (int col = 0; col < this->height; col++)
				temp[row][col] = this->tetro[col][row];

		for (int i = 0; i < height; i++)
			delete[] tetro[i];
		delete[] tetro;
		tetro = nullptr;

		swap(this->width, this->height);

		tetro = new char*[this->height];
		for (int i = 0; i < this->height; i++)
			tetro[i] = new char[this->width];

		for (int i = 0; i < this->height; i++)
			for (int j = 0; j < this->width; j++)
				this->tetro[i][j] = temp[i][j];

		for (int i = 0; i < height; i++)
			delete[] temp[i];
		delete[] temp;
		temp = nullptr;
		
	}
	
}

//	print function prints the current tetromino on the screen
void Tetromino::print()
{

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
			cout << this->tetro[i][j];
		cout << endl;
	}
		
}

//	getter function for the tetromino vector
char ** Tetromino::getTetro()
{
	return this->tetro;
}

//	getter function for the tetromino name in enum type
Tetrominos Tetromino::getShapeName()
{
	return this->shapeName;
}

const int& Tetromino::getWidth(){
	return this->width;
}

const int& Tetromino::getHeight(){
	return this->height;
}

//	defShape function uses enum class to convert char input to enum type
Tetrominos Tetromino::defShape(const char shape)
{
	switch (shape)
	{
	case 'I':
		return Tetrominos::I;
		break;
	case 'O':
		return Tetrominos::O;
		break;
	case 'T':
		return Tetrominos::T;
		break;
	case 'J':
		return Tetrominos::J;
		break;
	case 'L':
		return Tetrominos::L;
		break;
	case 'S':
		return Tetrominos::S;
		break;
	case 'Z':
		return Tetrominos::Z;
		break;					
	}

	return Tetrominos::I;
}

//	init function is called by constructor. it initializes the current tetromino vector
void Tetromino::init(Tetrominos shape)
{
	switch(shape)
	{
		case Tetrominos::I:
			width = 4;
			height = 1;
			tetro = new char*[1];
			tetro[0] = new char[4];
			for (int i = 0; i < 4; i++) tetro[0][i] = 'I'; 
			break;
		case Tetrominos::O:
			width = 2;
			height = 2;
			tetro = new char*[2];
			tetro[0] = new char[2];
			tetro[1] = new char[2];
			for (int i = 0; i < 2; i++) tetro[0][i] = 'O';
			for (int i = 0; i < 2; i++) tetro[1][i] = 'O';
			break;
		case Tetrominos::T:
			width = 3;
			height = 2;
			tetro = new char*[2];
			tetro[0] = new char[3];
			tetro[1] = new char[3];
			for (int i = 0; i < 3; i++) tetro[0][i] = 'T';
			tetro[1][0] = ' ';
			tetro[1][1] = 'T';
			tetro[1][2] = ' ';
			break;
		case Tetrominos::J:
			width = 2;
			height = 3;
			tetro = new char*[3];
			tetro[0] = new char[2];
			tetro[1] = new char[2];
			tetro[2] = new char[2];
			for (int i = 0; i < 3; i++) tetro[i][1] = 'J';
			tetro[0][0] = ' ';
			tetro[1][0] = ' ';
			tetro[2][0] = 'J';
			break;
		case Tetrominos::L:
			width = 2;
			height = 3;
			tetro = new char*[3];
			tetro[0] = new char[2];
			tetro[1] = new char[2];
			tetro[2] = new char[2];
			for (int i = 0; i < 3; i++) tetro[i][0] = 'L';
			tetro[0][1] = ' ';
			tetro[1][1] = ' ';
			tetro[2][1] = 'L';		
			break;
		case Tetrominos::S:
			width = 3;
			height = 2;
			tetro = new char*[2];
			tetro[0] = new char[3];
			tetro[1] = new char[3];
			tetro[0][0] = ' ';	tetro[0][1] = 'S';	tetro[0][2] = 'S';
			tetro[1][0] = 'S';	tetro[1][1] = 'S';	tetro[1][2] = ' ';	
			break;
		case Tetrominos::Z:
			width = 3;
			height = 2;
			tetro = new char*[2];
			tetro[0] = new char[3];
			tetro[1] = new char[3];
			tetro[0][0] = 'Z';	tetro[0][1] = 'Z';	tetro[0][2] = ' ';
			tetro[1][0] = ' ';	tetro[1][1] = 'Z';	tetro[1][2] = 'Z';		
			break;
	}
}


