#pragma once

#include <vector>

using namespace std;

class Field
{
private:
	bool mine;
	bool open;
	int minesAround;

public:
	Field(bool m = false, bool o = false, int a = 0) : mine(m), open(o), minesAround(a){}

	void setMine(bool m) { mine = m; }
	bool getMine() const { return mine; }

	void setOpen(bool o) { open = o; }
	bool getOpen() const { return open; }

	void setMinesAround(int m) { minesAround = m; }
	int getMinesAround() const { return minesAround; }
};


class Board
{
private:
	int size;
	double minesProbabiliy;

public:
	vector<vector<Field>> fields;

	Board(int s, double m) : size(s), minesProbabiliy(m){ setBoard(); setNumbers(); }

	void setBoard();
	void setNumbers();
	void openMulti(vector<int> positions);
	void Board::openFields(vector<int> positions);

	void displayBoard();
	void displayFinalBoard();
};

class Game
{
private:
	Board board;

public:
	Game(int size = 10, double m = 0.01) : board(Board(size, m)){}
	~Game(){}
	bool isGameOver(vector<int> positions);
	bool Game::isWin();
	void play();
};






