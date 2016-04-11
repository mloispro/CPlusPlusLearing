// SerialExt.h

#ifndef LCDEXT_h
#define LCDEXT_h

//#include "stdafx.h"
//#include <conio.h>
//#include <iostream>
//#include <msclr\marshal_cppstd.h>

#include "StaticUtils.h"
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

		//bool _accessingMenu = false;
		//bool _menuChanged = false;

		int _keyValues[5];
		int _numOfKeys = 5;
		vector<LCDMenu> _menus;
		
		short _selectedMenuId = -1;
		short _selectedOptionId = -1;
		string _rangeOptionText;
		int _optionCount;
		//LiquidCrystal _lcd(8, 9, 4, 5, 6, 7);
		
		/*int CurrentMenuIndex;
		int CurrentMenuItemIndex;
		int _oldMenuItemIndex = -1;*/

	public:
		
		LCDMenuController();
		
		LCDMenu GetSelectedMenu();
		void SetSelectedMenu(LCDMenu menu);
		//template<typename T>
		void PrintLine(short lineNum, string text);
		void AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, LCDMenu::RangeType rangeType);
		void CreateMenus();

		//--Menu functions
		LCDMenu GetMenu(short id, short optionId);

		void PrintMenu();

		void SelectMainMenu();
		void ExitMainMenu();

		////--key press
		int GetKeyFromVal(unsigned int input);
		int GetKey();
		void GetRangeOption();
		void NextOption();
		void DownButton();
		void PreviousOption();
		void UpButton();
		void LeftButton();
		void SaveRangeOption(LCDMenu::RangeType rangeType);
		void SelectButton();
		void CheckIfKeyPressed();

	};
}
//template<typename T = void>
//void Clear()
//{
//	_lcd.clear();
//}

/*int GetSize()
{
return MenuItems.size();
}*/
////template<typename T = void>
////void PrintMenu()
////{
////	SerialExt::Debug("PrintMenu1");
////	if (!_menuChanged)
////		return;

////	_menuChanged = false;

////	SerialExt::Debug("PrintMenu2");

////	LCDMenu menu = GetSelectedMenu();
////	
////	SerialExt::Debug("menu", menu.Text);
////	SerialExt::Debug("option", menu.OptionText);

////	Clear();
////	PrintLine(0, menu.Text);
////	PrintLine(1, menu.OptionText);
////}
////template<typename T = void>
////void SelectMenuOption()
////{
////	
////	auto& selectedMenu = GetSelectedMenu();
////	LCDMenu& nextMenu = Menus[selectedMenu.NextMenuId];

////	selectedMenu.IsSelected = false;
////	nextMenu.IsSelected = true;
////	_menuChanged = true;
////
////}

#endif

