#include "AbstractTetris.h"
using namespace tetris;

// selects a random shape for the tetromino
const char AbstractTetris::randShape() const{

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

void AbstractTetris::setLastMove(const char& shape, const string& dirR, const int countR, const string& dirM, const int countM){

	int countMM = countM;
	if(countM < 0) countMM = countM * -1;
	this->lm = string() + "Last move -> Rotate ";
	this->lm.push_back(shape);
	this->lm += string() + " to " + dirR + " " + to_string(countR) + " times, move to " + dirM + " " + to_string(countMM) + " times";

}

const string AbstractTetris::lastMove() const{

	try
	{
		if(this->lm.size() == 0) throw this->lm;
		else return this->lm;
	}
	catch(string lm)
	{
		cerr << "There is no last move yet." << '\n';
		return nullptr;
	}
	
}



