// gitTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyClass.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CMyClass obj;
	printf("hello world\n");
	printf("good\n");
	obj.Say();
	getchar();
	return 0;
}

