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

	bool deleteRecordByKey(int key); //������� ��������, �������� ������� ��������� �������
	bool searchByDisease(string disease_code); //������������ ����� �������� ���� �� ����� � ������������
	bool deleteRecord(int index); //������� ������ �� �������, ��������� ������ ����������� �� ����� ���������
	record readByIndex(int index); //��������� ������ �� �������
	bool showContent(); //����������
	bool saveToText(); //�������� ���������� ����� �� ������ ������� �������
	bool saveToBin(); //�������� ��������� ����� �� ������ ������� �������

	void process(); //��������� ��� �������������� � ������, ������� ����������� �� �������� ���������

	bool init(); //�������������
}

#endif