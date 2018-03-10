#include <iostream>
#include "NeuralNetwork.h"
#include "FileSystem.h"

using namespace std;

int main()
{
	NeuralNetwork net("lifeGame");
	FileSystem fs;
	net.addLayer(5, "input");
	net.addLayer(28, "between");
	net.addLayer(3, "output");

	net.connectLayers("input", "between");
	net.connectLayers("between", "output");

	net.randomizeWeights("input", "between", -1.0f, 2.0f);
	net.saveWeightsToDirectory(L"F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\saves", "input", "between");
	net.saveWeightsToDirectory(L"F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\saves", "between", "output");
	float mass[5] = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };
	net.setLayerData(mass, "input");
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