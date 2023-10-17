#include "tetris.h"
#include "tetromino.h"

int main(){

	Tetris tetris;
	vector<Tetromino> tetrominos;
	int flag = 0;
	bool gameOver;

	cout << "Starting the tests..............\n\n";
	cout << "Creating the board.............\n";
	tetris.createBoard();
	cout << "Done.\n";
	cout << "Drawing the board..............\n";
	tetris.drawBoard();
	cout << "Selecting a random tetromino.......\n";
	char shape = tetris.randShape();
	cout << "Placing the random tetromino at the top......\n";
	tetrominos.push_back(Tetromino::defShape(shape));
	tetris.placeTetromino(tetrominos[0]);
	tetris.drawBoard();
	cout << "Rotating the tetromino left once......\n";
	int mid = (tetris.getBoard()[0].size() - tetrominos[0].getTetro()[0].size())/2;
	tetris.removeTetromino(tetrominos[0], mid, "top");
	tetrominos[0].rotate("left");
	cout << "Moving the tetromino to the left.....\n";
	tetris.moveTetromino(tetrominos[0]);
	tetris.drawBoard();
	cout << "Animating the tetromino falling.........\n";
	for(int i = 0; i < tetris.getBoard().size()+1; i++) cout << "\n";
	tetris.animate(tetrominos[0]);
	cout << "Fitting a random tetromino to the previous one.......\n";
	for(int i = 0; i < tetris.getBoard().size()+1; i++) cout << "\n";
	shape = tetris.randShape();
	tetrominos.push_back(Tetromino::defShape(shape));
	tetris.animate(tetrominos[1]);
	cout << "Testing if game over state works.....";
	while(!tetris.isGameOver()){
		shape = tetris.randShape();
		tetrominos.push_back(Tetromino::defShape(shape));
		if(tetrominos.size() != 0) tetris.placeTetromino(tetrominos[tetrominos.size() - 1]);
		cout << endl;
		tetris.animate(tetrominos[tetrominos.size() - 1]);
		gameOver = tetris.isGameOver();
	}
	cout << "\nGame Over........\n";
}