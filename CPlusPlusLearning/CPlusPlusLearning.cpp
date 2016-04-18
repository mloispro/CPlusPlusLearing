// CPlusPlusLearning.cpp : Defines the entry point for the console application.
//
//#include <msclr\marshal.h>
#include "stdafx.h"
#include <iostream>



#include "AClass.h"

#include "ApiClassTester.h"
using namespace Tests;
#include "ApiClassExt.h"
#include "LCDMenuController.h"

#include "StaticUtils.h"
using namespace Utils;

using namespace System;
using namespace System::Threading;
//using namespace System::ComponentModel;         // for BackgroundWorker  
//
//public: System::ComponentModel::BackgroundWorker ^bgw;

//#include "ScheduleExt.h"
//using namespace Sched;

//using namespace Extensions;



int _num = 2;
int _runCountDown;
int _lastRun;

template<typename T = void>
int GetNextRunInSeconds(int runTime, int expectedNextRun, int expectedRunCountDown)
{
	int runEvery = 20;
	int nextRun = 0;

	
	Console::WriteLine("INPUT: ");
	Console::WriteLine("runTime: "+ runTime);
	Console::WriteLine("lastRun: "+ _lastRun);
	Console::WriteLine("runCountDown: "+ _runCountDown);
	Console::WriteLine(" ");

	int elapsedTime = runTime - _lastRun;

	if (_runCountDown <= 0 && _lastRun <= 0){ //first run
		_runCountDown = runEvery - runTime;
		nextRun = _runCountDown;
		//return nextRun;
	}
	else if (elapsedTime > runEvery){
		_runCountDown = 0;
		nextRun = runTime;
	}
	else if (_lastRun > runTime){
		_lastRun = 0;
		_runCountDown = _runCountDown - runTime;
		nextRun = runTime + _runCountDown;
	}
	else{
		if (_lastRun <= 0){ //restart, or countdown expired
			_runCountDown = _runCountDown - runTime;
		}
		else{
			_runCountDown = runEvery - elapsedTime;
			nextRun = _lastRun + runEvery;
		}
		
	}
	if (_runCountDown <= 0){ //needs to run set to 0
		_runCountDown = 0;
		nextRun = runTime;
	}

	Console::WriteLine("OUTPUT: ");

	Console::WriteLine("nextRun: "+ nextRun);
	Console::WriteLine("runCountDown: "+ _runCountDown);
	Console::WriteLine("expectedNextRun: "+ expectedNextRun);
	Console::WriteLine("expectedRunCountDown: "+ expectedRunCountDown);

	return nextRun;
}
template<typename T = void>
void IsTimeToRun(int runTime, int expectedNextRun, int expectedRunCountDown){
	int theNextRun = GetNextRunInSeconds(runTime, expectedNextRun, expectedRunCountDown);
	if (theNextRun <= runTime){
		Console::WriteLine("IsTimeToRun: "+ true);
		_lastRun = runTime;
	}
	else{
		Console::WriteLine("IsTimeToRun: " + false);
	}
	
	Console::WriteLine("");
	Console::WriteLine("------------------------------------");
}

#pragma region LCDMenu

using namespace Controllers;


template<typename T = void>
//freq,h,min,am - am=0,pm=1 -> [am=0,pm=1]
String^ TestSetTimer(LCDMenuController menuController, int freq, int hour, int min, int amPm ){

	menuController._optionCount = freq; //0=24, 1=48
	menuController.SaveRangeOption(LCDMenu::RangeType::Frequency, AccessoryType::Feeder);

	menuController._optionCount = hour;
	menuController.SaveRangeOption(LCDMenu::RangeType::Hour, AccessoryType::Feeder);

	menuController._optionCount = min;
	menuController.SaveRangeOption(LCDMenu::RangeType::Minute, AccessoryType::Feeder);

	menuController._optionCount = amPm;//0=am,1=PM
	menuController.SaveRangeOption(LCDMenu::RangeType::AmPm, AccessoryType::Feeder);
	
	return menuController.GetTimeFrequency(AccessoryType::Feeder);


}

template<typename T = void>
//y,m,d,h,min,am -> [am=0,pm=1]
String^ TestSetClock(LCDMenuController menuController, int y, int mon, int d, int h, int min, int amPm){
	
	menuController._optionCount = y;
	menuController.SaveRangeOption(LCDMenu::RangeType::Year, AccessoryType::Clock);
	
	menuController._optionCount = mon;
	menuController.SaveRangeOption(LCDMenu::RangeType::Month, AccessoryType::Clock);

	menuController._optionCount = d;
	menuController.SaveRangeOption(LCDMenu::RangeType::Day, AccessoryType::Clock);

	menuController._optionCount = h;
	menuController.SaveRangeOption(LCDMenu::RangeType::Hour, AccessoryType::Clock);

	menuController._optionCount = min;
	menuController.SaveRangeOption(LCDMenu::RangeType::Minute, AccessoryType::Clock);

	menuController._optionCount = amPm;//0=am,1=PM
	menuController.SaveRangeOption(LCDMenu::RangeType::AmPm, AccessoryType::Clock);

	return menuController.GetTimeLong(AccessoryType::Clock);
}


template<typename T = void>
int TestMenu()
{
	long sleep = 60 * 1000;
	String^ time;
	String^ freq;

	LCDMenuController menuController;

	//** dont worry about TIME being a little off, works fine in arduino api.
	time = TestSetClock(menuController, 2024, 1, 23, 12, 54, 0); //01/23/2024 12:54AM, !01/22/2024 11:54PM
	time = TestSetClock(menuController, 2021, 7, 18, 8, 46, 1); // 07/18/2021 08:46PM
	
	freq = TestSetTimer(menuController, 0, 5, 10, 0); //05:10AM, Daily
	freq = TestSetTimer(menuController, 1, 5, 10, 1); //05:10PM, Every Other Day
	menuController.PrintTime();
	menuController.PrintRunInfo(AccessoryType::Feeder);

	time = TestSetClock(menuController, 2018, 3, 9, 2, 4, 0); // 03/09/2018 02:04AM
	freq = TestSetTimer(menuController, 1, 1, 0, 1);
	freq = TestSetTimer(menuController, 0, 1, 0, 0);
	
	menuController.PrintTime();
	menuController.PrintRunInfo(AccessoryType::Feeder);
	menuController.SelectMainMenu();

	//for scroll outside main menu
	menuController.PrintRunInfo(AccessoryType::Feeder);
	Thread::Sleep(sleep);
	menuController.PrintRunInfo(AccessoryType::Feeder);
	Thread::Sleep(sleep);
	menuController.PrintRunInfo(AccessoryType::Feeder);
	Thread::Sleep(sleep);

	return 0;
}

#pragma endregion LCDMenu

int _tmain(int argc, _TCHAR* argv[])
{
	
	TestMenu();


	//schedules
	//persist: lastrun and runcountdown
	//int runTime, int expectedNextRun, int expectedRunCountDown
	//IsTimeToRun(6, 14, 14); //first run
	//IsTimeToRun(20, 20, 0);
	//IsTimeToRun(120, 120, 0);
	//IsTimeToRun(120, 140, 20); //motor ran
	//IsTimeToRun(130, 140, 10);
	//IsTimeToRun(220, 220, 0);
	//IsTimeToRun(260, 260, 0);
	//IsTimeToRun(340, 340, 0); //motor ran
	//IsTimeToRun(350, 360, 10);
	//IsTimeToRun(6, 10, 4); //power
	//IsTimeToRun(420, 420, 0);
	//IsTimeToRun(430, 440, 10);//motor ran
	//IsTimeToRun(440, 440, 0);

	//IsTimeToRun(6, 0, _runCountDown, 14, 14); //first run
	//IsTimeToRun(20, 0, _runCountDown, 20, 0);
	//IsTimeToRun(120, 0, _runCountDown, 120, 0);
	//IsTimeToRun(120, 120, _runCountDown, 140, 20); //motor ran
	//IsTimeToRun(130, 120, _runCountDown, 140, 10);
	//IsTimeToRun(220, 120, _runCountDown, 220, 0);
	//IsTimeToRun(260, 120, _runCountDown, 260, 0);
	//IsTimeToRun(340, 340, _runCountDown, 360, 20); //motor ran
	//IsTimeToRun(350, 340, _runCountDown, 360, 10);
	//IsTimeToRun(6, 340, _runCountDown, 16, 4); //power
	//IsTimeToRun(420, 340, _runCountDown, 440, 0);
	//IsTimeToRun(430, 430, _runCountDown, 450, 20);//motor ran
	//IsTimeToRun(440, 430, _runCountDown, 450, 10);
	

	//StaticUtils::DebugAddOne(_num);
	//Console::WriteLine(_num);

	//StaticUtils::DebugAddOne(6);
	////Console::WriteLine(num);
	//int b = StaticUtils::ReadIncomingByte();

	//int t = StaticUtils::TestAutoInt();
	//StaticUtils::Debug(t);

	////AClass::StaticMember = _num;
	//AClass::StaticMethod();

	//
	///*String^ runTime = ApiClassExt::GetRuntime();
	//runTime = ApiClassExt::GetRuntime();
	//StaticUtils::Debug(runTime);
	//ApiClassExt::PrintRuntime();*/

	////ApiClassTester apiClassTester;
	////apiClassTester.Test();
	//ApiClassExt ext;
	//String^ runTime = ext.GetRuntime();
	//runTime = ext.GetRuntime();
	//StaticUtils::Debug(runTime);
	//ext.PrintRuntime();

	//ApiClassTester::Test();

	system("pause");
	return 0;
}




