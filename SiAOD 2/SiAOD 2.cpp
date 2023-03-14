// SiAOD 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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

void quicksort(int* A, int from, int to, int64_t& comps, int64_t& moves)
{
	comps++;
	if (from >= to)
		return;
	int pivot = A[to];
	int pivot_index = from;
	for (int i = from; i < to; i++, comps++)
	{
		comps++;
		if (A[i] <= pivot)
		{
			moves++;
			swap(A[i], A[pivot_index]);
			pivot_index++;
		}
	}
	moves++;
	swap(A[to], A[pivot_index]);
	quicksort(A, from, pivot_index-1, comps, moves);
	quicksort(A, pivot_index+1, to, comps, moves);
}

void launch_sort(int* A, int size)
{
	int64_t comparisions = 0, moves = 0;
	auto start = chrono::steady_clock::now();

	quicksort(A, 0, size - 1, comparisions, moves);

	auto end = chrono::steady_clock::now();

	auto elapsed_mcs = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Сравнений: " << comparisions << "\nПеремещений: " << moves << endl;
	cout << "Время выполнения (мкс): " << elapsed_mcs.count() << endl;
}

void check_massive(int size)
{
	int* A = new int[size];
	generate(A, size);
	launch_sort(A, size);
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
	check_massive(1000000);
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
