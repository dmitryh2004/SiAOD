#pragma once
#ifndef __BIN_FILE_READER_H__
#define __BIN_FILE_READER_H__
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include "Record.h"

using namespace std;

namespace BinFileEditor {
	fstream file;
	string _path;

	void closeFile() 
	{
		if (file.good())
		{
			cout << "Ошибки ввода-вывода не обнаружены." << endl;
		}
		file.close();
	}

	bool openFile(string path)
	{
		file = fstream(path.c_str(), ios::in | ios::out | ios::binary);
		if (!file)
		{
			closeFile();
			return false;
		}
		return true;
	}

	bool reopenFile()
	{
		file.close();
		return openFile(_path);
	}

	bool readByIndex(int index, record &res)
	{
		record temp;
		reopenFile();
		for (int i = 0; i < index; i++)
		{
			if (file.eof()) {
				return false;
			}
			file.read((char*)&temp, sizeof(record));
		}
		if (!strcmp(temp.address, "Generic address"))
		{
			return false;
		}
		res = temp;
		return true;
	}

	bool readNext(record &res) 
	{
		record temp;
		if (!file.eof())
			file.read((char*)&temp, sizeof(record));
		else return false;
		if (!strcmp(temp.address, "Generic address"))
		{
			return false;
		}
		res = temp;
		return true;
	}

	bool init(string path)
	{
		_path = path;
		return openFile(path);
	}
}
#endif