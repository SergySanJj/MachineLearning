#include <cstdlib>
#include <iostream>
#include "NeuralNetwork.h"
#include "FileSystem.h"
#include "LifeGame.h"
#include "Player.h"

using namespace std;

int main()
{
	for (int i = 0; i < 50; i++)
	{
		LifeGame* ldf = new LifeGame(20, 20, 10, 0);
		ldf->setPause(50);
		ldf->echo(0);
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