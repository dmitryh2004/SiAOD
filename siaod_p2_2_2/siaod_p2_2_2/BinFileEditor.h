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
	void saveBin(); //��������� ���������� � �������� ����
	void saveText(); //��������� ���������� � ��������� ����

	bool deleteRecordByKey(int key); //������� ��������, �������� ������� ��������� �������
	bool searchByDisease(string disease_code); //������������ ����� �������� ���� �� ����� � ������������
	bool deleteRecord(int key); //������� ������ �� �������, ��������� ������ ����������� �� ����� ���������
	bool readByIndex(int index, record &res); //��������� ������ �� �������
	bool showContent(); //����������
	bool saveToText(); //�������� ���������� ����� �� ������ ������� �������
	bool saveToBin(); //�������� ��������� ����� �� ������ ������� �������

	void process(); //��������� ��� �������������� � ������, ������� ����������� �� �������� ���������

	bool init(); //�������������
}

#endif