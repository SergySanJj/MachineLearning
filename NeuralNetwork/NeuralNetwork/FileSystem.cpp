#include "FileSystem.h"
#include "NeuralNetwork.h"

int DeleteDirectory(const std::string &pathToDelDir, bool bDeleteSubdirectories = 1)
{
	bool            bSubdirectory = false;       // Flag, indicating whether subdirectories have been found
	HANDLE          hFile;                       // Handle to directory
	string          strFilePath;                 // Filepath
	string          strPattern;                  // Pattern
	WIN32_FIND_DATA FileInformation;             // File information

	strPattern = pathToDelDir + "\\*.*";
	hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FileInformation.cFileName[0] != '.')
			{
				strFilePath.erase();
				strFilePath = pathToDelDir + "\\" + FileInformation.cFileName;

				if (FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (bDeleteSubdirectories)
					{
						// Delete subdirectory
						int iRC = DeleteDirectory(strFilePath, bDeleteSubdirectories);
						if (iRC)
							return iRC;
					}
					else
						bSubdirectory = true;
				}
				else
				{
					// Set file attributes
					if (::SetFileAttributes(strFilePath.c_str(), FILE_ATTRIBUTE_NORMAL) == FALSE)
						return ::GetLastError();

					// Delete file
					if (::DeleteFile(strFilePath.c_str()) == FALSE)
						return ::GetLastError();
				}
			}
		} while (::FindNextFile(hFile, &FileInformation) == TRUE);

		// Close handle
		::FindClose(hFile);

		DWORD dwError = ::GetLastError();
		if (dwError != ERROR_NO_MORE_FILES)
			return dwError;
		else
		{
			if (!bSubdirectory)
			{
				// Set directory attributes
				if (::SetFileAttributes(pathToDelDir.c_str(), FILE_ATTRIBUTE_NORMAL) == FALSE)
					return ::GetLastError();

				// Delete directory
				if (::RemoveDirectory(pathToDelDir.c_str()) == FALSE)
					return ::GetLastError();
			}
		}
	}

	return 0;
}

string wstrtTostr(wstring ws)
{
	using convert_type = std::codecvt_utf8<wchar_t>; // c++ 11 standart converter
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.to_bytes(ws);
}

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

wstring FileSystem::organizeLayer(const  string & networkName, const  string & layerID)
{
	return createLayerDir(strToWstr(layerID));
}

void FileSystem::organizeNetwork(const  string & networkName)
{
	createNetworkDir(strToWstr(networkName));
}

void FileSystem::createWeightFile(vector<Neuron>* neurons, const wstring & path, const  string &connectedWith)
{
	ofstream fout(path);
	for (auto it = neurons->begin(); it != neurons->end(); ++it)
	{
		for (auto vIt = it->getEdges()->find(connectedWith)->second.begin(); vIt != it->getEdges()->find(connectedWith)->second.end(); ++vIt)
		{
			fout << (*vIt)->weight << ' ';
		}
		fout << '\n';
	}

	fout.close();
}

void FileSystem::deleteNetwork()
{
	DeleteDirectory(wstrtTostr(this->networkPath));
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

wstring FileSystem::strToWstr(const  string & s)
{
	wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(s);
}