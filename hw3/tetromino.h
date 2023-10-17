#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace tetris{

	enum class Tetrominos{
			I = 'I',
			O = 'O',
			T = 'T',
			J = 'J',
			L = 'L',
			S = 'S',
			Z = 'Z'
	};
	class Tetromino{
	public:
		Tetromino(Tetrominos shape);
		~Tetromino();
		void rotate(string dir);
		void print();
		char ** getTetro();
		const int& getWidth();
		const int& getHeight();
		Tetrominos getShapeName();
		static Tetrominos defShape(const char shape);
	private:	
		char ** tetro;
		int width;
		int height;
		void init(Tetrominos shape);
		Tetrominos shapeName;
	};

}

#endif