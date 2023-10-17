#include "TetrisVector.h"
#include "TetrisArray1D.h"
#include "TetrisAdapter.h"
#include "TetrisAdapter.cpp"
using namespace tetris;

#include <deque>
using namespace std;

template<class Game>
void menu(Game &game){
	fstream file;
	char shape, paraShape;
	bool gameOver = false;
	vector<Tetromino> tetrominos;
	do{
		cout << "\033[s" << "\033[K";
		cout << "Enter the tetromino shape(I, O, T, J, L, S, Z  &  R for random, Q for quit, K to save current game): ";
		cin >> shape;
		shape = game.upperCase(static_cast<int>(shape));
		while(shape != 'I' && shape != 'O' && shape != 'T' && shape != 'J' && shape != 'L' && shape != 'S' && shape != 'Z' && shape != 'R' && shape != 'Q' && shape != 'K'){
			cout << "\033[u" << "\033[K";
			cout << "Enter the tetromino shape(I, O, T, J, L, S, Z  &  R for random, Q for quit, K to save current game): ";
			cin >> shape;
			shape = game.upperCase(static_cast<int>(shape));
		}

		if(shape == 'Q') break;
		if(shape == 'R') shape = game.randShape();
		if(shape == 'K'){
			file.open("board.txt", ios::out);
			game.writeToFile(file);
			cout << "Board written to board.txt...\n";
			break;
		}
		paraShape = shape;
		tetrominos.push_back(Tetromino::defShape(shape));
		if(tetrominos.size() != 0) game += tetrominos[tetrominos.size() - 1];
		game.animate(tetrominos[tetrominos.size() - 1], paraShape);
		game.increaseTotalMove();
	}while(!gameOver);
	file.close();
}

int main(){

	int height, width, flag = 0;
	char type, saved;
	fstream file("board.txt", ios::in);
	string buffer;

	cout << "Would you like to continue from the saved txt file?(Y or N): ";
	cin >> saved;

	if (saved == 'Y')
	{
		try
		{
			getline(file, buffer);
			if(buffer.length() == 0) throw buffer;
			else{
				TetrisVector game;
				game.readFromFile(file);
				game.drawBoard();
				menu(game);
			}
		}
		catch(string buffer)
		{
			cerr << "There is no saved file" << '\n';
		}
	}
	else if (saved == 'N'){

		cout << "--------- Welcome to TETRIS!! ---------" << endl << endl;
		cout << "Enter the height of the board: ";
		cin >> height;
		cout << "Enter the width of the board: ";
		cin >> width;

		do{
			flag = 0;

			cout << "Enter the type of the tetris class(V for vector, 1 for array1D, A for adaptor): ";
			cin >> type;

			if (type == 'V')
			{
				TetrisVector game(height, width);
				menu(game);
			}else if(type == '1'){
				TetrisArray1D game(height, width);
				menu(game);
			}else if(type == 'A'){
				TetrisAdapter<deque<char>> game(height, width);
				menu(game);
			}else{
				flag = 1;
			}

		}while(flag != 0);
	}		
	
	else cout << "Invalid input, terminating...";

	file.close();
	return 0;
}

