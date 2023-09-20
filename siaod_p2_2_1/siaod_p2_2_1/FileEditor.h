#ifndef FileEditorH
#define FileEditorH

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cmath>

using namespace std;

namespace FileEditor {

	bool openFile(string path); //открыть файл
	void closeFile();
	bool reopenFile();

	bool showContent(); //содержимое
	void append(); //добавить запись в конец файла
	int readByIndex(int index); //прочитать число по индексу
	int numberOfNumbers(); //количество чисел
	bool createFileWithPrimals();

	void process(); //интерфейс для взаимодействия с файлом, который запускается из основной программы

	bool init(); //инициализация
	bool isPrimal(int n); //проверка простоты
}
#endif