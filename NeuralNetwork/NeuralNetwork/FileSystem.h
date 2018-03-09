#pragma once

#ifndef FileSystem_H_
#define FileSystem_H_

#include <iostream>
#include <windows.h>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>

using namespace std;

class NeuralNetwork;
struct Layer;
class Neuron;

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	wstring getCurDir();
	wstring organizeLayer(const string &networkName, const string &layerID); // returns path to layer dir
	void organizeNetwork(const string &networkName);
	void createWeightFile(vector<Neuron>* neurons);

private:
	wstring currentPath = L""; // path to .exe file
	wstring networkPath = L""; // path to network dir

	void createNetworkDir(const wstring &name);
	wstring createLayerDir(const wstring &name); // returns path to layer dir
	int StringToWString(std::wstring &ws, const std::string &s);
	wstring strToWstr(const string &s);
};

#endif //  FileSystem_H_