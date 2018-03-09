#pragma once
#include <vector>
#include <cmath>
#include "FileSystem.h"

#define e 2.71828f

class Neuron;

struct TEdge
{
	Neuron *son = nullptr;
	float weight = 0.0f;
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
	void createLink(Neuron &connectWith);
	float getData();
private:
	float data = 0.0f;
	std::vector< TEdge* > edges;
	float(*activationFunction)(float);
};
