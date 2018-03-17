#include "Player.h"
#include "LifeGame.h"
#include "NeuralNetwork.h"

float partFunction(float x)
{
	if (x <= -2.5f)
		return -1.0f;
	if (x >= 2.5f)
		return 1.0f;
	else
		return 0.0f;
}

wstring ToWString(const string& s)
{
	wstring wsTmp(s.begin(), s.end());
	return wsTmp;
}

int paramToInt(float param)
{
	if ((param - 1.0f) < FLT_EPSILON)
	{
		return 1;
	}
	if ((param - 0.0f) < FLT_EPSILON)
	{
		return 0;
	}
	else
		return -1;
}

///////////////////////////////////////////////////////////////////

Player::Player(int n, int m, int playerID, LifeGame* game)
{
	mt19937 gen(unsigned int(time(0)));
	uniform_int_distribution<int> range_n{ 0,n - 1 };
	uniform_int_distribution<int> range_m{ 0,m - 1 };
	//default_random_engine re{};

	this->playerID = playerID;

	this->neuro = new NeuralNetwork("player_" + to_string(this->playerID));

	this->neuro->addLayer(6, "input");
	this->neuro->addLayer(28, "between");
	this->neuro->addLayer(2, "sigmoid");
	this->neuro->addLayer(2, "output");

	this->neuro->setActivationFunction("output", partFunction);

	this->neuro->connectLayers("input", "between");
	this->neuro->connectLayers("between", "sigmoid");
	this->neuro->connectLayers("sigmoid", "output"); // 1.0f weights

	string savesPath = "F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\PlayersSaves\\player_";
	savesPath += to_string(this->playerID) + "\\";

	wstring tmpstr(savesPath.begin(), savesPath.end());

	this->neuro->loadWeightsFromFile(tmpstr + L"input\\input_between_.txt", "input", "between");
	this->neuro->loadWeightsFromFile(tmpstr + L"between\\between_sigmoid_.txt", "between", "sigmoid");
	this->neuro->loadWeightsFromFile(tmpstr + L"sigmoid\\sigmoid_output_.txt", "sigmoid", "output");

	this->currGame = game;

	this->pos_x = range_n(gen);
	this->pos_y = range_m(gen);

	while (this->currGame->getXY(this->pos_x, this->pos_y) != '_')
	{
		this->pos_x = range_n(gen);
		this->pos_y = range_m(gen);
	}

	setXY(this->pos_x, this->pos_y, '*', *game);
}

Player::Player(int n, int m, int playerID, LifeGame * game, bool echo)
{
	this->_echo = echo;
	mt19937 gen(unsigned int(time(0)));
	uniform_int_distribution<int> range_n{ 0,n - 1 };
	uniform_int_distribution<int> range_m{ 0,m - 1 };
	//default_random_engine re{};

	this->playerID = playerID;

	this->neuro = new NeuralNetwork("player_" + to_string(this->playerID), echo);

	this->neuro->addLayer(6, "input");
	this->neuro->addLayer(28, "between");
	this->neuro->addLayer(2, "sigmoid");
	this->neuro->addLayer(2, "output");

	this->neuro->setActivationFunction("output", partFunction);

	this->neuro->connectLayers("input", "between");
	this->neuro->connectLayers("between", "sigmoid");
	this->neuro->connectLayers("sigmoid", "output"); // 1.0f weights

	string savesPath = "F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\PlayersSaves\\player_";
	savesPath += to_string(this->playerID) + "\\";

	wstring tmpstr(savesPath.begin(), savesPath.end());

	this->neuro->loadWeightsFromFile(tmpstr + L"input\\input_between_.txt", "input", "between");
	this->neuro->loadWeightsFromFile(tmpstr + L"between\\between_sigmoid_.txt", "between", "sigmoid");
	this->neuro->loadWeightsFromFile(tmpstr + L"sigmoid\\sigmoid_output_.txt", "sigmoid", "output");

	this->currGame = game;

	this->pos_x = range_n(gen);
	this->pos_y = range_m(gen);

	while (this->currGame->getXY(this->pos_x, this->pos_y) != '_')
	{
		this->pos_x = range_n(gen);
		this->pos_y = range_m(gen);
	}

	setXY(this->pos_x, this->pos_y, '*', *game);
}

Player::~Player()
{
	string savesPath = "F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\PlayersSaves\\player_";
	savesPath += to_string(this->playerID) + "\\";

	wstring tmpstr(savesPath.begin(), savesPath.end());
	if (this->neuro != nullptr)
	{
		this->neuro->saveWeightsToDirectory(tmpstr + L"input", "input", "between");
		this->neuro->saveWeightsToDirectory(tmpstr + L"between", "between", "sigmoid");
		this->neuro->saveWeightsToDirectory(tmpstr + L"sigmoid", "sigmoid", "output");

		this->neuro->deleteNetworkFiles();
	}		
}


int Player::get_X()
{
	return this->pos_x;
}

int Player::get_Y()
{
	return this->pos_y;
}

int Player::getID()
{
	return this->playerID;
}

float Player::getHealth()
{
	return this->health;
}

void Player::copyNeuro(const Player& right)
{
	if (this == &right)
	{
		return;
	}
	this->neuro->deleteNetworkFiles();
	delete this->neuro;

	this->neuro = right.neuro;
}

void Player::clearNeuroData()
{
	this->neuro->clearLayerData("input");
	this->neuro->clearLayerData("between");
	this->neuro->clearLayerData("sigmoid");
	this->neuro->clearLayerData("output");
}

void Player::activateNeuro(float * input)
{
	this->neuro->setLayerData(input, 6, "input");

	this->neuro->activateLayer("input");
	this->neuro->activateLayer("between");

	//this->neuro->activatonFunction("sigmoid");

	this->neuro->activateLayer("sigmoid");

	this->neuro->activatonFunction("output");

	float* output = (this->neuro->getData("output")); // output size = 2

	int tmp_x = paramToInt(output[0]) + this->pos_x;
	int tmp_y = paramToInt(output[1]) + this->pos_y;

	if (this->currGame->checkMove(tmp_x, tmp_y))
	{
		this->pos_x = tmp_x;
		this->pos_y = tmp_y;
	}

	delete[] output;
}

void Player::mutate()
{
	this->neuro->randomizeWeights("input", "between", -0.4f, 0.4f);
	this->neuro->randomizeWeights("between", "sigmoid", -0.4f, 0.4f);
}

void Player::addHealth(float value)
{
	this->health += value;
}

void Player::saveWeights()
{
	string savesPath = "F:\\work\\Git\\MachineLearning\\NeuralNetwork\\NeuralNetwork\\PlayersSaves\\player_";
	savesPath += to_string(this->playerID) + "\\";

	wstring tmpstr(savesPath.begin(), savesPath.end());

	this->neuro->saveWeightsToDirectory(tmpstr + L"input", "input", "between");
	this->neuro->saveWeightsToDirectory(tmpstr + L"between", "between", "sigmoid");
	this->neuro->saveWeightsToDirectory(tmpstr + L"sigmoid", "sigmoid", "output");
}

