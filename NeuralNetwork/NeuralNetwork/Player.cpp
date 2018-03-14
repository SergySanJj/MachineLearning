#include "Player.h"
#include "LifeGame.h"
#include "NeuralNetwork.h"

Player::Player(int n, int m, int playerID)
{
	/*
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<int> distx(0, std::nextafter(n-2, INT_MAX));
	std::uniform_real_distribution<int> disty(0, std::nextafter(m-2, INT_MAX));
	*/
	srand(time(0));
	int rndx = rand() + n;
	int rndy = rand() + m;

	this->pos_x = rndx;
	this->pos_y = rndy;

	this->neuro = new NeuralNetwork("payer_" + to_string(this->playerID));
}


Player::~Player()
{
}
