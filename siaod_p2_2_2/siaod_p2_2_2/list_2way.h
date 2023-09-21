#pragma once
#ifndef __list2way_h__
#define __list2way_h__
#include <iostream>
#include <string>
using namespace std;

struct record {
	int oms_code; //ключ
	char surname[20]; //фамилия
	char name[20]; //имя
	char patronymic[20]; //отчество
	char disease_code[5]; //код болезни
	char date[8]; //дата ДД.ММ.ГГ
	int doctor_id; //ид врача

	record()
	{
		oms_code = -1;
		strcpy_s(this->surname, "generic");
		strcpy_s(this->name, "generic");
		strcpy_s(this->patronymic, "generic");
		strcpy_s(this->disease_code, "XXXXX");
		strcpy_s(this->date, "--.--.--");
		doctor_id = -1;
	}

	record(int oms_code, char* surname, char* name, char* patr, char* disease_code, char* date, int doctor_id) :
		oms_code(oms_code), doctor_id(doctor_id)
	{
		strcpy_s(this->surname, surname);
		strcpy_s(this->name, name);
		strcpy_s(this->patronymic, patronymic);
		strcpy_s(this->disease_code, disease_code);
		strcpy_s(this->date, date);
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
	void clear();

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
