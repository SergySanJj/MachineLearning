#include "Neuron.h"
#include "NeuralNetwork.h"

float sigm(float x)  // standart Activation Function
{
	return (1.0f / (1.0f + float(pow(e, -x))));
}

Neuron::Neuron()
{
	this->data = 0.0f;
	this->activationFunction = &sigm;
}

Neuron::~Neuron()
{
	this->edges.clear();
}

void Neuron::setInput(float input)
{
	this->data = input;
}

void Neuron::activate()
{
	for (auto it = this->edges.begin(); it != this->edges.end(); ++it)
	{
		for (auto vectorIt = it->second.begin(); vectorIt != it->second.end(); ++vectorIt)
			(*vectorIt)->son->increase(((*vectorIt)->weight) * (this->data));
	}
}

inline void Neuron::increase(float value)
{
	this->data += value;
}

float Neuron::activateFunction()
{
	this->data = (this->activationFunction)(this->data);
	return this->data;
}

void Neuron::setActivationFunction(float(*f)(float))
{
	this->activationFunction = f;
}

void Neuron::createLink(Neuron & connectWith, const string &layerTo)
{
	TEdge *newEdge = new TEdge();
	newEdge->son = &connectWith;
	newEdge->weight = 0.0f;
	//newEdge->layerFrom = move(layerFrom);
	newEdge->layerTo = move(layerTo);
	//this->edges.push_back(newEdge);
	this->edges[layerTo].push_back(newEdge);
}

float Neuron::getData()
{
	return (this->data);
}

std::map<string, std::vector<TEdge*>>* Neuron::getEdges()
{
	return &this->edges;
}