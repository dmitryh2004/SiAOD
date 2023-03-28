#include "list_2way.h"


void list_chain_2way::show()
{
	cout << "[ Номер зачетки: " << this->number << " Группа: " << this->group << " Оценка: " << this->score << "]" << endl;
}

list_2way::list_2way()
{
	first = nullptr;
	last = nullptr;
}

list_2way::~list_2way()
{
	while (!empty())
		delete_last();
}

list_chain_2way* list_2way::operator [] (int index)
{
	if (empty()) return nullptr;
	list_chain_2way* cur = first;
	for (int i = 0; i < index; i++)
	{
		cur = cur->next;
		if (!cur)
			return nullptr;
	}
	return cur;
}

bool list_2way::empty()
{
	return (last == nullptr);
}

void list_2way::append_to_begin(int number, int group, int score)
{
	list_chain_2way* temp = new list_chain_2way;
	temp->number = number;
	temp->group = group;
	temp->score = score;
	length++;
	if (empty())
	{
		first = temp;
		last = temp;
		return;
	}
	temp->next = first;
	first->prev = temp;
	first = temp;

}

void list_2way::append_to_end(int number, int group, int score)
{
	list_chain_2way* temp = new list_chain_2way;
	temp->number = number;
	temp->group = group;
	temp->score = score;
	length++;
	if (empty())
	{
		first = temp;
		last = temp;
		return;
	}
	temp->prev = last;
	last->next = temp;
	last = temp;

}

void list_2way::append_before(int index, int number, int group, int score)
{
	if (empty()) return;
	if (index == 0) append_to_begin(number, group, score);
	else {
		list_chain_2way* temp = this->get_element_by_index(index);
		list_chain_2way* temp2 = new list_chain_2way;
		temp2->number = number;
		temp2->group = group;
		temp2->score = score;
		length++;
		temp2->prev = temp->prev;
		temp->prev->next = temp2;
		temp2->next = temp;
		temp->prev = temp2;
	}
}

void list_2way::append_after(int index, int number, int group, int score)
{
	if (empty()) return;
	if (index == length - 1) append_to_end(number, group, score);
	else {
		list_chain_2way* temp = this->get_element_by_index(index);
		list_chain_2way* temp2 = new list_chain_2way;
		temp2->number = number;
		temp2->group = group;
		temp2->score = score;
		length++;
		temp2->next = temp->next;
		temp->next->prev = temp2;
		temp2->prev = temp;
		temp->next = temp2;
	}
}

void list_2way::delete_last()
{
	if (empty()) return;
	list_chain_2way* temp = last;
	last = temp->prev;
	if (last)
		last->next = nullptr;
	delete temp;
	length--;
}

void list_2way::delete_element(int index)
{
	if (empty()) return;
	if (index >= this->size()) return;
	list_chain_2way* temp = this->get_element_by_index(index);
	list_chain_2way* old_prev = temp->prev; 
	list_chain_2way* old_next = temp->next;
	if ((old_prev == nullptr) && (old_next == nullptr))
	{
		first = nullptr;
		last = nullptr;
	}
	else if (old_prev == nullptr)
	{
		first = old_next;
		old_next->prev = old_prev;
	}
	else if (old_next == nullptr)
	{
		last = old_prev;
		old_prev->next = old_next;
	}
	else
	{
		old_prev->next = old_next;
		old_next->prev = old_prev;
	}
	delete temp;
	length--;
}

void list_2way::show()
{
	if (empty()) { cout << "Список пуст" << endl; return; }
	list_chain_2way* temp = first;
	cout << "[" << endl;
	while (temp != nullptr)
	{
		temp->show();
		temp = temp->next;
	}
	cout << "] (длина: " << length << ")" << endl;
}

void list_2way::show_reversed()
{
	if (empty()) { cout << "Список пуст" << endl; return; }
	list_chain_2way* temp = last;
	cout << "[" << endl;
	while (temp != nullptr)
	{
		temp->show();
		temp = temp->prev;
	}
	cout << "] (длина: " << length << ")" << endl;
}

bool list_2way::is_in(int number)
{
	if (empty()) return false;
	list_chain_2way* temp = first;
	while ((temp != nullptr) && (temp->number != number))
	{
		temp = temp->next;
	}
	if (temp == nullptr)
		return false;
	else
		return true;
}

list_chain_2way* list_2way::get_element(int number)
{
	if (empty()) return nullptr;
	list_chain_2way* temp = first;
	while ((temp != nullptr) && (temp->number != number))
	{
		temp = temp->next;
	}
	if (temp == nullptr)
		return nullptr;
	else
		return temp;
}

list_chain_2way* list_2way::get_element_by_index(int index)
{
	if (empty()) return nullptr;
	list_chain_2way* temp = first;
	int i = 0;
	while ((temp != nullptr) && (i < index))
	{
		temp = temp->next;
		i++;
	}
	if (temp == nullptr)
		return nullptr;
	else
		return temp;
}

list_chain_2way* list_2way::get_first()
{
	return this->first;
}

list_chain_2way* list_2way::get_last()
{
	return this->last;
}

int list_2way::size()
{
	return this->length;
}
