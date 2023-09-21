#pragma once
#ifndef __BinFileEditor_H__
#define __BinFileEditor_H__
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include "list_2way.h"
using namespace std;

namespace BinFileEditor {
	bool openFile(string path);
	bool reopenFile();
	void closeFile();

	bool deleteRecordByKey(int key); //удалить пациента, сохраняя порядок остальных записей
	bool searchByDisease(string disease_code); //сформировать новый двоичный файл из людей с заболеванием
	bool deleteRecord(int index); //удалить запись по индексу, последнюю запись переместить на место удаленной
	record readByIndex(int index); //прочитать запись по индексу
	bool showContent(); //содержимое
	bool saveToText(); //создание текстового файла на основе текущих записей
	bool saveToBin(); //создание двоичного файла на основе текущих записей

	void process(); //интерфейс для взаимодействия с файлом, который запускается из основной программы

	bool init(); //инициализация
}

#endif