#pragma once

#ifndef Player_H_
#define Player_H_

#include <ctime>
#include <stdlib.h>

using namespace std;

#define MAXFIELD 1000.0f
#define DEAFULTHEALTH 100.0

class NeuralNetwork;

class Player
{
public:
	Player(int n, int m, int playerID);
	~Player();

private:
	int playerID = 0;

	float health = DEAFULTHEALTH;
	float closestFood_X = MAXFIELD;
	float closestFood_Y = MAXFIELD;

	int pos_x = 0;
	int pos_y = 0;

	NeuralNetwork* neuro;

};

#endif // !Player_H_