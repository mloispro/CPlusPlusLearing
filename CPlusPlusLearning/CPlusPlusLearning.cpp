// CPlusPlusLearning.cpp : Defines the entry point for the console application.
//
//#include <msclr\marshal.h>
#include <iostream>
#include "stdafx.h"
using namespace System;
using namespace System::Threading;

#include "AClass.h"

#include "ApiClassTester.h"
using namespace Tests;
#include "ApiClassExt.h"

#include "StaticUtils.h"
using namespace Utils;

//using namespace Extensions;



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

	
	/*String^ runTime = ApiClassExt::GetRuntime();
	runTime = ApiClassExt::GetRuntime();
	StaticUtils::Debug(runTime);
	ApiClassExt::PrintRuntime();*/

	//ApiClassTester apiClassTester;
	//apiClassTester.Test();
	ApiClassExt ext;
	String^ runTime = ext.GetRuntime();
	runTime = ext.GetRuntime();
	StaticUtils::Debug(runTime);
	ext.PrintRuntime();

	ApiClassTester::Test();



	system("pause");
	return 0;
}



