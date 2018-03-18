#include <cstdlib>
#include <iostream>
#include "NeuralNetwork.h"
#include "FileSystem.h"
#include "LifeGame.h"
#include "Player.h"

using namespace std;

int main()
{
	system("MODE CON: COLS=140 LINES=70");

	LifeGame* ldf = new LifeGame(20, 20, 10, 0);
	ldf->initializeAllWithRnd(-1.0f, 1.0f);
	ldf->play();
	delete ldf;
	for (int i = 0; i < 1000; i++)
	{
		LifeGame* ldf = new LifeGame(20, 20, 10, i);
		ldf->setPause(50);
		//ldf->echo(0);
		ldf->play();
		delete ldf;
	}
	//system("pause");
	return 0;
}

/// TODO ///
//1 filework (write/read weights from files +++ "interpretator" for network)
//2 write wrapper for NeuralNetwork class
//3 optimize file system

// write exeptions
// divide headers and cpp parts of code

/*
FILE SYSTEM:
name of network:
	layer name:
		id1_id2.txt ///

*/