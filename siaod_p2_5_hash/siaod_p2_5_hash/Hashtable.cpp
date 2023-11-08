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
		cout << "Ошибка при чтении файла." << endl;
		errors = true;
	}
}

bool Hashtable::hashtable::addData(record* data, int record_number)
{
	if (this->findData(data->phone) > 0)
	{
		cout << "Ошибка: эта запись уже есть в таблице." << endl;
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
		cout << "Элемент с ключом " << data->phone << " не найден в хэш-таблице" << endl;
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
	while (iterations < 2 * table_size) //для предотвращения зацикливания
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
	cout << "Ошибка при поиске в хэш-таблице." << endl;
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
		cout << "Выберите действие:" << endl
			<< "[Q] - выход" << endl
			<< "[A] - добавить запись в таблицу" << endl
			<< "[R] - удалить запись из таблицы и из файла" << endl
			<< "[F] - найти запись в таблице" << endl
			<< "[O] - найти запись в таблице и вывести ее на экран" << endl
			<< "[S] - показать хэш-таблицу" << endl;
		choose = _getch();
		switch (tolower(choose))
		{
		case 'q':
			running = false;
			break;
		case 's':
			cout << "Хэш-таблица (использовано полей: " << this->used_entries << "/" << table_size << "):" << endl;
			this->show();
			break;
		case 'a':
			cout << "Введите номер записи из файла, который необходимо вставить в таблицу: ";
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
					cout << "Ошибка при чтении записи №" << record_number << endl;
				}
				else
				{
					this->addData(&temp, record_number);
				}
				input.close();
			}
			else
			{
				cout << "Ошибка при вводе значения." << endl;
			}
			break;
		case 'r':
			cout << "Введите номер телефона, запись с которым нужно удалить: ";
			cin >> key;
			if (this->removeData(&record(key, key)))
			{
				cout << "Запись с ключом " << key << " удалена успешно." << endl;
			}
			else
			{
				cout << "Ошибка при удалении записи с ключом " << key << endl;
			}
			break;
		case 'f':
			cout << "Введите номер телефона, запись с которым нужно найти: ";
			cin >> key;
			pos = this->findData(key);
			if (pos > 0)
			{
				cout << "Запись с ключом " << key << " найдена на позиции " << pos << endl;
			}
			else
			{
				cout << "Запись с ключом " << key << " не найдена" << endl;
			}
			break;
		case 'o':
			cout << "Введите номер телефона, запись с которым нужно найти: ";
			cin >> key;
			start = chrono::steady_clock::now();
			pos = this->findData(key);
			end = chrono::steady_clock::now();
			if (pos > 0)
			{
				cout << "Запись с ключом " << key << " найдена на позиции " << pos << endl;
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
				cout << "Запись с ключом " << key << " не найдена" << endl;
			}
			if (pos > 0)
			{
				cout << "Найденная запись: " << temp.phone << "; " << temp.address << endl;
			}
			cout << "Время поиска в хэш-таблице: " << chrono::duration_cast<chrono::microseconds> (end - start).count() << " мкс" << endl;
			break;
		default:
			cout << "Неизвестное действие." << endl;
		}
		if (errors)
		{
			cout << "Были обнаружены ошибки, которые могут влиять на работу программы. Процесс прекращен." << endl;
			running = false;
		}
		if (running)
		{
			system("pause");
			system("cls");
		}
	}
}