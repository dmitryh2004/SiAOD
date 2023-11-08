#pragma once
#ifndef __RECORD_H__
#define __RECORD_H__
#include <iostream>
#include <string>

struct record {
	char phone[11];
	char address[100];
	record();
	record(char* phone, char* address);
	bool operator == (record* right);
	bool operator != (record* right);
};
#endif