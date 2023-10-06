// siaod_p2_3_FileConverter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct record {
	char phone[11];
	char address[100];
};


int main()
{
	fstream input, output;
	string input_path;
	cin >> input_path;
	input = fstream(input_path, ios::in);
	output = fstream(input_path + "_bin.txt", ios::out | ios::binary);
	record temp;
	while (!input.eof())
	{
		string temps;
		getline(input, temps);
		strcpy_s(temp.phone, temps.c_str());
		getline(input, temps);
		strcpy_s(temp.address, temps.c_str());
		output.write((char*)&temp, sizeof(record));
	}
	input.close();
	output.close();
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
