#pragma once

#ifndef LifeGame_H_
#define LifeGame_H_

#include <iostream>

using namespace std;

/*
	_  used for empty field
	*  used for player field
	+  used for food field
*/

class Field
{
public:
	Field(int n, int m);
	~Field();

	void printField();
private:
	int _n = 1;
	int _m = 1;
	char* _field = nullptr;
};

class LifeGame
{
public:
	LifeGame(int n, int m);
	~LifeGame();

	void printField();
private:
	int _n = 1;
	int _m = 1;
	unsigned int _step = 0;
	Field* _field = nullptr;
};

#endif // !LifeGame_H_