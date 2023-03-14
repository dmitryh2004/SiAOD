// SiAOD 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale.h>
#include <chrono>
#include <ctime>

using namespace std;

void generate(int* A, int size)
{
	for (int i = 0; i < size; i++)
		A[i] = rand() % 32000;
}

void sort(int* A, int size)
{
	int64_t comparisions = 0, moves = 0;
	auto start = chrono::steady_clock::now();

	int minimal = 0;
	int index = 0;
	for (int i = 0; i < size; i++, comparisions++)
	{
		index = i;
		minimal = A[i];
		for (int j = i + 1; j < size; j++, comparisions++)
		{
			comparisions++;
			if (A[j] < minimal)
			{
				index = j;
				minimal = A[j];
			}
		}
		swap(A[i], A[index]);
		moves++;
	}

	auto end = chrono::steady_clock::now();

	auto elapsed_mcs = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Сравнений: " << comparisions << "\nПеремещений: " << moves << endl;
	cout << "Время выполнения (мкс): " << elapsed_mcs.count() << endl;
}

void check_massive(int size)
{
	int* A = new int[size];
	generate(A, size);
	sort(A, size);
	delete[] A;
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	check_massive(100);
	check_massive(1000);
	check_massive(10000);
	check_massive(100000);
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
