#pragma once

#ifndef Neuron_H_
#define Neuron_H_

#include <vector>
#include <cmath>
#include <map>
#include "FileSystem.h"

#define e 2.71828f

class Neuron;
struct Layer;

struct TEdge
{
	Neuron *son = nullptr;
	float weight = 0.0f;
	string layerTo = "";
};

class Neuron
{
public:
	Neuron();
	~Neuron();

	void setInput(float input);
	void activate();
	inline void increase(float value);
	float activateFunction();
	void setActivationFunction(float(*f)(float));
	void createLink(Neuron &connectWith, const string &layerTo);
	float getData();
private:
	float data = 0.0f;
	std::map< string, std::vector< TEdge* > > edges;
	//std::vector< TEdge* > edges;
	float(*activationFunction)(float);
};

#endif // !Neuron_H_
