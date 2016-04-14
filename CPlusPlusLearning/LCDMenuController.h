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

		int _lowerLimit;
		int _upperLimit;

		int _keyValues[5];
		int _numOfKeys = 5;
		vector<LCDMenu> _menus;
		
		short _selectedMenuId = -1;
		short _selectedOptionId = -1;
		
		//LiquidCrystal _lcd(8, 9, 4, 5, 6, 7);
		
		void LimitRange(int lower, int upper);

	public:
		int _optionCount;

		LCDMenuController();
		LCDMenu GetSelectedMenu();
		void SetSelectedMenu(LCDMenu menu);
		void PrintLine(short lineNum, String^ text);
		void AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, LCDMenu::RangeType rangeType);
		void AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, LCDMenu::RangeType rangeType, LCDMenu::MenuType menuType);
		String^ GetRangeOption(LCDMenu::RangeType rangeType, LCDMenu::MenuType menuType);
		void SaveRangeOption(LCDMenu::RangeType rangeType, LCDMenu::MenuType menuType);
		
		void CreateMenus();

		//--Menu functions
		LCDMenu GetMenu(short id, short optionId);

		void PrintMenu(LCDMenu menu);

		void SelectMainMenu();
		void ExitMainMenu();

		////--key press
		int GetKeyFromVal(unsigned int input);
		int GetKey();
		
		void NextOption();
		void PreviousOption();
		void LeftButton();
		
		void SelectButton();
		void CheckIfKeyPressed();
		void PrintRunInfo(LCDMenu::MenuType menuType);
		void PrintTime();
		String^ GetTimeFrequency(LCDMenu::MenuType menuType);
		String^ GetTimeLong(LCDMenu::MenuType menuType);

	};
}
//template<typename T = void>
//void Clear()
//{
//	_lcd.clear();
//}


#endif

