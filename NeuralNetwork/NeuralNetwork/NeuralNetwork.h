#pragma once

#ifndef NeuralNetwork_H_
#define NeuralNetwork_H_

#include <fstream>
#include "Neuron.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <iterator>
#include <random>

using namespace std;

#define ID_ALREADY_EXISTS 1
#define ID_HAS_ERRORS     2

class FileSystem;

class Layer
{
public:
	Layer(int n, string id);
	~Layer();

	wstring         getPath();
	string          getID();
	vector<Neuron>* getNeurons();
	float           getNeuronData(unsigned int n);
	unsigned int    getSize();

	void            setPath(const wstring& path);
	void            setNetworkName(const string& name);
	void            setActivationFunction(float(*f)(float));

	void            activateFunction();
	void            linkWithLayer(Layer *linkWith);
	void            outputData(const wstring& pathToFile);
	void            activate();
	void            clearData();

	template <size_t N>
	bool            setLayerData(float(&mas)[N])
	{
		if (N < this->size)
			return 0;
		else
		{
			for (auto it = this->neurons->begin();
				it != this->neurons->end(); ++it)
			{
				(*it).setInput(mas[distance(this->neurons->begin(), it)]);
			}
			return 1;
		}
	}

private:
	vector<Neuron> *neurons = nullptr;
	string id = "";                    // unique identifier for layer in network
	unsigned int size = 0;
	wstring pathToLayer = L"";
	string networkName = "";           // must be without _.<>,\/?* symbols
	float(*activationFunction)(float); // pointer on function that returns float
									   // value and has one float argument
};

#define layerPair pair< string, Layer* >

class NeuralNetwork
{
public:
	NeuralNetwork(const string& name);
	~NeuralNetwork();

	

	float* getData(const string& ID);

	void addLayer(unsigned int  neuronQuantity,
		          const string& layerID);

	bool connectLayers(const string& ID1,
		               const string& ID2);

	bool loadWeightsFromFile(const wstring& pathToFile,
		                     const  string& IDFrom,
		                     const  string& IDTo);

	bool saveWeightsToDirectory(const wstring& pathToDirectory,
		                        const  string& IDFrom,
		                        const  string& IDTo);

	bool randomizeWeights(const  string& IDFrom, 
		                  const  string& IDTo,
		                  const   float& a,
		                  const   float& b); // set layer weights to random [a..b]

	bool addRandomValueToWeights(const  string& IDFrom,
		                         const  string& IDTo,
		                         const   float& a,
		                         const   float& b); // adds to layer weights random floats [a..b]
	void mutate(const float &a, const float &b);

	void activateLayer(const string& ID);

	void outputDataToFile(const string& ID, const wstring& path);

	void activatonFunction(const string &ID);

	bool clearLayerData(const string& ID);

	void deleteNetworkFiles();

	template <size_t N>
	bool setLayerData(float(&mas)[N], const string& ID)
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
private:
	unordered_map<string, Layer*> layers; // key, point to the layer of nodes
	string networkName = "a";
	FileSystem fs;

	inline bool checkLayerExist(const string& ID);
};

//////////////////** templates **///////////////////////////



#endif // NeuralNetwork_H_ 