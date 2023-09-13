// siaod_p2_1_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale.h>
#include <conio.h>
#include <ctime>
#include <cmath>
#include <bitset>
#include <fstream>
#include <chrono>

using namespace std;

const int massive_length = 10000000 / 8; //делим на 8 - количество чисел в одном элементе char, 
//чтобы получить необходимую длину массива для сортировки целых чисел от 0 до 10^7

bool setNumber(int n, unsigned char* data)
{
	int k = n;
	unsigned char mask = 1 << (8 - (k % 8) - 1);
	if ((data[k / 8] & mask) != 0)
	{
		return false;
	}
	data[k / 8] = data[k / 8] | mask;
	return true;
}

void printNumbers(unsigned char* data)
{
	int n = 0;
	for (int i = 0; i < massive_length; i++)
	{
		bitset<8> temp(data[i]);
		for (int j = 7; j >= 0; j--)
		{
			if (temp[j] == 1)
			{
				cout << n << " ";
			}
			n++;
		}
	}
}

void insert(unsigned char* byte_massive, const char* path)
{
	fstream data_source = fstream(path, ios::in);
	if (!data_source) return;
	auto start = chrono::steady_clock::now();
	while(1)
	{
		int temp = -1;
		if (!data_source.eof())
		{
			data_source >> temp;
			setNumber(temp, byte_massive);
		}
		else
		{
			break;
		}
	}
	auto end = chrono::steady_clock::now();
	data_source.close();
	auto duration = chrono::duration_cast<chrono::microseconds> (end - start);
	cout << "Время сортировки данных - " << duration.count() << " мкс" << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	unsigned char* massive = new unsigned char[massive_length];
	for (int i = 0; i < massive_length; i++)
	{
		massive[i] = 0;
	}
	char choose = ' ';
	cout << "Выберите тип ввода: [M] - ручной, [A] - автоматический из файла: " << endl;
	while (!((tolower(choose) == 'm') || (tolower(choose) == 'a')))
	{
		choose = _getch();
	}
	int n = 0;
	switch(tolower(choose))
	{
	case 'm':
		cout << "Вводите не повторяющиеся целые числа в диапазоне [0; 9999999], для завершения введите -1:" << endl;
		while (true)
		{
			cin >> n;
			if (n == -1) break;
			if (!setNumber(n, massive))
				cout << "Это число уже вводилось. Введите другое или введите -1 для завершения." << endl;
		}
		break;
	case 'a':
		cout << "Введите путь к файлу с числами: " << endl;
		string path;
		getline(cin, path);
		fstream ds = fstream(path, ios::in);
		if (!ds) { 
			cout << "Файл не найден" << endl; 
		}
		else
		{
			cout << "Исходный массив: [ ";
			int temp;
			while (!ds.eof()) { 
				ds >> temp; 
				cout << temp << " ";
			}
			cout << "]" << endl;
			insert(massive, path.c_str());
		}
	}
	cout << "Отсортированный массив: [ ";
	printNumbers(massive);
	cout << "]" << endl;
	system("pause");
	delete[] massive;
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
