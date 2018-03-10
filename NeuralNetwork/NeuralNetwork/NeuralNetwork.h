#pragma once

#ifndef NeuralNetwork_H_
#define NeuralNetwork_H_

#include <fstream>
#include "Neuron.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <iterator>

using namespace std;

#define ID_ALREADY_EXISTS 1
#define ID_HAS_ERRORS     2

class FileSystem;

struct Layer
{
private:
	vector<Neuron> *neurons = nullptr;
	string id = "";                    // unique identifier for layer in network
	unsigned int size = 0;
	wstring pathToLayer = L"";
	string networkName = "";           // must be without _ . < > , \ / ? * symbols
	float(*activationFunction)(float); // pointer on function that returns float value and has one float argument

public:
	Layer(int n, string id);
	~Layer();

	wstring         getPath();
	string          getID();
	vector<Neuron>* getNeurons();
	float           getNeuronData(unsigned int n);
	unsigned int    getSize();

	template <size_t N>
	bool            setLayerData(float(&mas)[N]);
	void            setPath(const wstring &path);
	void            setNetworkName(const  string &name);
	void            setActivationFunction(float(*f)(float));
	
	void activateFunction();
	void linkWithLayer(Layer *linkWith);
	void outputData(const wstring &pathToFile);
};

#define layerPair pair< string, Layer* >

class NeuralNetwork
{
public:
	NeuralNetwork(const  string &name);
	~NeuralNetwork();

	template <size_t N>
	bool setLayerData(float(&mas)[N], const  string &ID);

	void addLayer(unsigned int neuronQuantity, const  string &layerID);
	bool connectLayers(const  string &ID1, const  string &ID2);
	bool loadWeightsFromFile(const wstring &pathToFile, const  string &IDFrom, const  string &IDTo);
	bool saveWeightsToDirectory(const wstring &pathToDirectory, const  string &IDFrom, const  string &IDTo);
	void deleteNetworkFiles();
private:
	unordered_map<string, Layer*> layers; // key, point to the layer of nodes
	string networkName = "a";
	FileSystem fs;

	inline bool checkLayerExist(const  string &ID);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<size_t N>
bool NeuralNetwork::setLayerData(float(&mas)[N], const  string &ID)
{
	if (checkLayerExist(ID))
	{
		(*(this->layers.find(ID))).second->setLayerData(mas);
		return 1;
	}
	else
	{
		return 0;
	}
}

template <size_t N>
bool Layer::setLayerData(float(&mas)[N])
{
	if (N < this->size)
		return 0;
	else
	{
		for (auto it = this->neurons->begin(); it != this->neurons->end(); ++it)
		{
			(*it).setInput(mas[distance(this->neurons->begin(), it)]);
		}
		return 1;
	}
}

#endif // NeuralNetwork_H_ 