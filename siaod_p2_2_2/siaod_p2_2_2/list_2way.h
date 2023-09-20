#pragma once
#ifndef __list2way_h__
#define __list2way_h__
#include <iostream>
#include <string>
using namespace std;

struct record {
	int oms_code; //ключ
	string surname; //фамилия
	string name; //имя
	string patronymic; //отчество
	string disease_code; //код болезни
	string date; //дата ДД.ММ.ГГ
	int doctor_id; //ид врача

	record()
	{

	}

	record(int oms_code, string surname, string name, string patr, string disease_code, string date, int doctor_id) :
		oms_code(oms_code), surname(surname), name(name), patronymic(patr), disease_code(disease_code), date(date), doctor_id(doctor_id)
	{

	}

	bool operator == (record right)
	{
		if (this->oms_code != right.oms_code) return false;
		if (this->surname != right.surname) return false;
		if (this->name != right.name) return false;
		if (this->patronymic != right.patronymic) return false;
		if (this->disease_code != right.disease_code) return false;
		if (this->date != right.date) return false;
		if (this->doctor_id != right.doctor_id) return false;
		return true;
	}

	bool operator != (record right)
	{
		return !(*this == right);
	}
};

using std::cout; using std::endl;
struct list_chain_2way
{
	void show();

	record data;
	list_chain_2way* prev = nullptr;
	list_chain_2way* next = nullptr;
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

	void append_to_begin(record new_record);

	void append_to_end(record new_record);

	void append_before(int index, record new_record);
	void append_after(int index, record new_record);

	void delete_last();
	void delete_element(int index);

	void show();
	void show_reversed();

	bool is_in(record data);

	list_chain_2way* get_element(record data);
	list_chain_2way* get_element_by_index(int index);

	list_chain_2way* get_first();
	list_chain_2way* get_last();
	int size();
};
#endif
