// siaod_p2_5_bin_tree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <chrono>
#include "BinTree.h"
#include "BinFileReader.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	BinFileEditor::init("input.txt");
	record temp;
	BinFileEditor::readNext(temp);
	BinTree tree = BinTree(stoull(string(temp.phone)), 1);
	int i = 2;
	while (BinFileEditor::readNext(temp))
	{
		if (strcmp(temp.phone, ""))
			tree.addElement(stoull(string(temp.phone)), i++);
	}
	bool running = true;
	char choose = ' ';
	int recordIndex = 0;
	int64_t key = 0;
	int pos;
	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();
	while (running) {
		cout << "Выберите действие: \n"
			<< "[S] - показать бинарное дерево\n"
			<< "[A] - добавить запись в дерево\n"
			<< "[R] - удалить запись из дерева\n"
			<< "[F] - найти запись по ключу с помощью дерева\n"
			<< "[O] - найти запись по ключу с помощью дерева и вывести ее на экран\n"
			<< "[Q] - выйти\n";
		choose = _getch();
		switch (tolower(choose)) {
		case 'q':
			running = false;
			break;
		case 's':
			cout << "Бинарное дерево поиска:\n";
			tree.showTree();
			break;
		case 'a':
			cout << "Введите номер записи из файла, которую нужно добавить в дерево: ";
			cin >> recordIndex;
			if (BinFileEditor::readByIndex(recordIndex, temp))
			{
				tree.addElement(stoull(string(temp.phone)), recordIndex);
			}
			else {
				cout << "Записи с номером " << recordIndex << " не существует в файле.\n";
			}
			break;
		case 'r':
			cout << "Введите номер телефона, запись с которым нужно удалить из дерева: ";
			cin >> key;
			tree.removeElement(key);
			break;
		case 'f':
			cout << "Введите искомый номер телефона: ";
			cin >> key;
			pos = tree.findElement(key);
			if (pos > 0)
			{
				cout << "Искомый номер телефона найден в записи с номером " << pos << "\n";
			}
			else
			{
				cout << "Искомый номер телефона не найден\n";
			}
			break;
		case 'o':
			cout << "Введите искомый номер телефона: ";
			cin >> key;
			start = chrono::steady_clock::now();
			pos = tree.findElement(key);
			end = chrono::steady_clock::now();
			if (pos > 0)
			{
				cout << "Искомый номер телефона найден в записи с номером " << pos << "\n";
				BinFileEditor::readByIndex(pos, temp);
				cout << "Номер телефона: " << temp.phone << "\nАдрес: " << temp.address << "\n";
				cout << "Время поиска записи: " << chrono::duration_cast<chrono::microseconds> (end - start).count() << " мкс\n";
			}
			else
			{
				cout << "Искомый номер телефона не найден\n";
				cout << "Время поиска записи: " << chrono::duration_cast<chrono::microseconds> (end - start).count() << " мкс\n";
			}
			break;
		default:
			cout << "Неизвестное действие.\n";
		}
		if (running) {
			system("pause");
			system("cls");
		}
	}
	return 0;
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
