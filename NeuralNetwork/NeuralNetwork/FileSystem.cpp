#include "FileSystem.h"
#include "NeuralNetwork.h"

FileSystem::FileSystem()
{
	char path[MAX_PATH];
	GetCurrentDirectory(sizeof(path), path);

	this->currentPath = strToWstr(path);
	this->networkPath = this->currentPath;
}

FileSystem::~FileSystem()
{
}

wstring FileSystem::getCurDir()
{
	return (this->currentPath);
}

wstring FileSystem::organizeLayer(const string & networkName, const string & layerID)
{
	//createNetworkDir(strToWstr(networkName));
	return createLayerDir(strToWstr(layerID));
}

void FileSystem::organizeNetwork(const string & networkName)
{
	createNetworkDir(strToWstr(networkName));
}

void FileSystem::createNetworkDir(const wstring &name)
{
	wstring path = this->currentPath;
	path.append(L"\\");
	path.append(name);
	CreateDirectoryW(path.c_str(), NULL);
	this->networkPath = move(path); // start string was const so we don't need to c_str(), also we can not do copy and just use move()
}

wstring FileSystem::createLayerDir(const wstring &name)
{
	wstring path = this->networkPath;
	path.append(L"\\");
	path.append(name);
	CreateDirectoryW(path.c_str(), NULL);
	return path;
}

int FileSystem::StringToWString(std::wstring & ws, const std::string & s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}

wstring FileSystem::strToWstr(const string & s)
{
	wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(s);
}