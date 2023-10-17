#include "tetris.h"
#include "tetromino.h"

int main(){

	int height, width;
	char shape;
	bool gameOver = false;
	vector<Tetromino> tetrominos;

	cout << "--------- Welcome to TETRIS!! ---------" << endl << endl;
	cout << "Enter the height of the board: ";
	cin >> height;
	cout << "Enter the width of the board: ";
	cin >> width;

	Tetris tetris(height, width);

	do{
		cout << "\033[s" << "\033[K";
		cout << "Enter the tetromino shape(I, O, T, J, L, S, Z  &  R for random, Q for quit): ";
		cin >> shape;
		shape = tetris.upperCase(static_cast<int>(shape));
		while(shape != 'I' && shape != 'O' && shape != 'T' && shape != 'J' && shape != 'L' && shape != 'S' && shape != 'Z' && shape != 'R' && shape != 'Q'){
			cout << "\033[u" << "\033[K";
			cout << "Enter the tetromino shape(I, O, T, J, L, S, Z  &  R for random, Q for quit): ";
			cin >> shape;
			shape = tetris.upperCase(static_cast<int>(shape));
		}
		if(shape == 'Q') break;
		if(shape == 'R') shape = tetris.randShape();
		tetrominos.push_back(Tetromino::defShape(shape));
		if(tetrominos.size() != 0) tetris += tetrominos[tetrominos.size() - 1];
		tetris.animate(tetrominos[tetrominos.size() - 1]);
		gameOver = tetris.isGameOver();
	}while(!gameOver);

	return 0;
}

