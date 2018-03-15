#pragma once

#ifndef Player_H_
#define Player_H_

#include <ctime>
#include <stdlib.h>

using namespace std;

#define MAXFIELD 1000.0f
#define DEAFULTHEALTH 100.0

/// COMMANDS ///


class NeuralNetwork;
class LifeGame;

class Player
{
public:
	Player(int n, int m, int playerID, LifeGame* game);
	~Player();

	int get_X();
	int get_Y();
	float getHealth();

	pair<int,int> step(float* inputData); // returns pair with new coordinates

private:
	int playerID = 0;

	float health = DEAFULTHEALTH;
	float closestFood_X = MAXFIELD;
	float closestFood_Y = MAXFIELD;

	LifeGame* currGame = nullptr;

	int pos_x = 0;
	int pos_y = 0;

	NeuralNetwork* neuro = nullptr;

};

#endif // !Player_H_