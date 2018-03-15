#include "LifeGame.h"
#include "Player.h"


LifeGame::LifeGame(int n, int m, int  numberOfPlayers) :_n(n), _m(m)
{
	this->_field = new Field(n, m);
	for (int i = 0; i < numberOfPlayers; i++)
	{
		Player* tmpPlayer = new Player(n, m, i, this);
		this->players.push_back(tmpPlayer);
	}
		
}


LifeGame::~LifeGame()
{
	for (auto it  = this->players.begin();
		      it != this->players.end()  ; ++it)
	{
		delete (&(*(*it)));
	}
}

void LifeGame::step()
{
	// if any player alive
		vector<stepNode> stepNodes;
		//form input vector for each player
		//get output from each
		//write into stepNodes \|/
		for (auto it = this->players.begin();
			it != this->players.end(); ++it)
		{
			stepNode tmpNode;
			tmpNode._player = (&*(*it));
			tmpNode._x = tmpNode._player->get_X();
			tmpNode._y = tmpNode._player->get_Y();
			stepNodes.push_back(tmpNode);
		}
		//check on repeats in pair of coords
			//if so - > 
				// kill player with lesser health
		// if alive player stays on food cell health++
		// every player health --
		// check if dead 
		// put all dead players into vector of dead with mark of current step number
		// currNumber++
		// generate new food
		// Go to beginning 
	//else
		// return results to wrapper function
}

char LifeGame::getXY(int X, int Y)
{
	return (this->_field->getXY(X, Y));
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

void setXY(int X, int Y, char symbol, LifeGame& game)
{
	game._field->setXY(X, Y, symbol);
}

void movePlayer(int pl_x, int pl_y, int new_x, int new_y, LifeGame& game)
{
	game._field->setXY(pl_x, pl_y, '_');
}
