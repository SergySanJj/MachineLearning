#include "NeuralNetwork.h"
#include "FileSystem.h"

float sigmoidFunction(float x)    // standart Activation Function
{
	return (1.0f / (1.0f + float(pow(e, -x))));
}

inline bool checkIn(const string &strIn, const string &str)
{
	return (strIn.find(str) != string::npos);
}

inline bool checkForFileName(const string &layerID)
{
	return (checkIn(layerID, ".") &&
		checkIn(layerID, "_") &&
		checkIn(layerID, "/") &&
		checkIn(layerID, "\\") &&
		checkIn(layerID, "?") &&
		checkIn(layerID, "<") &&
		checkIn(layerID, ">") &&
		checkIn(layerID, "*"));
}

wstring StringToWString(const std::string & s)
{
	std::wstring wsTmp(s.begin(), s.end());
	return wsTmp;
}

NeuralNetwork::NeuralNetwork(const string &name) :networkName(name)
{
	this->fs.organizeNetwork(name);
}

NeuralNetwork::~NeuralNetwork()
{
	for (auto it = this->layers.begin(); it != this->layers.end(); it++)
	{
		delete (*it).second;
	}
}

void NeuralNetwork::addLayer(unsigned int neuronQuantity, const string &layerID)
{
	if (checkForFileName(layerID)) // check on _ . < > , \ / ? * in id
	{
		throw ID_HAS_ERRORS;
		exit(ID_HAS_ERRORS);
	}
	if (this->layers.find(layerID) == this->layers.cend())
	{
		Layer * newLayer = new Layer(neuronQuantity, layerID);
		newLayer->setNetworkName(this->networkName);
		this->layers.insert(layerPair(layerID, newLayer));
		newLayer->setPath(this->fs.organizeLayer(this->networkName, layerID));
	}
	else
	{
		throw ID_ALREADY_EXISTS; // DO SOMETHING or write catch in wrapper for network class
		exit(ID_ALREADY_EXISTS);
	}
}

bool NeuralNetwork::connectLayers(const string &ID1, const string &ID2)
{
	if (checkLayerExist(ID1) && checkLayerExist(ID2))
	{
		(*(this->layers.find(ID1))).second->linkWithLayer((*(this->layers.find(ID2))).second);
		wstring pathToWeights = (*(this->layers.find(ID1))).second->getPath();
		pathToWeights += L"\\" + StringToWString(ID1) + L"_" + StringToWString(ID2) + L".txt";

		this->fs.createWeightFile(this->layers.find(ID1)->second->getNeurons(), pathToWeights, ID2);
		return 1;
	}
	else
		return 0;
}

inline bool NeuralNetwork::checkLayerExist(const string & ID)
{
	if (this->layers.find(ID) != this->layers.cend())
	{
		return 1;
	}
	return 0;
}

Layer::Layer(int n, string id) :id(id), size(n)
{
	this->activationFunction = &sigmoidFunction;
	this->neurons = new vector<Neuron>(n);
}

Layer::~Layer()
{
	delete this->neurons;
	this->neurons = nullptr;
}

wstring Layer::getPath()
{
	return this->pathToLayer;
}

void Layer::setPath(const wstring &path)
{
	this->pathToLayer = move(path);
}

void Layer::setNetworkName(const string &name)
{
	this->networkName = move(name);
}

string Layer::getID()
{
	return this->id;
}

unsigned int Layer::getSize()
{
	return (this->size);
}

void Layer::setActivationFunction(float(*f)(float))
{
	for (auto it = this->neurons->begin(); it != this->neurons->end(); ++it)
	{
		(*it).setActivationFunction(f);
	}
}

void Layer::activateFunction()
{
	for (auto it = this->neurons->begin(); it != this->neurons->end(); ++it)
	{
		(*it).activateFunction();
	}
}

float Layer::getNeuronData(unsigned int n)
{
	if (n < this->size)
	{
		return (this->neurons->at(n).getData());
	}
	else
		return 0.0f;
}

void Layer::linkWithLayer(Layer * linkWith)
{
	for (auto layer1 = this->neurons->begin(); layer1 != this->neurons->end(); ++layer1)
	{
		for (auto layer2 = linkWith->neurons->begin(); layer2 != linkWith->neurons->end(); ++layer2)
		{
			(*layer1).createLink(*layer2, linkWith->getID());
		}
	}
}

vector<Neuron>* Layer::getNeurons()
{
	return this->neurons;
}