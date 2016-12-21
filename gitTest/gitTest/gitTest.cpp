// gitTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyClass.h"
#include "HappyDay.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CHappyDay day;
	CMyClass obj;
	printf("hello world\n");
	printf("good\n");
	obj.Say();
	obj.eat();
	day.Hello();
	getchar();
	return 0;
}

