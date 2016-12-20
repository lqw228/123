// gitTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyClass.h"
#include "Game.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CMyClass obj;
	CGame gm;
	printf("hello world\n");
	printf("good\n");
	obj.Say();
	obj.eat();
	gm.Play();
	getchar();
	return 0;
}

