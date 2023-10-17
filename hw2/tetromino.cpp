#include "tetromino.h"

//	constructor
Tetromino::Tetromino(Tetrominos shape)
{
	init(shape);
	shapeName = shape;
}

//	rotate function takes direction as a parameter and rotates the tetromino
//  90 degrees in given direction
void Tetromino::rotate(string dir)
{
	char swep;
	
	if(dir == "right")
	{
		vector<vector<char>> temp(this->getTetro()[0].size(), vector<char>(this->getTetro().size()));

		for (int row = 0; row < this->getTetro().size(); row++)
		{
			for (int col = 0; col < this->getTetro()[row].size(); col++)
			{
				temp[col][row] = this->getTetro()[row][col];
			}
			
		}
		for (int row = 0; row < temp.size(); row++)
		{
			for (int col = 0; col < temp[row].size()/2; col++)
			{
				swap(temp[row][col], temp[row][temp[row].size() - col - 1]);
			}
			
		}

		this->getTetro()= temp;

	}
	if(dir == "left")
	{

		for (int row = 0; row < this->getTetro().size(); row++)
		{
			for (int col = 0; col < this->getTetro()[row].size()/2; col++)
			{
				swap(this->getTetro()[row][col], this->getTetro()[row][this->getTetro()[row].size() - col - 1]);
			}
			
		}


		vector<vector<char>> temp(this->getTetro()[0].size(), vector<char>(this->getTetro().size()));

		for (int row = 0; row < temp.size(); row++)
		{
			for (int col = 0; col < temp[row].size(); col++)
			{
				temp[row][col] = this->getTetro()[col][row];
			}
			
		}

		this->getTetro()= temp;
		
	}
	
}

//	print function prints the current tetromino on the screen
void Tetromino::print()
{
	for (auto &a : this->getTetro())
	{
		for (auto &b : a)
		{
			cout << b;
		}

		cout << "\n";
	}	
}

//	canFit function takes the next tetromino as parameter and returns true if
// 	given tetromino can be put next to the current tetromino, returns false else 
bool Tetromino::canFit(Tetromino &other, int op)
{

	int canMove = 0, diff;

	if (op == 0)
	{
		//left is higher than right
		if(this->getTetro().size() > other.getTetro().size()){
			diff = this->getTetro().size() - other.getTetro().size();
			for(int i = this->getTetro().size() - 1; i >= diff; i--){
				if(!(this->getTetro().at(i).at(this->getTetro()[0].size() -1) == ' ') !=  
				!(other.getTetro().at(i-diff).at(0) == ' ')) canMove++;
			}
			if(canMove == other.getTetro().size()) return true;
			else return false;
		}//right is higher than left or equal
		else{
			diff =  other.getTetro().size() - this->getTetro().size();
			for(int i = other.getTetro().size() - 1; i >= diff; i--){
				if(!(this->getTetro().at(i-diff).at(this->getTetro()[0].size() -1) == ' ') !=  
				!(other.getTetro().at(i).at(0) == ' ')) canMove++;
			}
			if(canMove == this->getTetro().size()) return true;
			else return false;
		} 	
	}

	if (op == 1)
	{
		//cout << "3";
		if((this->getTetro()[this->getTetro().size() -1][this->getTetro()[0].size() -1] != ' ') && 
		(other.getTetro()[other.getTetro().size() -1][0] != ' '))
			return true;
		else return false;		
	}

	else return false;
}

//	mostFit function creates the best fit 2d vector of all tetrominos bundled together
//	it repeatedly calls canFit function to create the best fit version, if canFit returns
//	false, then it rotates the current tetromino by calling the function 'rotate'
/*void Tetromino::mostFit(vector<Tetromino> &tetros)
{
	tetros.insert(tetros.begin(), Tetromino(Tetrominos::J));
	
	for(int i = 0; i < tetros.size() -1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(tetros[i].canFit(tetros[i+1], 0) == true)
				break;
			else
				tetros[i].rotate("right");
		}
		// tetros[i].rotate("right");
	}


	tetros.erase(tetros.begin());
}*/

//	getter function for the tetromino vector
vector<vector<char>> &Tetromino::getTetro()
{
	return tetro;
}

//	getter function for the tetromino name in enum type
Tetrominos Tetromino::getShapeName()
{
	return shapeName;
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
			tetro = {
				{'I', 'I', 'I', 'I'}
			};	
			break;
		case Tetrominos::O:
			tetro = {
				{'O', 'O'},
				{'O', 'O'}
			};	
			break;
		case Tetrominos::T:
			tetro = {
				{'T', 'T', 'T'},
				{' ', 'T', ' '}
			};	
			break;
		case Tetrominos::J:
			tetro = {
				{' ', 'J'},
				{' ', 'J'},
				{'J', 'J'}
			};		
			break;
		case Tetrominos::L:
			tetro = {
				{'L', ' '},
				{'L', ' '},
				{'L', 'L'}
			};		
			break;
		case Tetrominos::S:
			tetro = {
				{' ', 'S', 'S'},
				{'S', 'S', ' '}
			};		
			break;
		case Tetrominos::Z:
			tetro = {
				{'Z', 'Z', ' '},
				{' ', 'Z', 'Z'}
			};		
			break;
	}
}


