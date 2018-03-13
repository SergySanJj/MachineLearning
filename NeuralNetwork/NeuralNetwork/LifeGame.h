#pragma once

#ifndef LifeGame_H_
#define LifeGame_H_

#include <iostream>
#include <vector>

using namespace std;

/*
	_  used for empty field
	*  used for player field
	+  used for food field
*/


#define N 5  // Player info vector size

class Player;

class Field
{
public:
	Field(int n, int m);
	~Field();

	void setXY(int X, int Y, char symbol);
	char getXY(int X, int Y);


	void printField();
private:
	int _n = 1;
	int _m = 1;
	char** _field = nullptr;
};

class LifeGame
{
public:
	LifeGame(int n, int m);
	~LifeGame();

	int* getPlayerInfo();
	void makeAction(int actionID);

	void printField();
private:
	int _n = 1;
	int _m = 1;
	unsigned int _step = 0;
	Field* _field = nullptr;
	vector<Player*> players;
};

#endif // !LifeGame_H_