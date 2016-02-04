// CPlusPlusLearning.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
using namespace System;
#include "Print.h"
using namespace Utils;

int _tmain(int argc, _TCHAR* argv[])
{
	int num = 2;
	Print::DebugAddOne(num);
	Console::WriteLine(num);

	Print::DebugAddOne(6);
	//Console::WriteLine(num);
	int b = Print::ReadIncomingByte();

	int t = Print::TestAutoInt();
	Print::Debug(t);

	system("pause");
	return 0;
}

