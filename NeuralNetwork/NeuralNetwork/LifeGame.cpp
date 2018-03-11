#include "LifeGame.h"



LifeGame::LifeGame(int n, int m) :_n(n), _m(m)
{
	this->_field = new Field(n, m);
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
	this->_field = new char[n*m];
	for (int i = 0; i < n*m; i++)
		this->_field[i] = '_';
}

Field::~Field()
{
	delete (this->_field);
}

void Field::printField()
{
	for (int i = 0; i < this->_n * this->_m; i++)
	{
		cout << this->_field[i] << ' ';

		if ((i+1) % this->_m == 0)
			cout << '\n';
	}
	cout << '\n';
}
