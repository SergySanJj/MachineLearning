#pragma once

#ifndef LifeGame_H_
#define LifeGame_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <Windows.h>
#include <random>
#include <algorithm>

using namespace std;

/*
	_  used for empty field
	*  used for player field
	+  used for food field
*/

#define INFOSIZE 5     // Player info vector size
#define MAXSTEPS 10000 // maximum number of steps in each game
#define FOODVALUE 20
#define MAXLEN 10000.0f // max coord of vector to enemy (etalon)
#define PAUSE_BETWEEN_GAMES 10

class Player;

/*
struct FieldCell
{
	char symbol = '_';
	Player* _player = nullptr;

	void movePlayer(Player* player,int x_from, int y_from, int x_to, int y_to);
};
*/

class Field
{
public:
	Field(int n, int m);
	~Field();

	void setXY(int X, int Y, char symbol);
	char getXY(int X, int Y);

	void printField();
	void clearField();
private:
	int _n = 1;
	int _m = 1;
	char** _field = nullptr;
};

struct Food
{
	int pos_x = 0;
	int pos_y = 0;
};

struct stepNode
{
	int _x = 0;
	int _y = 0;

	Player* _player = nullptr;
};

struct deadPlayer
{
	Player* _player = nullptr;
	int lastStep = 0;
};

class LifeGame
{
public:
	LifeGame(int n, int m, int numberOfPlayers);
	LifeGame(int n, int m, int numberOfPlayers, bool echo);
	~LifeGame();

	void setPause(unsigned int time_);
	void echo(bool value); // 1 - print 0 - don't print
	char getXY(int X, int Y);
	bool checkMove(int new_x, int new_y);

	void step();
	void play();
	void teach();
	void printField();
	
private:
	int _n = 1;
	int _m = 1;
	unsigned int _step = 0;
	unsigned int _evolution = 0;
	unsigned int _pause = 100;
	bool _echo = 1;
	Field* _field = nullptr;
	vector<Player*> players;
	vector<deadPlayer*> deadPlayers;
	vector<Food*> food;

	friend void setXY(int X, int Y, char symbol, LifeGame&);
	friend void movePlayer(int pl_x, int pl_y, int new_x, int new_y, LifeGame&);
	void generateFood();
	void assigneCells();

	float* formInputVector(Player* formFor);
};

#endif // !LifeGame_H_