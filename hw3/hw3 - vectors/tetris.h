#ifndef TETRIS_H
#define TETRIS_H

#include "tetromino.h"
#include <iostream>
#include <vector>

using namespace std;

class Tetris{
public:
	Tetris(const int height, const int width);
	Tetris();
	void createBoard();
	void placeTetromino(Tetromino &tetro);
	void removeTetromino(Tetromino &tetro, const int x, const string place);
	void moveTetromino(Tetromino &tetro, const int x);
	void drawBoard() const;
	void animate(Tetromino &tetro);
	const bool isGameOver();
	const vector<vector<char>> getBoard();
	const int getxPos();
	const char upperCase(int letter);
	const char randShape();
	Tetris& operator+=(Tetromino& tetro);

private:
	vector<vector<char>> board;
	vector<Tetromino> tetrominos;
	int xPos;
};

#endif