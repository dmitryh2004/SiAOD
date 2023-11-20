#include "Graph.h"

Graph::Graph(bool isDirected, int size, vector<string> names)
{
	this->isDirected = isDirected;
	this->size = size;
	this->matrix = new int*[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->matrix[i] = new int[this->size];
		for (int j = 0; j < this->size; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
	this->names = names;
	while (this->names.size() < size) //добавляем имена при необходимости
		this->names.push_back("not found");
}

Graph::~Graph()
{
	for (int i = 0; i < this->size; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	while (names.size() > 0)
		names.pop_back();
}

void Graph::show()
{
	int offset = 0;
	for (int i = 0; i < size; i++)
	{
		offset = (names[i].size() > offset) ? names[i].size() : offset;
	}
	cout << "Матрица смежности графа: " << endl;
	cout << setw(offset+1) << "|";
	for (int i = 0; i < size; i++)
	{
		cout << setw(offset) << names[i] << "|";
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << setw(offset) << names[i] << "|";
		for (int j = 0; j < size; j++)
		{
			cout << setw(offset) << matrix[i][j] << "|";
		}
		cout << endl;
	}
}

bool Graph::addPath(int verticeA, int verticeB, int weight)
{
	if ((verticeA < 0) || (verticeA >= size) || (verticeB < 0) || (verticeB >= size))
	{
		return false;
	}
	matrix[verticeA][verticeB] = weight;
	if (!isDirected)
	{
		matrix[verticeB][verticeA] = weight;
	}
	return true;
}

bool Graph::addPath(string nameA, string nameB, int weight)
{
	int vA = -1, vB = -1;
	for (int i = 0; i < size; i++)
	{
		if (names.at(i) == nameA) vA = i;
		if (names.at(i) == nameB) vB = i;
	}
	return addPath(vA, vB, weight);
}

bool Graph::removePath(int verticeA, int verticeB) {
	if ((verticeA < 0) || (verticeA >= size) || (verticeB < 0) || (verticeB >= size))
	{
		return false;
	}
	matrix[verticeA][verticeB] = 0;
	if (!isDirected)
	{
		matrix[verticeB][verticeA] = 0;
	}
	return true;
}

bool Graph::removePath(string nameA, string nameB)
{
	int vA = -1, vB = -1;
	for (int i = 0; i < size; i++)
	{
		if (names.at(i) == nameA) vA = i;
		if (names.at(i) == nameB) vB = i;
	}
	return removePath(vA, vB);
}

void Graph::showChainsFromVertice(int verticeIndex, string currentChain) {
	bool deadEnd = true;
	for (int i = 0; i < size; i++)
	{
		if ((matrix[verticeIndex][i] > 0) && (currentChain.find(names[i]) == string::npos))
		{
			deadEnd = false;
			showChainsFromVertice(i, currentChain + " - " + names[i]);
		}
	}
	if (deadEnd)
	{
		cout << currentChain << endl;
	}
}

void Graph::getAllChains(int verticeIndex, string currentChain, int currentLength, vector<string>& output, vector<int>& lengthOutput) {
	bool deadEnd = true;
	for (int i = 0; i < size; i++)
	{
		if ((matrix[verticeIndex][i] > 0) && (currentChain.find(names[i]) == string::npos))
		{
			deadEnd = false;
			getAllChains(i, currentChain + " -> " + names[i], currentLength + matrix[verticeIndex][i], output, lengthOutput);
		}
	}
	if (deadEnd)
	{
		output.push_back(currentChain);
	}
}

void Graph::showAllChains() {
	cout << "Все цепочки в графе: " << endl;
	for (int i = 0; i < size; i++)
	{
		showChainsFromVertice(i, names[i]);
	}
}

int Graph::getShortestPath(int verticeA, int verticeB)
{
	vector<string> temp;
	vector<int> l_temp;
	vector<string> paths;
	vector<int> pathsLength;
	getAllChains(verticeA, names[verticeA], 0, temp, l_temp);
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i].find(names[verticeB]) != string::npos)
		{
			string temp_s = temp[i].substr
			(0, temp[i].find(names[verticeB]) + names[verticeB].size());
			bool is_unique = true;
			for (int j = 0; j < paths.size(); j++)
			{
				if (paths[j] == temp_s) {
					is_unique = false;
					break;
				}
			}
			if (is_unique)
			{
				paths.push_back(temp_s);
				int pathLength = 0;
				int start = 0;
				int end = 0;
				int vLast = 0;
				int vCurrent = 0;
				while (end < temp_s.size())
				{
					if (start == string::npos)
						end = temp_s.size();
					else
					{
						end = temp_s.find("->", start);
						string temp_s_sub = temp_s.substr(start, end - start - 1);
						for (int j = 0; j < size; j++)
						{
							if (names[j] == temp_s_sub)
							{
								vCurrent = j;
								break;
							}
						}
						pathLength += matrix[vLast][vCurrent];
						vLast = vCurrent;
					}
					start = temp_s.find_first_not_of(" ", end + 2);
				}
				pathsLength.push_back(pathLength);
			}
		}
	}
	if (paths.size() > 0)
	{
		int minLength = pathsLength[0];
		cout << "Пути между вершинами " << names[verticeA] << ", " << names[verticeB] << ":" << endl;
		for (int i = 0; i < paths.size(); i++)
		{
			if (minLength > pathsLength[i])
				minLength = pathsLength[i];
			cout << paths[i] << ", длина: " << pathsLength[i] << endl;
		}
		cout << "Минимальная длина пути: " << minLength << endl;
	}
	else
	{
		cout << "Пути между вершинами " << names[verticeA] << ", " << names[verticeB] << " не найдены" << endl;
	}
	temp.clear();
	l_temp.clear();
	paths.clear();
	pathsLength.clear();
	return 0;
}

int Graph::getShortestPath(string verticeA, string verticeB)
{
	int vA = -1, vB = -1;
	for (int i = 0; i < size; i++)
	{
		if (names.at(i) == verticeA) vA = i;
		if (names.at(i) == verticeB) vB = i;
	}
	return getShortestPath(vA, vB);
}
