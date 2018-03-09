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
	string id = "";
	unsigned int size = 0;
	wstring pathToLayer = L"";
	string networkName = "";  // must be without _ . < > , \ / ? * symbols

	float(*activationFunction)(float);

public:

	Layer(int n, string id);

	~Layer();

	wstring getPath();
	void setPath(const wstring &path);
	void setNetworkName(const string &name);
	string getID();
	unsigned int getSize();
	void setActivationFunction(float(*f)(float));
	void activateFunction();
	float getNeuronData(unsigned int n);
	template <size_t N>
	bool setLayerData(float(&mas)[N]);
	void linkWithLayer(Layer *linkWith);

	vector<Neuron>* getNeurons();
};

#define layerPair pair< string, Layer* >

class NeuralNetwork
{
public:
	NeuralNetwork(const string &name);
	~NeuralNetwork();

	void addLayer(unsigned int neuronQuantity, const string &layerID);
	bool connectLayers(const string &ID1, const string &ID2);
	template <size_t N>
	bool setLayerData(float(&mas)[N], const string &ID);
private:
	unordered_map<string, Layer*> layers; // key, point to the layer of nodes
	string networkName = "a";
	FileSystem fs;

	inline bool checkLayerExist(const string &ID);
};

template<size_t N>
bool NeuralNetwork::setLayerData(float(&mas)[N], const string &ID)
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