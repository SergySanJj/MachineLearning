#include "Player.h"
#include "LifeGame.h"
#include "NeuralNetwork.h"

Player::Player(int n, int m, int playerID, LifeGame* game)
{
	uniform_int_distribution<int> range_n{ 0,n };
	uniform_int_distribution<int> range_m{ 0,m };
	default_random_engine re{};

	this->neuro = new NeuralNetwork("payer_" + to_string(this->playerID));

	this->currGame = game;

	this->pos_x = range_n(re);
	this->pos_y = range_m(re);

	while (this->currGame->getXY(this->pos_x, this->pos_y) != '_')
	{
		this->pos_x = range_n(re);
		this->pos_y = range_m(re);
	}

	setXY(this->pos_x, this->pos_y, '*', *game);
}


Player::~Player()
{
	delete this->neuro;
}

int Player::get_X()
{
	return this->pos_x;
}

int Player::get_Y()
{
	return this->pos_y;
}

float Player::getHealth()
{
	return this->health;
}


