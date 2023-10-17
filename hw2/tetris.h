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
	void fitTetromino(Tetromino &tetro, int &flag);
	void moveTetromino(Tetromino &tetro);
	void joinTetromino(Tetromino &tetro);
	void drawBoard();
	void animate(Tetromino &tetro);
	const bool isGameOver();
	const vector<vector<char>> getBoard();
	const int getxPos();
	const char upperCase(int letter);
	const char randShape();

private:
	vector<vector<char>> board;
	vector<vector<char>> block;
	vector<Tetromino> tetrominos;
	int xPos;
};

#endif