#include "Game.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

void Board::setBoard()
{
	vector<vector<Field>> tmp(size, vector<Field>(size));

	for (auto &t1 : tmp)
	{
		for (auto &t2 : t1)
		{
			if (rand() % 10 < minesProbabiliy)
				t2.setMine(true);
		}
	}

	fields = tmp;
}

void Board::displayBoard()
{
	cout.width(4);

	for (int i = 1; i < size + 1; i++)
	{
		cout << i;
		cout.width(2);
	}
	cout << endl;
	int counter = 1;

	for (auto t1 : fields)
	{
		cout.width(2);
		cout << counter++;

		for (auto t2 : t1)
		{
			if (t2.getOpen())
			{
				cout.width(2);				
				cout << t2.getMinesAround();				
			}
			else
			{
				cout.width(2);
				cout << (char)219;
			}
		}
		cout << endl << endl;
	}
}

void Board::displayFinalBoard()
{
	for (auto t1 : fields)
	{
		for (auto t2 : t1)
		{
			if (t2.getMine())
			{
				cout.width(2);
				cout << "!";
			}
			else
			{
				cout.width(2);
				cout << t2.getMinesAround();
			}
		}
		cout << endl << endl;
	}
}

void Board::openFields(vector<int> pos)
{	
	if ((pos[0] < 0 || pos[0] > size - 1))
		return;

	if ((pos[1] < 0 || pos[1] > size - 1))
		return;	
	
	if (fields[pos[0]][pos[1]].getMinesAround() == 0)
	{
		if (fields[pos[0]][pos[1]].getOpen() == false)
		{
			fields[pos[0]][pos[1]].setOpen(true);
			openMulti({ pos[0], pos[1] });
		}
		else
			return;
	}
	else
	{
		if (fields[pos[0]][pos[1]].getMine() == false)
			fields[pos[0]][pos[1]].setOpen(true);
		return;
	}
}

void Board::openMulti(vector<int> pos)
{
	openFields({ pos[0] + 1, pos[1] + 1});
	openFields({ pos[0] + 1, pos[1] });
	openFields({ pos[0] + 1, pos[1] - 1});
	openFields({ pos[0], pos[1] + 1});
	openFields({ pos[0], pos[1] - 1});
	openFields({ pos[0] - 1, pos[1] + 1});
	openFields({ pos[0] - 1, pos[1] });
	openFields({ pos[0] - 1, pos[1] - 1});
}


void Board::setNumbers()
{
	vector<vector<int>> result(fields.size() + 2, vector<int>(fields[0].size() + 2));

	for (size_t i = 1; i < result.size() - 1; i++)
	{
		for (size_t j = 1; j < result[0].size() - 1; j++)
		{
			if (fields[i - 1][j - 1].getMine())
			{
				result[i - 1][j - 1]++;
				result[i - 1][j + 1]++;
				result[i - 1][j]++;
				result[i][j - 1]++;
				result[i][j + 1]++;
				result[i + 1][j - 1]++;
				result[i + 1][j + 1]++;
				result[i + 1][j]++;
			}
		}
	}

	result.erase(result.begin());
	result.erase(result.begin() + result.size() - 1);

	for (auto &r : result)
	{
		r.erase(r.begin());
		r.erase(r.begin() + r.size() - 1);
	}

	for (size_t i = 0; i < result.size(); i++)
	{
		for (size_t j = 0; j < result[0].size(); j++)
		{
			fields[i][j].setMinesAround(result[i][j]);
			if (fields[i][j].getMine())
				fields[i][j].setMinesAround(-1);
		}
	}	
}

bool Game::isWin()
{
	for (auto t1 : board.fields)
	{
		for (auto t2 : t1)
		{
			if (!t2.getOpen() && !t2.getMine())
				return false;				
		}
	}

	return true;
}


bool Game::isGameOver(vector<int> positions)
{
	return (board.fields[positions[0] - 1][positions[1] - 1].getMine());
}

void Game::play()
{
	vector<int> positions(2);
	bool winner = false;

	do
	{
		system("cls");
		board.displayBoard();

		cout << endl << "Choose field: ";
		cin >> positions[0];
		cin >> positions[1];

		board.openMulti({ positions[0] - 1, positions[1] - 1 });
		board.fields[positions[0] - 1][positions[1] - 1].setOpen(true);

		if (isWin())
		{
			winner = true;
			break;
		}

	} while (!isGameOver(positions));

	system("cls");
	board.displayFinalBoard();

	string endGameMsg = (winner) ? "YOU WIN ! ! !" : "YOU LOSE !!!";
	cout << endl << endGameMsg << endl;
}