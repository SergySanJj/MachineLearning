#include <iostream>
#include "NeuralNetwork.h"
#include "FileSystem.h"

using namespace std;

int main()
{
	NeuralNetwork net("lifeGame");
	FileSystem fs;
	net.addLayer(2, "input");
	net.addLayer(4, "between");
	net.addLayer(3, "output");

	net.connectLayers("input", "between");
	net.connectLayers("between", "output");

	net.loadWeightsFromFile(L"F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\saves\\input_between_.txt", "input", "between");
	net.loadWeightsFromFile(L"F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\saves\\between_output_.txt", "between", "output");

	float mass[2] = { 0.1f, 0.2f };
	net.setLayerData(mass, "input");

	net.activateLayer("input");
	net.activateLayer("between");

	net.outputDataToFile("output", L"F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\saves\\result.txt");

	//net.randomizeWeights("input", "between", -1.0f, 1.0f);
	//net.randomizeWeights("between", "output", -1.0f, 1.0f);

	//net.saveWeightsToDirectory(L"F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\saves", "input", "between");
	//net.saveWeightsToDirectory(L"F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\saves", "between", "output");
	system("pause");
	net.deleteNetworkFiles();
	system("pause");
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