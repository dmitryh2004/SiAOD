#pragma once
#ifndef __hashtable_h__
#define __hashtable_h__
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <chrono>
#include "Record.h"

using namespace std;

namespace Hashtable {
	int getHash(record* data);

	struct hashtable_entry {
		bool open = true;
		bool wasCollision = false;
		int hash = 0;
		int record_number = -1;
		char key[11];
		hashtable_entry(int hash);
		~hashtable_entry();
	};

	class hashtable {
		vector<hashtable_entry*> entries;
		int used_entries = 0;
	public:
		float getUsage();
		void show();
		bool addData(record* data, int record_number);
		bool removeData(record* data);
		int findData(char* phone);
		void process();
		void rehash(bool mode, int pos);
		void extend_table();
		hashtable();
		hashtable(int size);
		~hashtable();
	};
}
#endif