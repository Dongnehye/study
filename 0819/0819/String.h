#pragma once
#include <iostream>

using namespace std;

class String
{
	//char szBuffer[256];
	char* buf;
public:
	//String(const char* _szBuffer)
	//{
	//	strcpy(szBuffer, _szBuffer);
	//}
	String(const char* sz)
	{
		buf = new char[strlen(sz) + 1];
	}
	~String()
	{
		delete[] buf;
	}
	const String& operator=(const String& arg)
	{
		delete[] buf;
		buf = new char[strlen(arg.buf) + 1];
		strcpy(buf, arg.buf);
		return *this;
	}
	//operator const char*() const
	//{
	//	return szBuffer;
	//}
	


};

