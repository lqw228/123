#include "StdAfx.h"
#include "MyClass.h"

CMyClass::CMyClass(void)
{
}

CMyClass::~CMyClass(void)
{
}

// speak
int CMyClass::Say(void)
{
	printf("hello Say\n");
	return 0;
}

// eat
void CMyClass::eat(void)
{
	printf("eat\n");
}
