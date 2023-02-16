// SiAOD 3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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

void merge(int* A, int* B, int start, int mid, int end, int64_t& comps, int64_t& moves)
{
	int merged_index = start, i = start, j = mid + 1;
	comps += 2;
	while (i <= mid && j <= end)
	{
		comps += 1;
		if (A[i] <= A[j]) {
			moves++;
			B[merged_index] = A[i];
			merged_index++; i++;
		}
		else {
			moves++;
			B[merged_index] = A[j];
			merged_index++; j++;
		}
	}
	while (i <= mid) {
		comps += 1;
		moves++;
		B[merged_index] = A[i];
		merged_index++; i++;
	}
	while (j <= end) {
		comps++;
		moves++;
		B[merged_index] = A[j];
		merged_index++; j++;
	}
	for (i = start; i <= end; i++)
	{
		comps++;
		moves++;
		A[i] = B[i];
	}
}

void merge_sort(int* A, int* secondary, int start, int end, int64_t& comps, int64_t& moves)
{
	if (start == end)
		return;

	int mid = start + ((end - start) >> 1);

	merge_sort(A, secondary, start, mid, comps, moves);
	merge_sort(A, secondary, mid + 1, end, comps, moves);
	merge(A, secondary, start, mid, end, comps, moves);
}

void launch_sort(int* A, int size)
{
	int64_t comparisions = 0, moves = 0;
	auto start = chrono::steady_clock::now();

	int* temp = new int[size];

	merge_sort(A, temp, 0, size-1, comparisions, moves);

	delete[] temp;

	auto end = chrono::steady_clock::now();

	auto elapsed_mcs = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Сравнений: " << comparisions << "\nПеремещений: " << moves << endl;
	cout << "Время выполнения (мкс): " << elapsed_mcs.count() << endl;
}

void check_massive(int size)
{
	cout << "--- Сортировка " << size << " элементов ---" << endl;
	int* A = new int[size];
	generate(A, size);
	launch_sort(A, size);
	/*if (size <= 100)
	{
		for (int i = 0; i < size; i++)
		{
			cout << A[i] << "\t";
		}
		cout << endl;
	}*/
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
