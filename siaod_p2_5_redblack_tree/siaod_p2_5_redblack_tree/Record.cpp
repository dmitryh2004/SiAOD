#include "Record.h"

record::record()
{
	for (int i = 0; i < 11; i++)
	{
		this->phone[i] = 0;
		this->address[i] = 0;
	}
	for (int i = 11; i < 100; i++)
	{
		this->address[i] = 0;
	}
	strcpy_s(this->phone, "1234567890");
	strcpy_s(this->address, "Generic address");
}

record::record(char* phone, char* address)
{
	for (int i = 0; i < 11; i++)
	{
		this->phone[i] = 0;
		this->address[i] = 0;
	}
	for (int i = 11; i < 100; i++)
	{
		this->address[i] = 0;
	}
	strcpy_s(this->phone, phone);
	strcpy_s(this->address, address);
}

bool record::operator ==(record* right)
{
	if (strcmp(this->phone, right->phone)) return false;
	if (strcmp(this->address, right->address)) return false;
	return true;
}

bool record::operator!=(record* right)
{
	return !(*this == right);
}