#include "list_2way.h"
#include "BinFileEditor.h"

list_2way entries; //нужно для записи в файл
fstream file;
bool isBinary;
string _path;


bool BinFileEditor::openFile(string path)
{
	file = fstream(path.c_str(), ios::in | ios::out | (isBinary * ios::binary));
	if (!file)
	{
		closeFile();
		return false;
	}
	return true;
}

bool BinFileEditor::reopenFile()
{
	int binary = file.flags() & ios::binary;
	file.close();
	return openFile(_path);
}

void BinFileEditor::closeFile()
{
	if (file.good())
	{
		cout << "Ошибок ввода/вывода в файл не обнаружено." << endl;
	}
	file.close();
}

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
	if (tolower(filetype) == 'b')
	{
		file = fstream(_path, ios::in | ios::binary);
		isBinary = true;
	}
	else
	{
		file = fstream(_path, ios::in);
		isBinary = false;
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
			if (isBinary)
			{
				file.read((char*)&temp_r, sizeof(record));
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
		if (isBinary)
			entries.delete_last();
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
		file.write((char*)(entries.get_element_by_index(i)), sizeof(record));
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

bool BinFileEditor::deleteRecordByKey(int key)
{
	return false;
}

bool BinFileEditor::searchByDisease(string disease_code)
{
	return false;
}

bool BinFileEditor::deleteRecord(int index)
{
	return false;
}

record BinFileEditor::readByIndex(int index)
{
	if (entries.size() < index)
	{
		cout << "Записи с номером " << index << " не существует" << endl;
		return record();
	}
	if (!reopenFile())
	{
		cout << "Ошибка при чтении файла" << endl;
		return record();
	}
	record res = record();
	for (int i = 0; i < index; i++)
	{
		if (isBinary)
		{
			file.read((char*)&res, sizeof(record));
		}
		else
		{
			file >> res.oms_code;
			file >> res.surname;
			file >> res.name;
			file >> res.patronymic;
			file >> res.disease_code;
			file >> res.date;
			file >> res.doctor_id;
		}
	}
	return res;
}

bool BinFileEditor::showContent()
{
	if (!reopenFile())
	{
		cout << "Ошибка при чтении файла" << endl;
		return false;
	}
	cout << "Содержание файла: " << endl;
	entries.clear();
	while (!file.eof())
	{
		int temp_i;
		string temp_s;
		record temp_r = record();
		if (isBinary)
		{
			file.read((char*)&temp_r, sizeof(record));
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
	if (isBinary)
		entries.delete_last();
	entries.show();
	return true;
}

void BinFileEditor::process()
{
	if (!init()) return;
	showContent();
	cout << "Введите индекс:" << endl;
	int n;
	cin >> n;
	record t = readByIndex(n);
	if (t != record())
		cout << "Запись с индексом " << n << ": " << "{ Номер полиса: " << t.oms_code << ", ФИО: " << t.surname << " " << t.name <<
		" " << t.patronymic << ", код болезни: " << t.disease_code << ", дата обращения - " << t.date
		<< ", ИД врача: " << t.doctor_id << "}" << endl;
	saveToBin();
	saveToText();
}