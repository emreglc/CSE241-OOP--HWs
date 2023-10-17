#ifndef TETRIS_H
#define TETRIS_H

#include "tetromino.h"

using namespace tetris;

#include <iostream>
#include <vector>

using namespace std;

namespace tetris{

	class Tetris{
	public:
		Tetris(const int height, const int width);
		Tetris();
		~Tetris();
		void createBoard();
		void placeTetromino(Tetromino &tetro);
		void removeTetromino(Tetromino &tetro, const int x, const string place);
		void moveTetromino(Tetromino &tetro, const int x);
		void drawBoard() const;
		void animate(Tetromino &tetro);
		const bool isGameOver(Tetromino &tetro);
		const int getxPos() const;
		const int getyPos() const;
		const int getWidth() const;
		const int getHeight() const;
		inline const char upperCase(int letter) {
			if(letter <= 122 && letter >= 97) return static_cast<char>(letter-32);
				else return letter;};
		const char randShape();
		bool canFall(Tetromino &tetro) const;
		Tetris& operator+=(Tetromino& tetro);

	private:
		char ** board;
		int width;
		int height;
		int xPos;
		int yPos;
	};

}

#endif