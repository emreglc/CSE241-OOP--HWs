#include "tetris.h"
#include "tetromino.h"

using namespace tetris;

int main(){

	Tetris * tetris = new Tetris;
	Tetromino * tetromino = nullptr;
	int flag = 0;
	bool gameOver;

	cout << "Starting the tests..............\n\n";
	cout << "Creating the board.............\n";
	tetris->createBoard();
	cout << "Done.\n";
	cout << "Drawing the board..............\n";
	tetris->drawBoard();
	cout << "Selecting a random tetromino.......\n";
	char shape = tetris->randShape();
	cout << "Placing the random tetromino at the top......\n";
	tetromino = new Tetromino(Tetromino::defShape(shape));
	tetris->placeTetromino(*tetromino);
	tetris->drawBoard();
	cout << "Rotating the tetromino left once......\n";
	int mid = (tetris->getWidth() - tetromino->getWidth())/2;
	tetris->removeTetromino(*tetromino, mid, "top");
	tetromino->rotate("left");
	cout << "Moving the tetromino to the left.....\n";
	tetris->moveTetromino(*tetromino, 1);
	tetris->drawBoard();
	cout << "Animating the tetromino falling.........\n";
	for(int i = 0; i < tetris->getHeight()+1; i++) cout << "\n";
	tetris->animate(*tetromino);
	cout << "Testing if game over state works.....";
	while(!tetris->isGameOver(*tetromino)){
		shape = tetris->randShape();
		delete [] tetromino;
		tetromino = new Tetromino(Tetromino::defShape(shape));
		cout << endl;
		tetris->animate(*tetromino);
		gameOver = tetris->isGameOver(*tetromino);
	}
	delete [] tetromino;
	delete [] tetris;
	cout << "\n\n\nGame Over........\n";
}