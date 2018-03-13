#include "LifeGame.h"
#include "Player.h"


LifeGame::LifeGame(int n, int m, int  numberOfPlayers) :_n(n), _m(m)
{
	this->_field = new Field(n, m);
	for (int i = 0; i < numberOfPlayers; i++)
		this->players.push_back(new Player(n, m, i));
}


LifeGame::~LifeGame()
{
}

void LifeGame::printField()
{
	this->_field->printField();
}

Field::Field(int n, int m) :_n(n), _m(m)
{
	this->_field = new char* [n];
	for (int i = 0; i < n; i++)
	{
		this->_field[i] = new char[m];
		for (int k=0;k<m;k++)
			this->_field[i][k] = '_';
	}
}

Field::~Field()
{
	for (int i = 0; i < this->_n; i++)
	{
		delete (this->_field[i]);
	}
	delete (this->_field);
}

void Field::setXY(int X, int Y, char symbol)
{
	if (X < this->_n && Y < this->_m)
		this->_field[X][Y] = symbol;
}

char Field::getXY(int X, int Y)
{
	return (this->_field[X][Y]);
}

void Field::printField()
{
	for (int i = 0; i < this->_n; i++)
	{
		for (int k = 0; k < this->_m; k++)
			cout << this->_field[i][k] << ' ';
		cout << '\n';
	}
}
