#include "list_2way.h"
#include "BinFileEditor.h"

list_2way entries;
string _path;

bool BinFileEditor::init()
{
	char filetype = ' ';
	cout << "Выберите тип файла, который необходимо прочесть ([T] - текстовый, [B] - двоичный):";
	while (!((tolower(filetype) == 'b') || (tolower(filetype) == 't')))
	{
		filetype = _getch();
	}
	string path;
	cout << "Введите путь к файлу: ";
	getline(cin, path);
	_path = path;
	fstream file;
	if (tolower(filetype) == 'b')
	{
		file = fstream(_path, ios::in | ios::binary);
	}
	else
	{
		file = fstream(_path, ios::in);
	}
	if (!file)
	{
		cout << "Ошибка при открытии файла" << endl;
		return false;
	}
	else
	{
		while (!file.eof())
		{
			int temp_i;
			string temp_s;
			record temp_r = record();
			if (tolower(filetype) == 'b')
			{
				file >> temp_r.oms_code;
				temp_r.surname = readStringFromBin(file);
				temp_r.name = readStringFromBin(file);
				temp_r.patronymic = readStringFromBin(file);
				temp_r.disease_code = readStringFromBin(file);
				temp_r.date = readStringFromBin(file);
				file >> temp_r.doctor_id;
			}
			else
			{
				file >> temp_r.oms_code;
				file >> temp_r.surname;
				file >> temp_r.name;
				file >> temp_r.patronymic;
				file >> temp_r.disease_code;
				file >> temp_r.date;
				file >> temp_r.doctor_id;
			}
			entries.append_to_end(temp_r);
		}
	}
	file.close();
	return true;
}

bool BinFileEditor::saveToBin()
{
	string path;
	cout << "Введите путь к создаваемому двоичному файлу: ";
	getline(cin, path);
	fstream file(path, ios::out | ios::binary);
	if (!file) 
	{
		cout << "Произошла ошибка при записи в файл." << endl;
		return false;
	}
	for (int i = 0; i < entries.size(); i++)
	{
		file << entries[i]->data.oms_code << "\n";
		writeStringToBin(file, entries[i]->data.surname);
		writeStringToBin(file, entries[i]->data.name);
		writeStringToBin(file, entries[i]->data.patronymic);
		writeStringToBin(file, entries[i]->data.disease_code);
		writeStringToBin(file, entries[i]->data.date);
		file << entries[i]->data.doctor_id;
		if (i < entries.size() - 1)
			file << "\n";
	}
	file.close();
	return true;
}

bool BinFileEditor::saveToText()
{
	string path;
	cout << "Введите путь к создаваемому текстовому файлу: ";
	getline(cin, path);
	fstream file(path, ios::out);
	if (!file)
	{
		cout << "Произошла ошибка при записи в файл." << endl;
		return false;
	}
	for (int i = 0; i < entries.size(); i++)
	{
		file << entries[i]->data.oms_code << "\n";
		file << entries[i]->data.surname << "\n";
		file << entries[i]->data.name << "\n";
		file << entries[i]->data.patronymic << "\n";
		file << entries[i]->data.disease_code << "\n";
		file << entries[i]->data.date << "\n";
		file << entries[i]->data.doctor_id;
		if (i < entries.size() - 1)
			file << "\n";
	}
	file.close();
	return true;
}

string BinFileEditor::readStringFromBin(fstream& file)
{
	int n = 0;
	file >> n;
	char* buf = new char[n];
	file.read(buf, n);
	string res = buf;
	delete[] buf;
	return res;
}

void BinFileEditor::writeStringToBin(fstream& file, string str)
{
	int n = str.size();
	file << n;
	file << str.c_str() << "\n";
}

void BinFileEditor::process()
{
	if (!init()) return;
	saveToBin();
	saveToText();
}