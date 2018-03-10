#define _CRT_SECURE_NO_WARNINGS
#pragma once

#ifndef FileSystem_H_
#define FileSystem_H_

#include <iostream>
#include <windows.h>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
#include <fstream>

using namespace std;

class NeuralNetwork;
struct Layer;
class Neuron;

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	wstring getCurDir();                                                                              // returns path to current directory of .exe file
	wstring organizeLayer(const string &networkName, const string &layerID);                          // returns path to layer dir
	void organizeNetwork(const string &networkName);                                                  // creates directory in current directory with network name
	void createWeightFile(vector<Neuron>* neurons, const wstring &path, const string &connectedWith); // creates .txt file with weights of neurons vector of connection with layer with connectedWith ID

	void deleteNetwork();

private:
	wstring currentPath = L""; // path to .exe file
	wstring networkPath = L""; // path to network dir

	void createNetworkDir(const wstring &name);                   // creates network directory and put path value into networkPath field
	wstring createLayerDir(const wstring &name);                  // returns path to layer dir
	int StringToWString(std::wstring &ws, const std::string &s);  // converts string to wstring and changes wstring argument
	wstring strToWstr(const string &s);                           // converts string to wstring and returns wstring as output
};

#endif //  FileSystem_H_