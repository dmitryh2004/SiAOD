#ifndef FileEditorH
#define FileEditorH

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cmath>

using namespace std;

namespace FileEditor {

	bool openFile(string path); //������� ����
	void closeFile();
	bool reopenFile();

	bool showContent(); //����������
	void append(); //�������� ������ � ����� �����
	int readByIndex(int index); //��������� ����� �� �������
	int numberOfNumbers(); //���������� �����
	bool createFileWithPrimals();

	void process(); //��������� ��� �������������� � ������, ������� ����������� �� �������� ���������

	bool init(); //�������������
	bool isPrimal(int n); //�������� ��������
}
#endif