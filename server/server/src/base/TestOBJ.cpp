#include "TestOBJ.h"
#include <iostream>

	TestOBJ::TestOBJ()
	{
		printf("TestOBJ new %p\n", this);
	}
	
	TestOBJ::~TestOBJ()
	{
		printf("~TestOBJ delete %p\n", this);
	}
	
	void TestOBJ::Test()
	{
		printf("TestOBJ Test\n");
	}