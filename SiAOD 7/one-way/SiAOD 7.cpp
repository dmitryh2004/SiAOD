// SiAOD 7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale.h>

using std::cout; 
using std::endl;

struct list_chain
{
	int data = 0;
	list_chain* next = nullptr;
};

struct list
{
	list_chain* first;
	list_chain* last;
	int length = 0;

	list()
	{
		first = nullptr;
		last = nullptr;
	}

	~list()
	{
		while (!empty())
			delete_first();
	}

	list_chain* operator [] (int index)
	{
		if (empty()) return nullptr;
		list_chain* cur = first;
		for (int i = 0; i < index; i++)
		{
			cur = cur->next;
			if (!cur)
				return nullptr;
		}
		return cur;
	}

	bool empty()
	{
		return (first == nullptr);
	}

	void append_to_begin(int data)
	{
		list_chain* temp = new list_chain;
		temp->data = data;
		length++;
		if (empty())
		{
			first = temp;
			last = temp;
			return;
		}
		temp->next = first;
		first = temp;
		
	}

	void delete_first()
	{
		if (empty()) return;
		list_chain* temp = first;
		first = temp->next;
		delete temp;
		length--;
	}

	void show()
	{
		if (empty()) return;
		list_chain* temp = first;
		cout << "[";
		while (temp != nullptr)
		{
			cout << temp->data;
			if (temp->next != nullptr)
				cout << " ";
			temp = temp->next;
		}
		cout << "] (длина: " << length << ")" << endl;
	}

	bool is_in(int what)
	{
		if (empty()) return false;
		list_chain* temp = first;
		while ((temp != nullptr) && (temp->data != what))
		{
			temp = temp->next;
		}
		if (temp == nullptr)
			return false;
		else
			return true;
	}

	list_chain* get_element(int what)
	{
		if (empty()) return nullptr;
		list_chain* temp = first;
		while ((temp != nullptr) && (temp->data != what))
		{
			temp = temp->next;
		}
		if (temp == nullptr)
			return nullptr;
		else
			return temp;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	list A, B, C;
	A.append_to_begin(1);
	A.append_to_begin(2);
	A.append_to_begin(3);
	A.append_to_begin(4);
	A.append_to_begin(6);
	A.append_to_begin(8);
	B.append_to_begin(4);
	B.append_to_begin(6);
	B.append_to_begin(8);
	B.append_to_begin(10);
	B.append_to_begin(12);

	cout << "Список A: ";
	A.show();
	cout << "Список B: ";
	B.show();
	for (int i = 0; i < A.length; i++)
	{
		int data = A[i]->data;
		if ((B.is_in(data))&&!(C.is_in(data)))
		{
			C.append_to_begin(data);
		}
	}
	for (int i = 0; i < B.length; i++)
	{
		int data = B[i]->data;
		if ((A.is_in(data)) && !(C.is_in(data)))
		{
			C.append_to_begin(data);
		}
	}
	cout << "Пересечение А и В: ";
	C.show();
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
