#pragma once

#ifndef Player_H_
#define Player_H_

#include <ctime>
#include <stdlib.h>
#include <string>

using namespace std;

#define MAXFIELD 1000.0f
#define DEFAULTHEALTH 100.0

#define EMPTY_  '_'
#define PLAYER_ '*'
#define FOOD_   '+'

/// COMMANDS ///

class NeuralNetwork;
class LifeGame;

class Player
{
public:
	Player(int n, int m, int playerID, LifeGame* game);
	Player(int n, int m, int playerID, LifeGame* game, bool echo);
	~Player();

	NeuralNetwork * neuro = nullptr;
	/*
	Player& operator = (const Player& right) // not an = operator in common thought, here it just copy NN
	{
		if (this == &right)
		{
			return *this;
		}
		delete this->neuro;
		this->neuro = right.neuro;
		return *this;
	}*/

	int get_X();
	int get_Y();
	int getID();
	float getHealth();
	void copyNeuro(const Player& right);
	void clearNeuroData();
	void activateNeuro(float* input);
	void mutate();
	void addHealth(float value);
	void saveWeights();
	//pair<int,int> step(float* inputData); // returns pair with new coordinates

private:
	int playerID = 0;
	bool _echo = 1;
	float health = DEFAULTHEALTH;

	LifeGame* currGame = nullptr;

	int pos_x = 0;
	int pos_y = 0;
};

#endif // !Player_H_