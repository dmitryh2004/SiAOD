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
		cout << "Ошибок ввода/вывода в файл не обнаружено." << endl;
	}
	file.close();
}

bool FileEditor::init()
{
	string path;
	cout << "Введите путь к файлу: ";
	getline(cin, path);
	_path = path;
	return openFile(path);
}

bool FileEditor::showContent()
{
	if (!reopenFile())
	{
		cout << "Ошибка при чтении файла" << endl;
		return false;
	}
	cout << "Содержимое файла:" << endl;
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
	cout << "Введите новую строку файла: ";
	string temp;
	getline(cin, temp);
	file << "\n" << temp;
	if (!file.fail())
		cout << "Запись произведена успешно." << endl;
}

int FileEditor::readByIndex(int index)
{
	if (index > numberOfNumbers())
	{
		cout << "Числа с индексом " << index << " не существует" << endl;
		return NO_SUCH_INDEX_CODE;
	}
	if (!reopenFile())
	{
		cout << "Ошибка при чтении файла" << endl;
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
		cout << "Ошибка при чтении файла" << endl;
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
		cout << "Ошибка при чтении файла" << endl;
		return false;
	}
	int temp = 0;
	int amount = 0;
	string path;
	cout << "Введите название файла, куда необходимо сохранить данные: ";
	getline(cin, path);
	fstream newfile = fstream(path.c_str(), ios::out);
	if (!newfile)
	{
		cout << "Не удалось создать файл" << endl;
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
		cout << "Создан новый файл; записано простых чисел: " << amount << endl;
	}
	return true;
}

void FileEditor::process()
{
	if (!init())
	{
		cout << "Не удалось открыть файл" << endl;
		return;
	}
	char choose = ' ';
	bool running = true;
	int ind = 0;
	int res;
	while (running)
	{
		cout << "Выберите действие: " << endl << 
			"[R] - вывести содержимое файла" << endl << 
			"[A] - вывести количество чисел в файле" << endl << 
			"[F] - найти число с заданным номером" << endl << 
			"[W] - добавить запись в конец файла" << endl <<
			"[N] - создать новый файл, записав в него только простые числа из исходного" << endl << 
			"[Q] - выход" << endl;
		choose = _getch();
		switch (tolower(choose))
		{
		case 'r':
			if (!showContent()) running = false;
			break;
		case 'a':
			if (!numberOfNumbers()) running = false;
			else { cout << "Количество чисел в файле: " << numberOfNumbers() << endl; }
			break;
		case 'f':
			cout << "Введите номер числа для поиска: ";
			cin >> ind;
			res = readByIndex(ind);
			if (res == NO_SUCH_INDEX_CODE)
			{

			}
			else if (res == FILE_READING_ERROR_CODE)
				running = false;
			else
			{
				cout << "Число с номером " << ind << ": " << res << endl;
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