// CPlusPlusLearning.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
using namespace System;
#include "StaticUtils.h"
using namespace Utils;
#include "AClass.h"
using namespace System::Threading;

int _num = 2;

int _tmain(int argc, _TCHAR* argv[])
{
	
	StaticUtils::DebugAddOne(_num);
	Console::WriteLine(_num);

	StaticUtils::DebugAddOne(6);
	//Console::WriteLine(num);
	int b = StaticUtils::ReadIncomingByte();

	int t = StaticUtils::TestAutoInt();
	StaticUtils::Debug(t);

	//AClass::StaticMember = _num;
	AClass::StaticMethod();

	String^ runTime = StaticUtils::GetRuntime();
	Thread::Sleep(2500);
	runTime = StaticUtils::GetRuntime();
	StaticUtils::Debug(runTime);
	Thread::Sleep(2500);
	StaticUtils::PrintRuntime();
	Thread::Sleep(4500);
	StaticUtils::PrintRuntime();
	
	system("pause");
	return 0;
}

