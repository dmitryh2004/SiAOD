#include <iostream>
#include <locale.h>
#include <fstream>
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
	this->matrix = new int64_t* [m];
	for (int i = 0; i < m; i++)
	{
		this->matrix[i] = new int64_t [n];
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

int permutations_size_x = 0;

bool permutate (int* moves, int size)
{
	bool matching = false, cango = true;
	//increment
	while ((!matching) && (cango))
	{
		int i = size-1;
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
		//count 1s and 0s
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

int64_t field::getNumberOfPaths() {
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			if ((i == 0) || (j == 0))
				matrix[i][j] = 1;
			else
				matrix[i][j] = matrix[i-1][j] + matrix[i][j-1];
		}
	}
	return matrix[size_x-1][size_y-1];
}

int64_t field::getNumberOfPathsBrute() {
	int* moves = new int[size_x+size_y-2]; //0 - right, 1 - down
	for (int i = 0; i < size_y - 1; i++)
	{
		moves[i] = 0;
	}
	for (int i = size_y - 1; i < size_x + size_y - 2; i++)
	{
		moves[i] = 1;
	}
	int64_t count = 1;
	permutations_size_x = size_x - 1;
	while (permutate(moves, size_x + size_y - 2))
	{
		count++;
	}
	return count;
}

void field::show() {
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			cout << setw(5) << matrix[i][j] << " | ";
		}
		cout << endl;
	}
}

int main()
{
	field f = field(10, 10);
	int64_t nopD = 0, nopB = 0;
	int timeD = 0, timeB = 0;
	auto start = chrono::steady_clock::now();
	nopD = f.getNumberOfPaths();
	auto end = chrono::steady_clock::now();
	timeD = chrono::duration_cast<chrono::microseconds> (end-start).count();
	start = chrono::steady_clock::now();
	nopB = f.getNumberOfPathsBrute();
	end = chrono::steady_clock::now();
	timeB = chrono::duration_cast<chrono::microseconds> (end-start).count();
	
	cout << "dynamic programming: " << nopD << endl << "brute force: " << nopB << endl;
	cout << "Time: " << endl;
	cout << "dynamic: " << timeD << ", brute force: " << timeB << endl;
	f.show();
	return 0;	
}