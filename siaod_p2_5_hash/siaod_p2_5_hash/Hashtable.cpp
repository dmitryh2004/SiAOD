#include "Hashtable.h"

int table_size = 1000;
const int TABLE_STEP = 3;
string path;
bool errors = false;

int Hashtable::getHash(record* data)
{
	unsigned int temp = 0;
	for (int i = 0; i < 11; i++)
	{
		temp += pow((abs((int)(data->phone[i])-48)), (i+1));
	}
	return temp % table_size;
}

Hashtable::hashtable_entry::hashtable_entry(int hash) : hash(hash)
{
	for (int i = 0; i < 11; i++)
	{
		this->key[i] = 0;
	}
}

Hashtable::hashtable_entry::~hashtable_entry()
{

}

Hashtable::hashtable::hashtable()
{
	
}

Hashtable::hashtable::hashtable(int size)
{
	for (int i = 0; i < size; i++)
	{
		hashtable_entry* temp = new hashtable_entry(i);
		this->entries.push_back(temp);
	}
}

Hashtable::hashtable::~hashtable()
{
	while (this->entries.size() > 0)
		this->entries.pop_back();
}

float Hashtable::hashtable::getUsage()
{
	return float(this->used_entries) / table_size;
}

void Hashtable::hashtable::extend_table() {
	int current_size = table_size;
	while (this->getUsage() >= 0.75) table_size *= 2;
	for (int i = current_size; i < table_size; i++)
	{
		hashtable_entry* temp = new hashtable_entry(i);
		this->entries.push_back(temp);
	}
	this->rehash(false, -1);
}

void Hashtable::hashtable::rehash(bool mode, int pos)
{
	this->used_entries = 0;
	fstream datafile = fstream(path, ios::in | ios::binary);
	if (datafile)
	{
		record temp;
		int current_record = 0;
		vector<int> records;
		for (int i = 0; i < table_size; i++)
		{
			int rn = this->entries.at(i)->record_number;
			if (rn != -1)
			{
				if (mode)
				{
					if (rn == pos) {}
					else if (rn > pos)
						records.push_back(rn-1);
					else
						records.push_back(rn);
				}
				else
					records.push_back(rn);
				this->entries.at(i)->record_number = -1;
				this->entries.at(i)->open = true;
				this->entries.at(i)->wasCollision = false;
				strcpy_s(this->entries.at(i)->key, "");
			}
		}
		sort(records.begin(), records.end());
		while (!datafile.eof())
		{
			if (current_record == records.size()) break;
			int start = 0;
			if (current_record) start = records[current_record-1];
			int end = records[current_record];
			for (int i = start; i < end; i++)
				datafile.read((char*)&temp, sizeof(record));
			this->addData(&temp, records[current_record]);
			current_record++;
		}
	}
	else {
		cout << "������ ��� ������ �����." << endl;
		errors = true;
	}
}

bool Hashtable::hashtable::addData(record* data, int record_number)
{
	if (this->findData(data->phone) > 0)
	{
		cout << "������: ��� ������ ��� ���� � �������." << endl;
		return false;
	}
	int hash = getHash(data);
	int c = TABLE_STEP;
	int i = 0;
	if (this->getUsage() >= 0.75) this->extend_table();
	while (this->entries.at(hash + c * i)->open == false)
	{
		this->entries.at(hash + c * i)->wasCollision = true;
		i++;
		if (hash + c * i >= table_size) hash -= table_size;
	}
	this->entries.at(hash + c * i)->record_number = record_number;
	this->entries.at(hash + c * i)->open = false;
	strcpy_s(this->entries.at(hash + c * i)->key, data->phone);
	this->used_entries++;
	return true;
}

bool Hashtable::hashtable::removeData(record* data)
{
	int pos = this->findData(data->phone);
	if (pos < 0)
	{
		cout << "������� � ������ " << data->phone << " �� ������ � ���-�������" << endl;
		return false;
	}
	else
	{
		fstream tempfile("temp.txt", ios::out | ios::binary);
		fstream source(path, ios::in | ios::binary);
		record temp;
		int i = 1;
		while (source.read((char*)&temp, sizeof(record)))
		{
			if (i != pos)
			{
				tempfile.write((char*)&temp, sizeof(record));
			}
			i++;
		}
		source.close();
		tempfile.close();
		tempfile = fstream("temp.txt", ios::in | ios::binary);
		source = fstream(path, ios::out | ios::binary);
		while (tempfile.read((char*)&temp, sizeof(record)))
		{
			source.write((char*)&temp, sizeof(record));
		}
		source.close();
		tempfile.close();
		this->rehash(true, pos);
	}
	return true;
}

int Hashtable::hashtable::findData(char* phone)
{
	record data = record(phone, phone);
	int hash = getHash(&data);
	int iterations = 0;
	while (iterations < 2 * table_size) //��� �������������� ������������
	{
		if (this->entries.at(hash)->open)
		{
			if (this->entries.at(hash)->wasCollision == false)
			{
				return -1;
			}
		}
		else
		{
			if (!strcmp(this->entries.at(hash)->key, data.phone))
			{
				return this->entries.at(hash)->record_number;
			}
		}
		hash += TABLE_STEP;
		if (hash >= table_size) hash -= table_size;
		iterations++;
	}
	cout << "������ ��� ������ � ���-�������." << endl;
	errors = true;
	return -2;
}

void Hashtable::hashtable::show()
{
	for (int i = 0; i < this->entries.size(); i++)
	{
		hashtable_entry* temp = this->entries.at(i);
		cout << "hash: " << temp->hash << ", open: " << temp->open << ", was collision: " << temp->wasCollision << ", record number: " << temp->record_number << ", key: " << temp->key << endl;
	}
}

void Hashtable::hashtable::process()
{
	path = "input.txt";
	fstream input;
	for (int i = 0; i < table_size; i++)
	{
		hashtable_entry* temp = new hashtable_entry(i);
		this->entries.push_back(temp);
	}
	record temp;
	int i = 1;
	input = fstream(path, ios::in | ios::binary);
	while (input.read((char*)&temp, sizeof(record)))
	{
		this->addData(&temp, i);
		i++;
	}
	input.close();
	i = 1;
	auto start = chrono::steady_clock::now();
	auto end_hash = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();
	bool running = true;
	char choose = ' ';
	int record_number, pos;
	char key[11];
	strcpy_s(key, "");
	while (running)
	{
		cout << "�������� ��������:" << endl
			<< "[Q] - �����" << endl
			<< "[A] - �������� ������ � �������" << endl
			<< "[R] - ������� ������ �� ������� � �� �����" << endl
			<< "[F] - ����� ������ � �������" << endl
			<< "[O] - ����� ������ � ������� � ������� �� �� �����" << endl
			<< "[S] - �������� ���-�������" << endl;
		choose = _getch();
		switch (tolower(choose))
		{
		case 'q':
			running = false;
			break;
		case 's':
			cout << "���-������� (������������ �����: " << this->used_entries << "/" << table_size << "):" << endl;
			this->show();
			break;
		case 'a':
			cout << "������� ����� ������ �� �����, ������� ���������� �������� � �������: ";
			if (cin >> record_number)
			{
				input = fstream(path, ios::in | ios::binary);
				i = 1;
				while (input.read((char*)&temp, sizeof(record)))
				{
					if (i == record_number)
						break;
					i++;
				}
				if (i != record_number)
				{
					cout << "������ ��� ������ ������ �" << record_number << endl;
				}
				else
				{
					this->addData(&temp, record_number);
				}
				input.close();
			}
			else
			{
				cout << "������ ��� ����� ��������." << endl;
			}
			break;
		case 'r':
			cout << "������� ����� ��������, ������ � ������� ����� �������: ";
			cin >> key;
			if (this->removeData(&record(key, key)))
			{
				cout << "������ � ������ " << key << " ������� �������." << endl;
			}
			else
			{
				cout << "������ ��� �������� ������ � ������ " << key << endl;
			}
			break;
		case 'f':
			cout << "������� ����� ��������, ������ � ������� ����� �����: ";
			cin >> key;
			pos = this->findData(key);
			if (pos > 0)
			{
				cout << "������ � ������ " << key << " ������� �� ������� " << pos << endl;
			}
			else
			{
				cout << "������ � ������ " << key << " �� �������" << endl;
			}
			break;
		case 'o':
			cout << "������� ����� ��������, ������ � ������� ����� �����: ";
			cin >> key;
			start = chrono::steady_clock::now();
			pos = this->findData(key);
			end = chrono::steady_clock::now();
			if (pos > 0)
			{
				cout << "������ � ������ " << key << " ������� �� ������� " << pos << endl;
				input = fstream(path, ios::in | ios::binary);
				i = 1;
				while (input.read((char*)&temp, sizeof(record)))
				{
					if (i == pos)
						break;
					i++;
				}
			}
			else
			{
				cout << "������ � ������ " << key << " �� �������" << endl;
			}
			if (pos > 0)
			{
				cout << "��������� ������: " << temp.phone << "; " << temp.address << endl;
			}
			cout << "����� ������ � ���-�������: " << chrono::duration_cast<chrono::microseconds> (end - start).count() << " ���" << endl;
			break;
		default:
			cout << "����������� ��������." << endl;
		}
		if (errors)
		{
			cout << "���� ���������� ������, ������� ����� ������ �� ������ ���������. ������� ���������." << endl;
			running = false;
		}
		if (running)
		{
			system("pause");
			system("cls");
		}
	}
}