// SerialExt.h

#ifndef LCDEXT_h
#define LCDEXT_h

//#include "stdafx.h"
//#include <conio.h>
//#include <iostream>
//#include <msclr\marshal_cppstd.h>

#include "StaticUtils.h"
#include "RTCExt.h"
using namespace Utils;

//#include <StandardCplusplus.h>
#include <string>
#include <vector>
using namespace std;

//using namespace System;

//#include <LCDMenu.h>
#include "LCDMenu.h"
//#include "DigitalTime.h"

//using namespace Models;

namespace Controllers {

	class LCDMenuController{
	private:
		//using namespace Utils;
		const short mainMenu = 0;
		const short feedMenu = 1;
		const short feedFreqMenu = 2;
		const short feedHourMenu = 3;
		const short feedMinMenu = 4;
		const short feedAmPmMenu = 5;
		const short clockMenu = 6;
		const short clockYearMenu = 7;
		const short clockMonthMenu = 8;
		const short clockDayMenu = 9;
		const short feedTimeMenu = 10;
		const short clockHourMenu = 11;
		const short clockMinMenu = 12;
		const short clockAmPmMenu = 13;
		const short doserMenu = 14;
		const short doserFreqMenu = 15;
		const short doserHourMenu = 16;
		const short doserMinMenu = 17;
		const short doserAmPmMenu = 18;
		const short doserTimeMenu = 19;

		vector<LCDMenu> _menus;
		
		short _selectedMenuId = -1;
		short _selectedOptionId = -1;
		
		int _lowerLimit;
		int _upperLimit;

		//--key press
		/*int _keyValues[5];
		int _numOfKeys = 5;*/
		int GetKeyFromVal(unsigned int input);
		int GetKey();
		void NextOption();
		void PreviousOption();
		void LeftButton();
		void SelectButton();
		void LimitRange(int lower, int upper);
		void DetectKeyPress();

		LCDMenu GetMenu(short id, short optionId);
		void PrintMenu(LCDMenu menu);
		void PrintLine(short lineNum, String^ text);
		void SetSelectedMenu(LCDMenu menu);

		void AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, LCDMenu::RangeType rangeType);
		void AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, LCDMenu::RangeType rangeType, AccessoryType accType);
		void CreateMenus();
		LCDMenu GetSelectedMenu();

		//LiquidCrystal _lcd(8, 9, 4, 5, 6, 7);
		
	public:
		int _optionCount;

		LCDMenuController();
		
		String^ GetRangeOption(LCDMenu::RangeType rangeType, AccessoryType accType);
		void SaveRangeOption(LCDMenu::RangeType rangeType, AccessoryType accType);
		
		void SelectMainMenu();
		void ExitMainMenu();
		
		void PrintRunInfo(AccessoryType accType);
		void PrintTime();
		String^ GetTimeFrequency(AccessoryType accType);
		String^ GetTimeLong(AccessoryType accType);

	};
}

#endif

