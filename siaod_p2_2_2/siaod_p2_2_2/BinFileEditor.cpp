#include "list_2way.h"
#include "BinFileEditor.h"

list_2way entries; //����� ��� ������ � ����
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
	file.close();
	return openFile(_path);
}

void BinFileEditor::closeFile()
{
	if (file.good())
	{
		cout << "������ �����-������ �� ����������." << endl;
	}
	file.close();
}

bool BinFileEditor::init()
{
	char filetype = ' ';
	cout << "�������� ��� �����, ������� ���������� �������� ([T] - ���������, [B] - ��������):";
	while (!((tolower(filetype) == 'b') || (tolower(filetype) == 't')))
	{
		filetype = _getch();
	}
	string path;
	cout << endl << "������� ���� � �����: ";
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
		cout << "������ ��� �������� �����" << endl;
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
				getline(file, temp_s); temp_r.oms_code = strtol(temp_s.c_str(), nullptr, 0);
				file.getline(temp_r.surname, 20);
				file.getline(temp_r.name, 20);
				file.getline(temp_r.patronymic, 20);
				file.getline(temp_r.disease_code, 6);
				file.getline(temp_r.date, 9);
				getline(file, temp_s); temp_r.doctor_id = strtol(temp_s.c_str(), nullptr, 0);
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
	cout << "������� ���� � ������������ ��������� �����: ";
	getline(cin, path);
	fstream file2(path, ios::out | ios::binary);
	if (!file2)
	{
		cout << "��������� ������ ��� ������ � ����." << endl;
		return false;
	}
	for (int i = 0; i < entries.size(); i++)
	{
		file2.write((char*)(entries.get_element_by_index(i)), sizeof(record));
	}
	file2.close();
	return true;
}

bool BinFileEditor::saveToText()
{
	string path;
	cout << "������� ���� � ������������ ���������� �����: ";
	getline(cin, path);
	fstream file2(path, ios::out);
	if (!file2)
	{
		cout << "��������� ������ ��� ������ � ����." << endl;
		return false;
	}
	for (int i = 0; i < entries.size(); i++)
	{
		file2 << entries[i]->data.oms_code << "\n";
		file2 << entries[i]->data.surname << "\n";
		file2 << entries[i]->data.name << "\n";
		file2 << entries[i]->data.patronymic << "\n";
		file2 << entries[i]->data.disease_code << "\n";
		file2 << entries[i]->data.date << "\n";
		file2 << entries[i]->data.doctor_id;
		if (i < entries.size() - 1)
			file2 << "\n";
	}
	file2.close();
	return true;
}

void BinFileEditor::saveBin()
{
	file.close();
	file = fstream(_path.c_str(), ios::out | ios::binary);
	if (!file)
	{
		cout << "��������� ������ ��� ������ � ����." << endl;
		return;
	}
	for (int i = 0; i < entries.size(); i++)
	{
		file.write((char*)(entries.get_element_by_index(i)), sizeof(record));
	}
	file.close();
	file = fstream(_path.c_str(), ios::in | ios::out | ios::binary);
}

void BinFileEditor::saveText()
{
	file.close();
	file = fstream(_path, ios::out);
	if (!file)
	{
		cout << "��������� ������ ��� ������ � ����." << endl;
		return;
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
	file = fstream(_path.c_str(), ios::in | ios::out);
}

bool BinFileEditor::deleteRecordByKey(int key)
{
	if (!entries.get_element_by_key(key))
	{
		cout << "������ � ����� ������� ������ �� �������" << endl;
		return false;
	}
	else
	{
		int index = entries.get_element_index(entries.get_element_by_key(key)->data);
		entries.delete_element(index);
		if (isBinary)
		{
			saveBin();
		}
		else
		{
			saveText();
		}
		cout << "������ ������� �������" << endl;
	}
	return true;
}

bool BinFileEditor::searchByDisease(string disease_code)
{
	string path;
	cout << "������� ����, �� �������� ����� ��������� ������: ";
	getline(cin, path);
	fstream file2 = fstream(path, ios::out | ios::binary);
	if (!file2)
	{
		cout << "��������� ������ ��� ������ � ����." << endl;
		return false;
	}
	else
	{
		int total = 0;
		for (int i = 0; i < entries.size(); i++)
		{
			if (entries[i]->data.disease_code == disease_code)
			{
				file2.write((char*)(entries.get_element_by_index(i)), sizeof(record));
				total++;
			}
		}
		cout << "������ �������� ����; ���������� " << total << " �������" << endl;
	}
	return true;
}

bool BinFileEditor::deleteRecord(int key)
{
	if (!entries.get_element_by_key(key))
	{
		cout << "������ � ����� ������� ������ �� �������" << endl;
		return false;
	}
	else
	{
		int index = entries.get_element_index(entries.get_element_by_key(key)->data);
		record last = record(entries.get_last()->data);
		entries[index]->data = record(last);
		if (isBinary)
		{
			saveBin();
		}
		else
		{
			saveText();
		}
		cout << "������ ������� �������� �� ��������� ������" << endl;
	}
	return true;
}

bool BinFileEditor::readByIndex(int index, record &res)
{
	if ((entries.size() < index) || (index < 0))
	{
		cout << "������ � �������� " << index << " �� ����������" << endl;
		return false;
	}
	if (!reopenFile())
	{
		cout << "������ ��� ������ �����" << endl;
		return false;
	}
	string temp_s;
	res = record();
	for (int i = 0; i < index; i++)
	{
		if (isBinary)
		{
			file.read((char*)&res, sizeof(record));
		}
		else
		{
			getline(file, temp_s); res.oms_code = strtol(temp_s.c_str(), nullptr, 0);
			file.getline(res.surname, 20);
			file.getline(res.name, 20);
			file.getline(res.patronymic, 20);
			file.getline(res.disease_code, 6);
			file.getline(res.date, 9);
			getline(file, temp_s); res.doctor_id = strtol(temp_s.c_str(), nullptr, 0);
		}
	}
	return true;
}

bool BinFileEditor::showContent()
{
	if (!reopenFile())
	{
		cout << "������ ��� ������ �����" << endl;
		return false;
	}
	cout << "���������� �����: " << endl;
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
			getline(file, temp_s); temp_r.oms_code = strtol(temp_s.c_str(), nullptr, 0);
			file.getline(temp_r.surname, 20);
			file.getline(temp_r.name, 20);
			file.getline(temp_r.patronymic, 20);
			file.getline(temp_r.disease_code, 6);
			file.getline(temp_r.date, 9);
			getline(file, temp_s); temp_r.doctor_id = strtol(temp_s.c_str(), nullptr, 0);
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
	char choose = ' ';
	int n;
	record t;
	string disease_code_search = "";
	bool running = true;
	while (running)
	{
		cout << "�������� ��������: " << endl
			<< "[T] - ��������� ������� ������ � ��������� ����" << endl
			<< "[B] - ��������� ������� ������ � �������� ����" << endl
			<< "[C] - ������� ���������� �������� �����" << endl
			<< "[I] - �������� ������ �� �������" << endl
			<< "[D] - ������� ������ �� ����� ����� ������ �� ��������� ������" << endl
			<< "[K] - ������� ������ �� �����, �������� ������� ��������� �������" << endl
			<< "[S] - ������������ ����� �������� ���� �� ������� � ������������ ����� �������" << endl
			<< "[Q] - �����" << endl;
		choose = _getch();
		switch (tolower(choose))
		{
		case 'q':
			running = false;
			break;
		case 't':
			saveToText();
			break;
		case 'b':
			saveToBin();
			break;
		case 'c':
			showContent();
			break;
		case 'i':
			cout << "������� ������:" << endl;
			cin >> n;
			cin.ignore(32768, '\n');
			if (readByIndex(n, t))
			{
				cout << "������ � �������� " << n << ": " << "{ ����� ������: " << t.oms_code << ", ���: " << t.surname << " " << t.name <<
					" " << t.patronymic << ", ��� �������: " << t.disease_code << ", ���� ��������� - " << t.date
					<< ", �� �����: " << t.doctor_id << "}" << endl;
			}
			break;
		case 'd':
			cout << "������� ����� ������:" << endl;
			cin >> n;
			cin.ignore(32768, '\n');
			if (entries.get_element_by_key(n))
			{
				t = entries.get_element_by_key(n)->data;
				deleteRecord(t.oms_code);
			}
			else
			{
				cout << "������ � ����� ������� ������ �� �������" << endl;
			}
			break;
		case 'k':
			cout << "������� ����� ������:" << endl;
			cin >> n;
			cin.ignore(32768, '\n');
			if (entries.get_element_by_key(n))
			{
				t = entries.get_element_by_key(n)->data;
				deleteRecordByKey(t.oms_code);
			}
			else
			{
				cout << "������ � ����� ������� ������ �� �������" << endl;
			}
			break;
		case 's':
			cout << "������� ��� �������, ������� ���������� �����: " << endl;
			cin >> disease_code_search;
			cin.ignore(32768, '\n');
			searchByDisease(disease_code_search);
			break;
		default:
			cout << "����������� ��������." << endl;
		}
		if (running)
		{
			system("pause");
			system("cls");
		}
	}
	closeFile();
}