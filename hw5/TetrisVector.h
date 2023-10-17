#ifndef TETRISVEC_H
#define TETRISVEC_H

#include "AbstractTetris.h"
using namespace tetris;

namespace tetris{

	class TetrisVector : public AbstractTetris{
		public:
			TetrisVector();
			TetrisVector(const int height, const int width);
			virtual void createBoard();
			virtual void placeTetromino(Tetromino &tetro);
			virtual void removeTetromino(Tetromino &tetro, const int x, const string place);
			virtual void moveTetromino(Tetromino &tetro, const int x);
			virtual void drawBoard() const;
			virtual void writeToFile(fstream &file);
			virtual void readFromFile(fstream &file);
			virtual void animate(Tetromino &tetro, char shape);
			virtual void animate(Tetromino &tetro);
			virtual const bool isGameOver(Tetromino &tetro);
			virtual bool canFall(Tetromino &tetro) const;
			inline vector<vector<char>> const getBoard(){return this->board;};
		private:
			vector<vector<char>> board;
	};

}

#endif