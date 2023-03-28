#pragma once
#ifndef __postarithm__
#define __postarithm__
#include <iostream>
#include <locale.h>
#include <string>
#include "stack.h"

stack calc_stack;

void reset()
{
	while (!calc_stack.empty())
		calc_stack.pop();
}

bool stack_add()
{
	if (calc_stack.size < 3)
	{
		cout << "Ошибка при вычислении: не хватает аргументов" << endl;
		cout << "Текущее состояние стека: ";
		calc_stack.show();
		cout << endl;
		return false;
	}
	int arg1, arg2;
	calc_stack.pop();
	arg2 = calc_stack.get_top()->data1;
	calc_stack.pop();
	arg1 = calc_stack.get_top()->data1;
	calc_stack.pop();
	calc_stack.push(number, arg1 + arg2, 0);
	return true;
}
bool stack_substract()
{
	if (calc_stack.size < 3)
	{
		cout << "Ошибка при вычислении: не хватает аргументов" << endl;
		cout << "Текущее состояние стека: ";
		calc_stack.show();
		cout << endl;
		return false;
	}
	int arg1, arg2;
	calc_stack.pop();
	arg2 = calc_stack.get_top()->data1;
	calc_stack.pop();
	arg1 = calc_stack.get_top()->data1;
	calc_stack.pop();
	calc_stack.push(number, arg1 - arg2, 0);
	return true;
}
bool stack_multiply()
{
	if (calc_stack.size < 3)
	{
		cout << "Ошибка при вычислении: не хватает аргументов" << endl;
		cout << "Текущее состояние стека: ";
		calc_stack.show();
		cout << endl;
		return false;
	}
	int arg1, arg2;
	calc_stack.pop();
	arg2 = calc_stack.get_top()->data1;
	calc_stack.pop();
	arg1 = calc_stack.get_top()->data1;
	calc_stack.pop();
	calc_stack.push(number, arg1 * arg2, 0);
	return true;
}
bool stack_divide()
{
	if (calc_stack.size < 3)
	{
		cout << "Ошибка при вычислении: не хватает аргументов" << endl;
		cout << "Текущее состояние стека: ";
		calc_stack.show();
		cout << endl;
		return false;
	}
	int arg1, arg2;
	calc_stack.pop();
	arg2 = calc_stack.get_top()->data1;
	calc_stack.pop();
	arg1 = calc_stack.get_top()->data1;
	calc_stack.pop();
	if (arg2 == 0)
	{
		cout << "Ошибка: деление на 0" << endl;
		return false;
	}
	calc_stack.push(number, arg1 / arg2, 0);
	return true;
}

void make_calcs(string input)
{
	string remaining = input;
	string temp = "";
	string temp2 = "";
	bool error = false;
	while (remaining.size() > 0)
	{
		temp = "";
		temp2 = "";
		int index = 0;
		for (int i = 0; (i < remaining.size() && remaining[i] != ' '); i++, index++)
		{
			temp += remaining[i];
		}
		temp2 = remaining;
		remaining = "";
		for (int i = index + 1; i < temp2.size(); i++)
		{
			remaining += temp2[i];
		}
		
		if (temp == "+")
		{
			calc_stack.push(ch, 0, temp[0]);
			if (!stack_add()) { error = true; break; }
		}
		else if (temp == "-")
		{
			calc_stack.push(ch, 0, temp[0]);
			if (!stack_substract()) { error = true; break; }
		}
		else if (temp == "*")
		{
			calc_stack.push(ch, 0, temp[0]);
			if (!stack_multiply()) { error = true; break; }
		}
		else if (temp == "/")
		{
			calc_stack.push(ch, 0, temp[0]);
			if (!stack_divide()) { error = true; break; }
		}
		else {
			int t = strtol(temp.c_str(), nullptr, 0);
			calc_stack.push(number, t, 0);
		}
	}
	if (calc_stack.size > 1)
	{
		cout << "Допущена ошибка в записи постфиксной формы" << endl;
	}
	else {
		if (!error)
		{
			cout << "Ответ: " << calc_stack.get_top()->data1 << endl;
		}
	}
	reset();
}
#endif