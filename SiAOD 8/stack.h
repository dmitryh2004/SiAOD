#pragma once
#ifndef __stack_h__
#define __stack_h__
#include <iostream>
#include <locale.h>
#include <string>

using namespace std;

enum types { number = 0, ch = 1 };

struct stack1 {
	types type;
	int data1;
	char data2;
	stack1* next;
	void show()
	{
		if (type == number) cout << data1 << " ";
		else cout << data2 << " ";
	}
};

struct stack {
	int size;
	stack1* top;

	bool empty()
	{
		return (top == nullptr);
	}

	void push_n(int n)
	{
		stack1* temp = new stack1;
		temp->type = types::number;
		temp->data1 = n;
		temp->data2 = 0;
		temp->next = top;
		top = temp;
		size++;
	}

	void push_ch(char ch)
	{
		stack1* temp = new stack1;
		temp->type = types::ch;
		temp->data1 = 0;
		temp->data2 = ch;
		temp->next = top;
		top = temp;
		size++;
	}

	void push(types type, int d1, char d2)
	{
		switch (type)
		{
		case 0:
			push_n(d1);
			break;
		case 1:
			push_ch(d2);
			break;
		default:
			cout << "Невозможно добавить элемент в стек" << endl;
		}
	}

	void pop()
	{
		if (empty()) return;
		stack1* temp = this->top;
		top = temp->next;
		delete[] temp;
		size--;
	}

	void show()
	{
		stack1* cur = top;
		while (cur != nullptr)
		{
			cur->show();
			cur = cur->next;
		}
		cout << "(длина: " << size << ")" << endl;
	}

	stack1* get_top()
	{
		return top;
	}

	stack()
	{
		size = 0;
		top = nullptr;
	}

	~stack()
	{
		while (!empty())
			pop();
	}
};
#endif