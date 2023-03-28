// SiAOD 7B.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale.h>
#include <conio.h>
#include "consolecolors.h"
#include "list_2way.h"

using std::cout;
using std::cin;
using std::endl;

///////////////////////////////////////////////////////
// Additional functions
///////////////////////////////////////////////////////
void append_new(list_2way& list, int number, int group, int score) //сложность O(n), n - число элементов в списке
{
	bool found = false;
	int index = 0;
	int first_greater = -1;
	for (index = 0; index < list.size(); index++)
	{
		if (list[index]->number > number)
		{
			found = true;
			first_greater = (first_greater == -1) ? index : first_greater;
		}
		if (list[index]->number == number)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		if (first_greater == -1)
		{
			list.append_before(index, number, group, score);
		}
		else
		{
			list.append_before(first_greater, number, group, score);
		}
	}
	else
	{
		SetColor(0, 12);
		cout << "Невозможно выполнить операцию" << endl;
		SetColor(0, 15);
	}
}

void delete_group(list_2way& list, int group)
{
	int i = 0;
	while (i < list.size())
	{
		if (list[i]->group == group)
		{
			list.delete_element(i);
		}
		else
		{
			i++;
		}
	}
	SetColor(0, 14);
	cout << "Удалены все записи с группой " << group << endl;
	SetColor(0, 15);
}

list_2way* make_otchislenie_list(list_2way& list)
{
	list_2way* newlist = new list_2way();
	int index = 0;
	while (index < list.size())
	{
		if (list[index]->score == 2)
		{
			newlist->append_to_end(list[index]->number, list[index]->group, list[index]->score);
			list.delete_element(index);
		}
		else
		{
			index++;
		}
	}
	return newlist;
}

void otchislenie(list_2way& list)
{
	list_2way* otch = make_otchislenie_list(list);
	cout << "Список отчисленных: ";
	otch->show();
	cout << "Оставшиеся студенты: ";
	list.show();
	delete otch;
}

void demonstrate()
{
	list_2way A;
	A.append_to_end(1, 1, 5);
	A.append_to_end(2, 1, 2);
	A.append_to_end(3, 1, 4);
	A.append_to_end(4, 1, 3);
	A.append_to_end(5, 1, 4);
	A.append_to_end(6, 1, 2);
	A.append_to_end(7, 1, 3);
	A.append_to_end(8, 1, 2);
	A.append_to_end(11, 1, 3);
	SetColor(0, 13);
	cout << "Демонстрация" << endl;
	SetColor(0, 15);
	cout << "Список A: ";
	A.show();
	append_new(A, 9, 2, 4);
	cout << "Список A после добавления элемента (9, 2, 4): ";
	A.show();
	cout << "Вывод в обратном порядке: ";
	A.show_reversed();
	cout << "А теперь отчислим студентов с неудом: ";
	otchislenie(A);
}

int main()
{
	SetColor(0, 15);
	setlocale(LC_ALL, "ru");
	list_2way students;
	bool a = true;
	char choice = 0, choice2;
	int n = 0, g = 0, s = 1;
	while (a)
	{
		if (choice != 0) system("pause");
		system("cls");
		s = 1;
		cout << "Выберите действие, нажав на клавишу (клавиши): " << endl;
		cout << "[Q] - выход" << endl;
		cout << "[S] - вывести список студентов" << endl;
		cout << "[R] - вывести список студентов в обратном направлении" << endl;
		cout << "[F] - найти узел с заданным значением" << endl;
		cout << "[A] - добавить новый элемент в список" << endl;
		cout << "--- [B] - в начало" << endl;
		cout << "--- [E] - в конец" << endl;
		cout << "--- [F] - перед первым элементом с таким же номером зачетки" << endl;
		cout << "[G] - удалить все элементы с заданным номером группы" << endl;
		cout << "[O] - сформировать список студентов с оценками \"неуд\" (2) и исключить их из основного списка" << endl;
		cout << "[D] - демонстрация всех операций" << endl;
		choice = _getch();
		switch (choice)
		{
		case 'q':
		case 'Q':
			a = false;
			break;
		case 's':
		case 'S':
			students.show();
			break;
		case 'r':
		case 'R':
			students.show_reversed();
			break;
		case 'f':
		case 'F':
			cout << "Введите номер зачетки для поиска -> ";
			while (!(cin >> n))
			{
				cout << "Неверный ввод" << endl;
				cout << "Повторите ввод номера зачетки -> ";
			}
			if (students.get_element(n))
			{
				cout << "Элемент найден" << endl; students.get_element(n)->show();
			}
			else
			{
				cout << "Ни один элемент с таким номером зачетки не найден" << endl;
			}
			break;
		case 'a':
		case 'A':
			system("cls");
			cout << "Выберите действие, нажав на клавишу (клавиши): добавить новый элемент..." << endl;
			cout << "--- [B] - в начало" << endl;
			cout << "--- [E] - в конец" << endl;
			cout << "--- [F] - перед первым элементом с таким же номером зачетки" << endl;
			choice2 = _getch();
			if ((tolower(choice2) != 'b') && (tolower(choice2) != 'e') && (tolower(choice2) != 'f'))
			{
				cout << "Неверный ввод" << endl;
				break;
			}
			
			cout << "Введите номер зачетки, номер группы и оценку от 2 до 5: " << endl;
			cout << "Номер зачетки -> ";
			while (!(cin >> n))
			{
				cout << "Неверный ввод" << endl;
				cout << "Повторите ввод номера зачетки -> ";
			}
			cout << "Номер группы -> ";
			while (!(cin >> g))
			{
				cout << "Неверный ввод" << endl;
				cout << "Повторите ввод номера группы -> ";
			}
			cout << "Оценка от 2 до 5 -> ";
			while ((!(cin >> s)) || (s < 2) || (s > 5))
			{
				cout << "Неверный ввод" << endl;
				cout << "Повторите ввод оценки -> ";
			}
			switch(choice2)
			{
		case 'b':
		case 'B':
			students.append_to_begin(n, g, s);
			break;
		case 'E':
		case 'e':
			students.append_to_end(n, g, s);
			break;
		case 'f':
		case 'F':
			append_new(students, n, g, s);
			break;
			}
			break;
		case 'g':
		case 'G':
			cout << "Введите номер группы для удаления -> ";
			while (!(cin >> g))
			{
				cout << "Неверный ввод" << endl;
				cout << "Повторите ввод номера группы -> ";
			}
			delete_group(students, g);
			break;
		case 'o':
		case 'O':
			otchislenie(students);
			break;
		case 'd':
		case 'D':
			demonstrate();
			break;
		default:
			cout << "Действие не найдено" << endl;
		}
	}
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
