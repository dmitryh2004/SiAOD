#pragma once
#ifndef __list2way_h__
#define __list2way_h__
#include <iostream>

using std::cout; using std::endl;
struct list_chain_2way
{
	int number = 0;
	int score = 0;
	int group = 0;
	list_chain_2way* prev = nullptr;
	list_chain_2way* next = nullptr;

	void show();
};

struct list_2way
{
private:
	list_chain_2way* first;
	list_chain_2way* last;
	int length = 0;
public:
	list_2way();

	~list_2way();

	list_chain_2way* operator [] (int index);

	bool empty();

	void append_to_begin(int number, int group, int score);

	void append_to_end(int number, int group, int score);

	void append_before(int index, int number, int group, int score);
	void append_after(int index, int number, int group, int score);

	void delete_last();
	void delete_element(int index);

	void show();
	void show_reversed();

	bool is_in(int number);

	list_chain_2way* get_element(int number);
	list_chain_2way* get_element_by_index(int index);

	list_chain_2way* get_first();
	list_chain_2way* get_last();
	int size();
};
#endif
