#include "TetrisVector.h"
#include "tetrisArray1D.h"
#include "tetrisAdapter.h"
#include "tetrisAdapter.cpp"
using namespace tetris;

#include <deque>
using namespace std;

void test(AbstractTetris &tetris){

	vector<Tetromino> tetrominos;

	tetris.createBoard();
	cout << "15x25 Board has been created:\n";
	tetris.drawBoard();
	cout << "Placing a random tetromino at the top......\n";
	tetrominos.push_back(Tetromino::defShape(tetris.randShape()));
	tetris.placeTetromino(tetrominos[tetrominos.size() - 1]);
	cout << "31" << endl;
	tetris.drawBoard();
	cout << "Rotating it to the left once and moving to the left 5 indexes.........\n";
	tetris.removeTetromino(tetrominos[tetrominos.size() - 1], (tetris.getWidth() - tetrominos[tetrominos.size() - 1].getTetro()[0].size())/2, "top");
	tetrominos[tetrominos.size() - 1].rotate("left");
	tetris.moveTetromino(tetrominos[tetrominos.size() - 1], (tetris.getWidth() - tetrominos[tetrominos.size() - 1].getTetro()[0].size())/2 - 5);
	tetris.setxPos((tetris.getWidth() - tetrominos[tetrominos.size() - 1].getTetro()[0].size())/2 - 5);
	tetris.drawBoard();
	cout << "Making it fall to the bottom..........\n";
	tetris.animate(tetrominos[tetrominos.size() - 1]);
	cout << "Placing another random tetromino at the top......\n";
	tetrominos.push_back(Tetromino::defShape(tetris.randShape()));
	tetris.placeTetromino(tetrominos[tetrominos.size() - 1]);
	tetris.setxPos((tetris.getWidth() - tetrominos[tetrominos.size() - 1].getTetro()[0].size())/2);
	tetris.drawBoard();
	cout << "Rotating it to the left once and moving to the left 3 indexes.........\n";
	tetris.removeTetromino(tetrominos[tetrominos.size() - 1], tetris.getxPos(), "top");
	tetrominos[tetrominos.size() - 1].rotate("left");
	tetris.moveTetromino(tetrominos[tetrominos.size() - 1], tetris.getxPos() - 3);
	tetris.setxPos(tetris.getxPos() - 3);
	tetris.drawBoard();
	cout << "Making it fall to the bottom..........\n";
	tetris.animate(tetrominos[tetrominos.size() - 1]);
}

int main(){

	TetrisAdapter<deque<char>> tetrisA;
	TetrisVector tetrisV;
	TetrisArray1D tetris1;
	TetrisVector savedGame;
	fstream file;
	file.open("test.txt", ios::out);

	cout << "Testing phase started................\n";
	cout << "Objects for all types are created...........\n";
	cout << "Starting with deque type game.........\n\n";
	AbstractTetris * tetris = &tetrisA;
	test(*tetris);
	cout << "Testing tetris type game.........\n\n";
	tetris = &tetrisV;
	test(*tetris);
	cout << "Testing array1D type game.........\n\n";
	tetris = &tetris1;
	test(*tetris);
	tetris->writeToFile(file);
	file.close();
	cout << endl << "Writing the board to test.txt.........\n" << "Done...\n\n";
	cout << "Reloading the saved game from test.txt.........\n";
	file.open("test.txt", ios::in);
	tetris = &savedGame;
	tetris->readFromFile(file);
	tetris->drawBoard();
	cout << endl << tetris->lastMove() << endl;
	cout << "Done...\n\n";

	cout << "\n\nAll tests are done...........\n";

	return 0;

}