﻿// siaod_p2_1_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <bitset>
#include <locale.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	cout << "Упражнение 1" << endl;
	unsigned long x = 0x89ABCDEF;
	unsigned long mask = 0;
	mask = (1 << 5) | (1 << 7) | (1 << 13);
	cout << "Значение х до применения маски: " << x << ", в двоичном виде: " << bitset<sizeof(x)*8>(x) << endl;
	cout << "Значение х после применения маски: " << (x | mask) << ", в двоичном виде: " << bitset<sizeof(x)*8>(x|mask) << endl;
	system("pause");
	system("cls");
	cout << "Упражнение 2" << endl;
	cout << "Введите х: ";
	cin >> x;
	mask = (~0);
	mask = mask >> 4;
	cout << "Значение х до применения маски: " << x << ", в двоичном виде: " << bitset<sizeof(x) * 8>(x) << endl;
	cout << "Значение х после применения маски: " << (x & mask) << ", в двоичном виде: " << bitset<sizeof(x) * 8>(x & mask) << endl;
	system("pause");
	system("cls");
	cout << "Упражнение 3" << endl;
	cout << "Введите х: ";
	cin >> x;
	cout << "Значение х до применения операции: " << x << ", в двоичном виде: " << bitset<sizeof(x) * 8>(x) << endl;
	x = x << 9;
	cout << "Значение х после применения операции: " << x << ", в двоичном виде: " << bitset<sizeof(x) * 8>(x) << endl;
	system("pause");
	system("cls");
	cout << "Упражнение 4" << endl;
	cout << "Введите х: ";
	cin >> x;
	cout << "Значение х до применения операции: " << x << ", в двоичном виде: " << bitset<sizeof(x) * 8>(x) << endl;
	x = x >> 7;
	cout << "Значение х после применения операции: " << x << ", в двоичном виде: " << bitset<sizeof(x) * 8>(x) << endl;
	system("pause");
	system("cls");
	cout << "Упражнение 5" << endl;
	cout << "Введите х: ";
	cin >> x;
	cout << "Введите n (0-31): ";
	int n;
	cin >> n;
	if (n < 0) n = 0;
	if (n > 31) n = 31;
	mask = 0x80000000;
	mask = mask >> (31 - n);
	cout << "Значение х до применения операции: " << x << ", в двоичном виде: " << bitset<sizeof(x) * 8>(x) << endl;
	cout << "Значение х после применения операции: " << (x | mask) << ", в двоичном виде: " << bitset<sizeof(x) * 8>(x | mask) << endl;
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
