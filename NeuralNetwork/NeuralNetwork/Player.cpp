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

	this->neuro = new NeuralNetwork("payer_" + to_string(this->playerID));
}


Player::~Player()
{
}
