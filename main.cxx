#include <iostream>
#include <locale.h>
#include <iomanip>
#include <chrono>

using namespace std;

class field {
	int size_x, size_y;
	int64_t** matrix;
public:
	field(int m, int n);
	~field();
	void show();
	int64_t getNumberOfPaths();
	int64_t getNumberOfPathsBrute();
};

field::field(int m, int n)
{
	this->size_x = m;
	this->size_y = n;
	this->matrix = new int64_t*[m];
	for (int i = 0; i < m; i++)
	{
		this->matrix[i] = new int64_t[n];
		for (int j = 0; j < n; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
}

field::~field() {
	for (int i = 0; i < size_x; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

int permutations_size_x = 0; //сколько нужно ходов вниз

bool permutate(int* moves, int size)
{
	bool matching = false, cango = true;
	//идем к следующему варианту
	while ((!matching) && (cango))
	{
		int i = size - 1;
		while (i >= 0)
		{
			if (moves[i] == 0)
			{
				moves[i] = 1;
				break;
			}
			else
			{
				moves[i] = 0;
				i--;
				if (i == -1)
				{
					cango = false;
					break;
				}
			}
		}
		//считаем единицы и ноли
		int onecount = 0, zerocount = 0;
		for (i = 0; i < size; i++)
		{
			(moves[i] == 1) ? onecount++ : zerocount++;
		}
		if (onecount == permutations_size_x)
		{
			matching = true;
		}
	}
	return matching;
}

int64_t field::getNumberOfPathsBrute() {
	if ((size_x == 1) || (size_y == 1))
		return 1;
	int* moves = new int[size_x + size_y - 2]; //0 - вправо, 1 - вниз
	for (int i = 0; i < size_y - 1; i++)
	{
		moves[i] = 0;
	}
	for (int i = size_y - 1; i < size_x + size_y - 2; i++)
	{
		moves[i] = 1;
	}
	int64_t count = 1;
	permutations_size_x = size_x - 1; //задаем необходимое количество ходов вниз для метода
	while (permutate(moves, size_x + size_y - 2))
	{
		count++;
	}
	return count;
}

int64_t field::getNumberOfPaths() {
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			if ((i == 0) || (j == 0))
				matrix[i][j] = 1;
			else
				matrix[i][j] = matrix[i - 1][j] + matrix[i][j - 1];
		}
	}
	return matrix[size_x - 1][size_y - 1];
}

void field::show() {
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			cout << setw(6) << matrix[i][j] << " | ";
		}
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	int x = 15, y = 15; //высота и ширина
	field f = field(x, y);
	int64_t nopD = 0, nopB = 0;
	int timeD = 0, timeB = 0;

	auto start = chrono::steady_clock::now();
	nopD = f.getNumberOfPaths();
	auto end = chrono::steady_clock::now();

	timeD = chrono::duration_cast<chrono::nanoseconds> (end - start).count();

	start = chrono::steady_clock::now();
	nopB = f.getNumberOfPathsBrute();
	end = chrono::steady_clock::now();

	timeB = chrono::duration_cast<chrono::microseconds> (end - start).count();

	cout << "Размеры поля: " << y << " x " << x << endl;
	cout << "=========================================================" << endl;
	cout << "РЕЗУЛЬТАТЫ" << endl;
	cout << "Метод \"грубой силы\": " << nopB << endl;
	cout << "Метод динамического программирования: " << nopD << endl;
	cout << "=========================================================" << endl;
	cout << "ВРЕМЯ ВЫПОЛНЕНИЯ" << endl;
	if (timeB > 1000000)
	{
		cout << "Метод \"грубой силы\": " << timeB / 1000000 << " с " << (timeB % 1000000) / 1000 << " мс" << endl;
	}
	else if (timeB > 1000)
	{
		cout << "Метод \"грубой силы\": " << timeB / 1000 << " мс" << endl;
	}
	else {
		cout << "Метод \"грубой силы\": " << timeB << " мкс" << endl;
	}
	cout << "Метод динамического программирования: " << timeD << " нс" << endl;
	cout << "=========================================================" << endl;
	f.show();
	return 0;
}
