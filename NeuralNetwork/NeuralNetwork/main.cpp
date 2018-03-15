#include <cstdlib>
#include <iostream>
#include "NeuralNetwork.h"
#include "FileSystem.h"
#include "LifeGame.h"
#include "Player.h"


using namespace std;

int main()
{
	LifeGame ldf(10, 10,10);
	ldf.printField();




	system("pause");
	/*
	NeuralNetwork net("lifeGame");
	FileSystem fs;
	net.addLayer(5, "input");
	net.addLayer(28, "between");
	net.addLayer(3, "output");

	net.connectLayers("input", "between");
	net.connectLayers("between", "output");

	//net.loadWeightsFromFile(L"F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\saves\\input_between_.txt", "input", "between");
	//net.loadWeightsFromFile(L"F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\saves\\between_output_.txt", "between", "output");

	float mass[5] = { 1, 2, 3, 4, 5 };
	net.setLayerData(mass, 5, "input");

	for (int i = 0; i < 5; i++)
	{
		net.mutate(-0.9f, 0.9f);
		net.clearLayerData("between");
		net.clearLayerData("output");

		net.activateLayer("input");
		net.activateLayer("between");

		net.activatonFunction("output");

		wstring tmp = L"saves\\result";
		tmp += to_wstring(i);
		tmp += L".txt";
		net.outputDataToFile("output", tmp);
	}

	

	

	//net.randomizeWeights("input", "between", -1.0f, 1.0f);
	//net.randomizeWeights("between", "output", -1.0f, 1.0f);

	//net.saveWeightsToDirectory(L"F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\saves", "input", "between");
	//net.saveWeightsToDirectory(L"F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\saves", "between", "output");
	//system("pause");
	//net.deleteNetworkFiles();
	*/

	
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