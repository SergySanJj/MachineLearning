#include "LifeGame.h"
#include "Player.h"


int getMax(int a, int b)
{
	return ((a > b) ? a : b);
}


////////////////////////////////////////////////////////////////////

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
	while ((this->players.size() != 0) && (this->_step < MAXSTEPS))
	{
		vector<stepNode> stepNodes;
		for (auto it = this->players.begin(); it != this->players.end(); ++it)
		{
			float* params = formInputVector((*it));
			(*it)->activateNeuro(params);

			delete params;
		}
		//form input vector for each player
		//get output decisions from each
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
		for (int i = 0; i < this->players.size(); i++)
		{
			for (int k = i + 1; k < this->players.size(); k++)
			{
				if (this->players[i]->get_X() == this->players[k]->get_X() &&
					this->players[i]->get_Y() == this->players[k]->get_Y())
				{
					if (this->players[i]->getHealth() >= this->players[k]->getHealth()) 
					{
						bool alreadyExists = 0;
						for (auto dead = this->deadPlayers.begin(); dead != this->deadPlayers.end(); ++dead)
						{
							if ((*dead)->_player == this->players[k])
								alreadyExists = 1;
						}
						if (!alreadyExists)
						{
							deadPlayer* tmpDead = new deadPlayer();
							tmpDead->_player = this->players[k];
							tmpDead->lastStep = this->_step;

							this->deadPlayers.push_back(tmpDead);
						}
	
						
					}
				}
			}
		}

		for (int i = 0; i < this->players.size(); i++) /// HERE HERE HEREHERE HERE HERE!!!
		{
			this->players.
		}
		// if alive player stays on food cell health++
		// every player health --
		// check if dead 
		// put all dead players into vector of dead with mark of current step number
		// currNumber++
		// generate new food
		// Go to beginning 
	}
	//else
		// return results to wrapper function
	this->_step++;
}

char LifeGame::getXY(int X, int Y)
{
	return (this->_field->getXY(X, Y));
}

bool LifeGame::checkMove(int new_x, int new_y)
{
	if (new_x > 0 && new_y > 0)
	{
		if (new_x < this->_n && new_y < this->_m)
			return 1;
	}
	return 0;
}


void LifeGame::printField()
{
	this->_field->printField();
}

float * LifeGame::formInputVector(Player * formFor)
{
	float* mas = new float[6];
	mas[0] = formFor->getHealth();

	//** ENEMY **//
	if (this->players.size() == 1)
	{
		mas[1] = MAXLEN;
		mas[2] = MAXLEN;
		mas[3] = MAXLEN; // enemy far away & has big health
	}
	else
	{
		int etalonLen = 10000;
		Player* etalonPlayer = nullptr;
		for (auto it = this->players.begin(); it != this->players.end(); ++it)
		{
			if ((*it) != formFor)
			{
				int tmp = getMax(abs(formFor->get_X()- (*it)->get_X()),
					             abs(formFor->get_Y() - (*it)->get_Y()));
				if (etalonLen > tmp)
				{
					etalonLen = tmp;
					etalonPlayer = (*it);
				}
			}
		}
		mas[1] = float(etalonPlayer->get_X());
		mas[2] = float(etalonPlayer->get_Y());
		mas[3] = float(etalonPlayer->getHealth());
	}

	//** FOOD **//

	int etalonLen = 10000;
	Food* etalonFood = nullptr;
	for (auto it = this->food.begin(); it != this->food.end(); ++it)
	{
		int tmp = getMax(abs(formFor->get_X() - (*it)->pos_x),
			             abs(formFor->get_Y() - (*it)->pos_y));
		if (etalonLen > tmp)
		{
			etalonLen = tmp;
			etalonFood = (*it);
		}
	}
	mas[4] = float(etalonFood->pos_x);
	mas[5] = float(etalonFood->pos_y);

	return mas;
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


