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


#define INFOSIZE 5  // Player info vector size

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

struct stepNode
{
	int _x = 0;
	int _y = 0;

	Player* _player = nullptr;
};

class LifeGame
{
public:
	LifeGame(int n, int m, int numberOfPlayers);
	~LifeGame();

	int* getPlayerInfo();
	void makeAction(int actionID);

	void step();

	char getXY(int X, int Y);
	void printField();
private:
	int _n = 1;
	int _m = 1;
	unsigned int _step = 0;
	Field* _field = nullptr;
	vector<Player*> players;

	friend void setXY(int X, int Y, char symbol, LifeGame&);
	friend void movePlayer(int pl_x, int pl_y, int new_x, int new_y, LifeGame&);
};

#endif // !LifeGame_H_