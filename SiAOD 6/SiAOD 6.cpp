// SiAOD 6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <locale.h>
#include <chrono>
#include <fstream>

using namespace std;

int convert_to_hash(string str)
{
	int temp = 0;
	for (int i = 0; i < str.size(); i++)
	{
		temp += (int)str[i];
	}
	return (temp % 1073741824);
}

int find_str(string& where_, string& what, int& comps, int& moves)
{
	int i = 0;
	int where_size = where_.size();
	int whatsize = what.size();
	string temp = "";
	for (i = 0; i < where_size - whatsize + 1; i++)
	{
		moves++;
		temp = "";
		for (int j = 0; j < whatsize; j++)
		{
			temp += where_[i + j];
		}
		comps++;
		if (temp == what)
		{
			return i;
		}	
	}
	return -1;
}

int find_with_hash(string& where_, string& what, int* hashes, int hashes_size, int& comps, int& moves)
{
	int whatsize = what.size();
	int pos = -1;
	string temp = "";
	int what_hash = convert_to_hash(what);
	for (int i = 0; i < hashes_size; i++)
	{
		if (hashes[i] == what_hash)
		{
			moves++;
			temp = "";
			for (int j = 0; j < whatsize; j++)
			{
				temp += where_[i + j];
			}
			comps++;
			if (temp == what)
			{
				pos = i;
				break;
			}
		}
	}
	
	return pos;
}

void launch_find(string& where_, string& what)
{
	int where_size = where_.size();
	int whatsize = what.size();
	auto find_start = chrono::steady_clock::now();
	int comps = 0, moves = 0;
	int pos = find_str(where_, what, comps, moves);
	auto find_end = chrono::steady_clock::now();
	auto find_dur = chrono::duration_cast<chrono::milliseconds>(find_end - find_start);
	cout << "--- Поиск подстроки размера " << whatsize << " в строке размера " << where_size << " --- " << endl;
	cout << "Время выполнения: " << find_dur.count() << " мс" << endl;
	cout << "Сравнений: " << comps << "\nСдвигов подстроки: " << moves << endl;
	cout << "-------------------------------------------\n";
	if (pos != -1)
		cout << "Подстрока найдена на позиции " << pos << endl;
	else
		cout << "Подстрока не найдена" << endl;
	cout << "===========================================\n";
}

void launch_hashfind(string& where_, string& what)
{
	int where_size = where_.size();
	int whatsize = what.size();
	auto prepare_hashes_start = chrono::steady_clock::now();
	int* hashes = new int[where_size - whatsize + 1];
	string temp = "";
	for (int i = 0; i < where_size - whatsize + 1; i++)
	{
		temp = "";
		for (int j = 0; j < whatsize; j++)
		{
			temp += where_[i + j];
		}
		hashes[i] = convert_to_hash(temp);
	}
	auto prepare_hashes_end = chrono::steady_clock::now();
	auto find_start = chrono::steady_clock::now();
	int comps = 0, moves = 0;
	int pos = find_with_hash(where_, what, hashes, where_size - whatsize + 1, comps, moves);
	auto find_end = chrono::steady_clock::now();
	auto prepare_dur = chrono::duration_cast<chrono::milliseconds>(prepare_hashes_end - prepare_hashes_start);
	auto find_dur = chrono::duration_cast<chrono::microseconds>(find_end - find_start);
	cout << "--- Поиск подстроки размера " << whatsize << " в строке размера " << where_size << " --- " << endl;
	cout << "Время выполнения: \n- Генерация хэшей - " << prepare_dur.count() << " мс\n- Поиск по хэшу - " <<
		find_dur.count() << " мкс\nВсего - " << prepare_dur.count() + round(find_dur.count() / 1000) << " мс" << endl;
	cout << "Сравнений: " << comps << "\nСдвигов подстроки: " << moves << endl;
	cout << "-------------------------------------------\n";
	if (pos != -1)
		cout << "Подстрока найдена на позиции " << pos << endl;
	else
		cout << "Подстрока не найдена" << endl;
	cout << "===========================================\n";
	delete[] hashes;
}

void readfile(const char* path, string& saveto)
{
	fstream inf(path, ios::in);
	if (!inf)
	{
		cout << "Ошибка: не удалось прочитать файл \"" << path << "\"." << endl;
		return;
	}
	while (!inf.eof())
	{
		string temp = "";
		getline(inf, temp);
		saveto += temp;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	string Zamyatin = "";
	string Dostoevskiy = "";
	string Pushkin = "";
	string Gogol = "";
	readfile("Лермонтов Герой нашего времени", Gogol);
	readfile("Замятин Мы (записи 1 - 5).txt", Zamyatin);
	readfile("Достоевский Преступление и наказание (первая часть).txt", Dostoevskiy);
	readfile("Пушкин Метель.txt", Pushkin);
	readfile("Гоголь Шинель.txt", Gogol);

	string small_strings[] = { "молитвы", "молитвы", "подстрекало", "Калинкиным" };

	cout << "Этап 1: поиск маленьких строк в файле" << endl << "======================================" << endl;
	launch_hashfind(Zamyatin, small_strings[0]);
	launch_find(Zamyatin, small_strings[0]);

	launch_hashfind(Dostoevskiy, small_strings[1]);
	launch_find(Dostoevskiy, small_strings[1]);

	launch_hashfind(Pushkin, small_strings[2]);
	launch_find(Pushkin, small_strings[2]);

	launch_hashfind(Gogol, small_strings[3]);
	launch_find(Gogol, small_strings[3]);

	system("pause");
	system("cls");

	string big_strings[] = { 
		"Все мы (а может быть, и вы) еще детьми, в школе читали этот величайший из дошедших до нас памятников древней литературы — «Расписание железных дорог».", 
		"Вон он теперь отошел маленько, стоит, будто папироску свертывает... Как бы нам ему не дать? Как бы нам ее домой отправить, — подумайте-ка!", 
		"Память его казалась священною для Маши; по крайней мере она берегла всё, что могло его напомнить: книги, им некогда прочитанные, его рисунки, ноты и стихи, им переписанные для нее.", 
		"Вдали, Бог знает где, мелькал огонек в какой-то будке, которая казалась стоявшей на краю света. Веселость Акакия Акакиевича как-то здесь значительно уменьшилась." 
	};

	cout << "Этап 2: поиск больших строк в файле" << endl << "======================================" << endl;
	launch_hashfind(Zamyatin, big_strings[0]);
	launch_find(Zamyatin, big_strings[0]);

	launch_hashfind(Dostoevskiy, big_strings[1]);
	launch_find(Dostoevskiy, big_strings[1]);

	launch_hashfind(Pushkin, big_strings[2]);
	launch_find(Pushkin, big_strings[2]);

	launch_hashfind(Gogol, big_strings[3]);
	launch_find(Gogol, big_strings[3]);
	system("pause");
	system("cls");

	cout << "Этап 3: неудачный поиск строки в файле" << endl << "======================================" << endl;
	string what_nottofind = "тсшеуа5г4р9щ57щар87ощ897рпи5ущ";
	launch_hashfind(Zamyatin, what_nottofind);
	launch_find(Zamyatin, what_nottofind);

	launch_hashfind(Dostoevskiy, what_nottofind);
	launch_find(Dostoevskiy, what_nottofind);

	launch_hashfind(Pushkin, what_nottofind);
	launch_find(Pushkin, what_nottofind);

	launch_hashfind(Gogol, what_nottofind);
	launch_find(Gogol, what_nottofind);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
