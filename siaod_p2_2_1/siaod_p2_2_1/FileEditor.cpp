#ifndef FileEditorCpp
#define FileEditorCpp
#include "FileEditor.h"

int NO_SUCH_INDEX_CODE = 2147483647;
int FILE_READING_ERROR_CODE = 2147483646;
fstream file;
string _path = "";

bool FileEditor::openFile(string path)
{
	file = fstream(path.c_str(), ios::in | ios::out);
	if (!file)
	{
		closeFile();
		return false;
	}
	return true;
}

bool FileEditor::reopenFile()
{
	file.close();
	return openFile(_path);
}

void FileEditor::closeFile()
{
	if (file.good())
	{
		cout << "������ �����/������ � ���� �� ����������." << endl;
	}
	file.close();
}

bool FileEditor::init()
{
	string path;
	cout << "������� ���� � �����: ";
	getline(cin, path);
	_path = path;
	return openFile(path);
}

bool FileEditor::showContent()
{
	if (!reopenFile())
	{
		cout << "������ ��� ������ �����" << endl;
		return false;
	}
	cout << "���������� �����:" << endl;
	while (!file.eof())
	{
		string temp;
		getline(file, temp);
		cout << temp << endl;
	}
	return true;
}

void FileEditor::append()
{
	file.seekg(0, ios::end);
	cout << "������� ����� ������ �����: ";
	string temp;
	getline(cin, temp);
	file << "\n" << temp;
	if (!file.fail())
		cout << "������ ����������� �������." << endl;
}

int FileEditor::readByIndex(int index)
{
	if (index > numberOfNumbers())
	{
		cout << "����� � �������� " << index << " �� ����������" << endl;
		return NO_SUCH_INDEX_CODE;
	}
	if (!reopenFile())
	{
		cout << "������ ��� ������ �����" << endl;
		return FILE_READING_ERROR_CODE;
	}
	int res = 0;
	for (int i = 0; i < index; i++)
	{
		file >> res;
	}
	return res;
}

int FileEditor::numberOfNumbers()
{
	if (!reopenFile())
	{
		cout << "������ ��� ������ �����" << endl;
		return FILE_READING_ERROR_CODE;
	}
	int temp;
	int amount = 0;
	while (!file.eof())
	{
		file >> temp;
		amount++;
	}
	return amount;
}

bool FileEditor::isPrimal(int n)
{
	if (n <= 0) return false;
	for (int i = 2; i*i <= n; i++)
	{
		if ((n % i) == 0) return false;
	}
	return true;
}

bool FileEditor::createFileWithPrimals()
{
	if (!reopenFile())
	{
		cout << "������ ��� ������ �����" << endl;
		return false;
	}
	int temp = 0;
	int amount = 0;
	string path;
	cout << "������� �������� �����, ���� ���������� ��������� ������: ";
	getline(cin, path);
	fstream newfile = fstream(path.c_str(), ios::out);
	if (!newfile)
	{
		cout << "�� ������� ������� ����" << endl;
	}
	else
	{
		while (!file.eof())
		{
			file >> temp;
			if (isPrimal(temp))
			{
				if (amount) newfile << "\n";
				newfile << temp;
				amount++;
			}
		}
		cout << "������ ����� ����; �������� ������� �����: " << amount << endl;
	}
	return true;
}

void FileEditor::process()
{
	if (!init())
	{
		cout << "�� ������� ������� ����" << endl;
		return;
	}
	char choose = ' ';
	bool running = true;
	int ind = 0;
	int res;
	while (running)
	{
		cout << "�������� ��������: " << endl << 
			"[R] - ������� ���������� �����" << endl << 
			"[A] - ������� ���������� ����� � �����" << endl << 
			"[F] - ����� ����� � �������� �������" << endl << 
			"[W] - �������� ������ � ����� �����" << endl <<
			"[N] - ������� ����� ����, ������� � ���� ������ ������� ����� �� ���������" << endl << 
			"[Q] - �����" << endl;
		choose = _getch();
		switch (tolower(choose))
		{
		case 'r':
			if (!showContent()) running = false;
			break;
		case 'a':
			if (!numberOfNumbers()) running = false;
			else { cout << "���������� ����� � �����: " << numberOfNumbers() << endl; }
			break;
		case 'f':
			cout << "������� ����� ����� ��� ������: ";
			cin >> ind;
			res = readByIndex(ind);
			if (res == NO_SUCH_INDEX_CODE)
			{

			}
			else if (res == FILE_READING_ERROR_CODE)
				running = false;
			else
			{
				cout << "����� � ������� " << ind << ": " << res << endl;
			}
			break;
		case 'w':
			append();
			break;
		case 'n':
			createFileWithPrimals();
			break;
		case 'q':
			running = false;
			break;
		}
		if (running)
		{
			system("pause");
			system("cls");
		}
	}
	closeFile();
}
#endif