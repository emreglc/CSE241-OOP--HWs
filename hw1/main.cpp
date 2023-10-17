#include "util.h"

using namespace std;

int main()
{

	// declaration section
	int tetroCount, i;
	vector<Tetromino> tetros;
	Tetromino result(Tetrominos::I);
	char shape;

	// getting input from user
	cout << "How many tetrominos would you like?\n";
	cin >> tetroCount;
	cout << "What are the types?\n";
	for (i = 0; i < tetroCount; i++){
		cin >> shape;
		tetros.push_back(tetros[i].defShape(shape));
	}

	// printing tetrominos
	cout << "Your tetrominos:\n\n";
	for (i = 0; i < tetroCount; i++)
	{
		tetros[i].print();
		cout << '\n';
	}
	
	result.mostFit(tetros);

	int height = 0;
	for (int i = 0; i < tetros.size(); i++)// setting the height variable the height of the current tetromino vector
		if (tetros[i].getTetro().size() > height) height = tetros[i].getTetro().size();


	result.getTetro().clear();

	// rotating tetrominos once in order to initialize result vector easier
	for(auto &tetro : tetros)
	{
		tetro.rotate("right");
	}

	// initialization of the result vector
	for(int i = 0; i < tetros.size(); i++)
	{
		for(auto &row : tetros[i].getTetro())
		{
			result.getTetro().push_back(row);
			while(result.getTetro()[result.getTetro().size() -1].size() < height)
				result.getTetro()[result.getTetro().size() -1].push_back('-');	
			
		}
	}

	// rotating tetrominos back to their shape
	for(auto &tetro : tetros)
	{
		tetro.rotate("left");
	}

	result.rotate("left");


	cout << "Best fit:\n\n";

	// printing the result
	result.print();
	

	
}