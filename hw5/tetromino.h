#ifndef TETROMINO_H
#define TETROMINO_H
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace tetris
{
	enum class Tetrominos
	{
		I = 'I',
		O = 'O',
		T = 'T',
		J = 'J',
		L = 'L',
		S = 'S',
		Z = 'Z'
	};
	class Tetromino
	{
	public:
		// enum class Tetrominos;
		Tetromino(Tetrominos shape);
		void rotate(string dir);
		void print();
		bool canFit(Tetromino &other, int op);
		vector<vector<char>> &getTetro();
		// void mostFit(vector<Tetromino> &tetros);
		Tetrominos getShapeName();
		static Tetrominos defShape(const char shape);

	private:
		vector<vector<char>> tetro;
		void init(Tetrominos shape);
		Tetrominos shapeName;
	};
}

#endif