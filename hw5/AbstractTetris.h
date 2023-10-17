#ifndef ABSTETRIS_H
#define ABSTETRIS_H

#include "tetromino.h"
using namespace tetris;

#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;

namespace tetris{

	class AbstractTetris{

	public:
		AbstractTetris() : total_move(0){};
		virtual void createBoard() = 0;
		virtual void placeTetromino(Tetromino &tetro) = 0;
		virtual void removeTetromino(Tetromino &tetro, const int x, const string place) = 0;
		virtual void moveTetromino(Tetromino &tetro, const int x) = 0;
		virtual void drawBoard() const = 0;
		virtual void animate(Tetromino &tetro, char shape) = 0;
		virtual void animate(Tetromino &tetro) = 0;
		virtual const bool isGameOver(Tetromino &tetro) = 0;
		virtual bool canFall(Tetromino &tetro) const = 0;
		virtual void writeToFile(fstream &file) = 0;
		virtual void readFromFile(fstream &file) = 0;
		virtual void setLastMove(const char& shape, const string& dirR, const int countR, const string& dirM, const int countM);
		virtual inline const int numberOfMoves() const final{return this->total_move;};
		virtual inline const int getxPos() const final{return this->xPos;};
		virtual inline const int getyPos() const final{return this->yPos;};
		virtual inline const void setxPos(int x) final{this->xPos = x;};
		virtual inline const void setyPos(int y) final{this->yPos = y;};
		virtual inline const int getWidth() const final{return this->width;};
		virtual inline const int getHeight() const final{return this->height;};
		virtual const string lastMove() const final;
		virtual inline const void increaseTotalMove() final{this->total_move++;};
		virtual inline char upperCase(int letter) final{
			if(letter <= 122 && letter >= 97) return static_cast<char>(letter-32);
				else return letter;};
		virtual const char randShape() const final;
		virtual inline void operator+=(Tetromino& tetro){this->placeTetromino(tetro);};

	protected:
		int width;
		int height;
		int xPos;
		int yPos;
		int total_move;
		string lm;
	};

}

#endif