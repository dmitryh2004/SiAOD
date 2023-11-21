// siaod_p2_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale.h>
#include <conio.h>
//graph.h
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class Graph {
	bool isDirected = false;
	int size;
	int** matrix;
	vector<string> names;
public:
	//common methods
	Graph(bool isDirected, int size, vector<string> names);
	~Graph();
	void show();
	bool addPath(int verticeA, int verticeB, int weight);
	bool addPath(string nameA, string nameB, int weight);
	bool removePath(int verticeA, int verticeB);
	bool removePath(string nameA, string nameB);

	//find all chains
	void showChainsFromVertice(int verticeIndex, string currentChain);
	void showAllChains();

	//shortest path
	void getAllChains(int verticeIndex, string currentChain, int currentLength, vector<string>& output, vector<int>& lengthOutput);
	int getShortestPath(int verticeA, int verticeB);
	int getShortestPath(string verticeA, string verticeB);
};

//graph.cpp

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
	while (this->names.size() < size) //��������� ����� ��� �������������
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
	int offset = 3;
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
	if ((verticeA < 0) || (verticeA >= size) || (verticeB < 0) || (verticeB >= size) || (verticeA == verticeB))
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
	if ((verticeA < 0) || (verticeA >= size) || (verticeB < 0) || (verticeB >= size) || (verticeA == verticeB))
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
	int minLength = 0;
	if ((verticeA < 0) || (verticeA >= size) || (verticeB < 0) || (verticeB >= size))
	{
		return -1;
	}
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
		minLength = pathsLength[0];
		int min_index = 0;
		cout << "Пути между вершинами " << names[verticeA] << ", " << names[verticeB] << ":" << endl;
		for (int i = 0; i < paths.size(); i++)
		{
			if (minLength > pathsLength[i])
			{
				minLength = pathsLength[i];
				min_index = i;
			}
			cout << paths[i] << ", длина: " << pathsLength[i] << endl;
		}
		cout << "Наикратчайший путь: " << paths[min_index] << ", его длина: " << minLength << endl;
	}
	else
	{
		cout << "Пути между вершинами " << names[verticeA] << ", " << names[verticeB] << " не найдены" << endl;
	}
	temp.clear();
	l_temp.clear();
	paths.clear();
	pathsLength.clear();
	return minLength;
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

int main()
{
	setlocale(LC_ALL, "ru");
	vector<string> names;
	int size = 0;
	cout << "Введите количество вершин -> ";
	string temp = "";
	cin >> size;
	for (int i = 0; i < size; i++)
	{
		cout << "Введите имя вершины #" << i << " -> ";
		cin >> temp;
		names.push_back(temp);
	}
	bool dir = false;
	cout << "Граф ориентированный? (0 - нет, другое - да)" << endl;
	cin >> dir;
	Graph graph = Graph(dir, size, names);
	cin.ignore(32768, '\n');
	system("pause");
	system("cls");
	bool running = true;
	char choice = ' ';
	string vA = "", vB = "";
	int weight = 0;
	while (running)
	{
		cout << "Выберите действие:" << endl
		<< "[Q] - выход" << endl
		<< "[A] - добавить ребро" << endl
		<< "[R] - удалить ребро" << endl
		<< "[S] - вывести граф на экран" << endl
		<< "[C] - показать все цепочки в графе" << endl
		<< "[P] - найти кратчайший путь между вершинами" << endl;
		choice = _getch();
		switch(tolower(choice))
		{
			case 'q':
				running = false;
				break;
			case 's':
				graph.show();
				break;
			case 'a':
				cout << "Введите имя вершины A -> ";
				cin >> vA;
				cout << "Введите имя вершины B -> ";
				cin >> vB;
				cout << "Введите вес ребра -> ";
				cin >> weight;
				if (graph.addPath(vA, vB, weight))
				{
					cout << "Ребро добавлено успешно." << endl;
				}
				else
				{
					cout << "Ошибка при добавлении ребра. Возможно, имена вершин неправильны или совпадают." << endl;
				}
				cin.ignore(32768, '\n');
				break;
			case 'r':
				cout << "Введите имя вершины A -> ";
				cin >> vA;
				cout << "Введите имя вершины B -> ";
				cin >> vB;
				if (graph.removePath(vA, vB))
				{
					cout << "Ребро удалено успешно." << endl;
				}
				else
				{
					cout << "Ошибка при удалении ребра. Возможно, имена вершин неправильны или совпадают." << endl;
				}
				cin.ignore(32768, '\n');
				break;
			case 'c':
				graph.showAllChains();
				break;
			case 'p':
				cout << "Введите имя вершины A -> ";
				cin >> vA;
				cout << "Введите имя вершины B -> ";
				cin >> vB;
				if (graph.getShortestPath(vA, vB) == -1)
				{
					cout << "Имена вершин заданы неправильно." << endl;
				}
				cin.ignore(32768, '\n');
				break;
			default:
				cout << "Неизвестное действие." << endl;
		}
		if (running)
		{
			system("pause");
			system("cls");
		}
	}
	names.clear();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.