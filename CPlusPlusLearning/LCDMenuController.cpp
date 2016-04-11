#include "LCDMenuController.h"

using namespace Controllers;

LCDMenuController::LCDMenuController()
{
	//_selectedMenu = LCDMenu();
	CreateMenus();
}
	


void LCDMenuController::PrintLine(short lineNum, string text)
{
	//T t(text);
	//_lcd.setCursor(0, lineNum);
	//_lcd.print(text);
	StaticUtils::WriteLine(text);
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


void LCDMenuController::AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, LCDMenu::RangeType rangeType)
{
	//R r(rangeType);
	LCDMenu menu(id, optionId, nextMenuId, prevMenuId, text, optionText, rangeType);
	_menus.push_back(menu);

}


void LCDMenuController::CreateMenus()
{

	if (_menus.size() > 0)
		_menus.clear();

	//menus
	AddMenu(mainMenu, 0, feedMenu, mainMenu, "Menu: [>] Exit", "Feeder", LCDMenu::RangeType::Nav);
	AddMenu(mainMenu, 1, clockMenu, mainMenu, "Menu: [>] Exit", "Clock", LCDMenu::RangeType::Nav);

	//feed menus
	AddMenu(feedMenu, 0, feedMenu, mainMenu, "Feedings: [<] Back", "Feed Time", LCDMenu::RangeType::TimeFrequency);
	AddMenu(feedMenu, 1, feedFreqMenu, mainMenu, "Feedings: [<] Back", "Set Feed Time", LCDMenu::RangeType::Nav);
	AddMenu(feedFreqMenu, 0, feedHourMenu, feedMenu, "Feeding: [<] Back", "Frequency", LCDMenu::RangeType::FeedFrequency);
	AddMenu(feedHourMenu, 0, feedMinMenu, feedFreqMenu, "Feeding: [<] Back", "Hour", LCDMenu::RangeType::FeedHour);
	AddMenu(feedMinMenu, 0, feedAmPmMenu, feedHourMenu, "Feeding: [<] Back", "Minute", LCDMenu::RangeType::FeedMinute);
	AddMenu(feedAmPmMenu, 0, feedMenu, feedMinMenu, "Feeding: [<] Back", "AM PM", LCDMenu::RangeType::FeedAmPm);

	//clock menus
	AddMenu(clockMenu, 0, clockMenu, mainMenu, "Clock: [<] Back", "Time", LCDMenu::RangeType::TimeLong);
	AddMenu(clockMenu, 1, clockYearMenu, clockMenu, "Clock: [<] Back", "Set Clock Time", LCDMenu::RangeType::Nav);
	AddMenu(clockYearMenu, 0, clockMonthMenu, clockMenu, "Clock: [<] Back", "Year", LCDMenu::RangeType::ClockYear);
	AddMenu(clockMonthMenu, 0, clockDayMenu, clockYearMenu, "Clock: [<] Back", "Month", LCDMenu::RangeType::ClockMonth);
	AddMenu(clockDayMenu, 0, clockMenu, clockMonthMenu, "Clock: [<] Back", "Day", LCDMenu::RangeType::ClockDay);


	//currentMenu:0
	//currentItem:1

	//currentMenu:1
	//currentItem:0

	//currentMenu:1
	//currentItem:1

	//[menus]
	//Menu, Feeder 				menu:0 item:0 nextMenu:1 menuText:Menu itemText:Feeder rangeType:None isSelected:true
	//Menu, Clock 				menu:0 item:1 nextMenu:5 menuText:Menu itemText:Clock rangeType:None isSelected:false
	//Feeder, Feed Time 		menu:1 item:0 nextMenu:0 itemText:Feed Time rangeType:None isSelected:false
	//Feeder, Set Feed Time 	menu:1 item:1 nextMenu:2 itemText:Set Feed Time rangeType:None isSelected:false
	//Feed Frequency, Daily 	menu:2 item:0 nextMenu:3 itemText:Daily rangeType:FeedFrequency isSelected:false
	//Feed Frequency, EO Day 	menu:2 item:1 nextMenu:3 itemText:Every Other Day rangeType:FeedFrequency isSelected:false
	//Feed Hour, 06:00 AM 		menu:3 item:0 nextMenu:4 itemText:06:00 AM rangeType:Hour isSelected:false
	//Feed Minute, 06:00 AM     menu:4 item:0 nextMenu:1 itemText:06:00 AM rangeType:Minute isSelected:false
	//Clock, Clock Time 		menu:5 item:0 nextMenu:0 itemText:Clock Time rangeType:None isSelected:false
	//Clock, Set Clock Time 	menu:5 item:1 nextMenu:6 itemText:Set Clock Time rangeType:None isSelected:false
	//Clock Year, 2016 			menu:6 item:0 nextMenu:7 itemText:2016 rangeType:Year isSelected:false
	//Clock Month, 04 			menu:7 item:0 nextMenu:8 itemText:04 rangeType:Month isSelected:false
	//Clock Day, 09 			menu:8 item:0 nextMenu:-1 itemText:09 rangeType:Day isSelected:false


}


	//--Menu functions

	//get by ref example
	//auto&& menu = GetMenu(5);
LCDMenu LCDMenuController::GetMenu(short id, short optionId)
{
	auto selectedMenu = _menus[0];
	for (auto menu : _menus)
	{
		if (menu.Id == id && menu.OptionId == optionId)
		{
			return menu;
		}
	}

	return selectedMenu;

}
LCDMenu LCDMenuController::GetSelectedMenu()
{
	auto selectedMenu = GetMenu(_selectedMenuId, _selectedOptionId);
	return selectedMenu;
}

void LCDMenuController::SetSelectedMenu(LCDMenu menu)
{
	_selectedMenuId = menu.Id;
	_selectedOptionId = menu.OptionId;

}


void LCDMenuController::PrintMenu()
{
	/*SerialExt::Debug("menu", menu.Text);
	SerialExt::Debug("option", menu.OptionText);
	*/

	auto menu = GetSelectedMenu();
	//String optionText = menu.OptionText;
	String^ optionText = StaticUtils::ParseString(menu.OptionText);
	
	if (_rangeOptionText != "")
	{
		//optionText = _rangeOptionText;
		optionText = StaticUtils::ParseString(_rangeOptionText);
	}

	StaticUtils::WriteLine(menu.Text);
	StaticUtils::WriteLine(optionText);

	//Clear();
	//PrintLine(0, menu.Text);
	//PrintLine(1, menu.OptionText);
}



void LCDMenuController::SelectMainMenu()
{
	//_accessingMenu = true;
	_selectedMenuId = 0;
	_selectedOptionId = 0;
	PrintMenu();
	while (_selectedMenuId > -1)
	{
		CheckIfKeyPressed();
		//delay(1000);
		System::Threading::Thread::Sleep(1000);
	}
}

void LCDMenuController::ExitMainMenu()
{
	//_accessingMenu = false;
	_selectedMenuId = -1;
	_selectedOptionId = -1;
}

//--key press
int LCDMenuController::GetKeyFromVal(unsigned int input) {
	//int k;
	//for (k = 0; k < _numOfKeys; k++)
	//{
	//	if (input < _keyValues[k])
	//	{
	//		return k;
	//	}
	//}
	//if (k >= _numOfKeys) k = -1;
	//return k;
	return 0;
}

int LCDMenuController::GetKey()
{
	//int keyVal = analogRead(0);
	//SerialExt::Debug("keyVal", keyVal);
	//int key = GetKeyFromVal(keyVal);
	//SerialExt::Debug("key", key);
	
	int key = StaticUtils::ReadKey();

	return key;
}

void LCDMenuController::GetRangeOption()
{
	auto selectedMenu = GetSelectedMenu();

	switch (selectedMenu.TheRangeType)
	{
	case LCDMenu::RangeType::FeedFrequency:
	{
		//auto nextMenuOption(selectedMenu);
		if (_optionCount <= 1)
			_rangeOptionText = "Daily";
		else
			_rangeOptionText = "Every Other Day";
		//return nextMenuOption;

	}
	break;
	case LCDMenu::RangeType::FeedHour:
	{
		//String hour = "01";
		String^ hour = "01";
		if (_optionCount <= 12 && _optionCount >= 1)
		{
			//hour = String(_optionCount);
			hour = System::Convert::ToString(_optionCount);
			if (_optionCount < 10)
				hour = "0" + hour;
		}
		/*_rangeOptionText = hour;*/
		_rangeOptionText = StaticUtils::ParseString(hour);

	}
	break;
	case LCDMenu::RangeType::FeedMinute:
	{
		//todo get feed time from RTC..
		String^ minute = "01";
		if (_optionCount <= 59 && _optionCount >= 1)
		{
			//hour = String(_optionCount);
			minute = System::Convert::ToString(_optionCount);
			if (_optionCount < 10)
				minute = "0" + minute;
		}
		/*_rangeOptionText = hour;*/
		_rangeOptionText = StaticUtils::ParseString(minute);

	}
	break;
	case LCDMenu::RangeType::FeedAmPm:
	{
		if (_optionCount <= 1)
			_rangeOptionText = "AM";
		else
			_rangeOptionText = "PM";
	}
	break;
	case LCDMenu::RangeType::TimeFrequency:
	{
		//Daily, 08:30AM
		_rangeOptionText = "Get From RTC";
	}
	break;
	default:
		_rangeOptionText = "";
		break;
	}

	//return selectedMenu;
}


void LCDMenuController::NextOption()
{
	if (_selectedOptionId >= 0)
	{
		short nextOptionId = _selectedOptionId + 1;
		auto nextMenu = GetMenu(_selectedMenuId, nextOptionId);
		if (nextMenu.Id == _selectedMenuId && nextMenu.OptionId == nextOptionId)
			_selectedOptionId = nextOptionId;
		//else
		//	_selectedOptionId = 0;
	}

	auto selectedMenu = GetSelectedMenu();
	
	if (selectedMenu.TheRangeType != LCDMenu::RangeType::Nav)
		GetRangeOption();

	//_selectedMenuId = nextOption.Id;
	//return nextOption;
}

void LCDMenuController::DownButton()
{
	_optionCount++;
	NextOption();
	PrintMenu();

}

void LCDMenuController::PreviousOption()
{
	if (_selectedOptionId > 0)
	{
		short prevOptionId = _selectedOptionId - 1;
		auto prevMenu = GetMenu(_selectedMenuId, prevOptionId);
		if (prevMenu.Id == _selectedMenuId && prevMenu.OptionId == prevOptionId)
			_selectedOptionId = prevOptionId;
		//else
		//	_selectedOptionId = 0;
	}

	auto selectedMenu = GetSelectedMenu();

	if (selectedMenu.TheRangeType != LCDMenu::RangeType::Nav)
		GetRangeOption();
	
}

void LCDMenuController::UpButton()
{
	_optionCount--;
	PreviousOption();
	PrintMenu();
}

void LCDMenuController::LeftButton()
{
	//navigates back
	_optionCount = 0;
	auto selectedMenu = GetSelectedMenu();
	auto prevMenu = GetMenu(selectedMenu.PrevMenuId, 0);
	SetSelectedMenu(prevMenu);
	PrintMenu();
}

void LCDMenuController::SaveRangeOption(LCDMenu::RangeType rangeType)
{
	//SerialExt::Debug("save", selectedMenu.OptionText);
	

	switch (rangeType)
	{
	case LCDMenu::RangeType::FeedFrequency:
	{
		if (_rangeOptionText == "Daily")
		{
			//save to eeprom
		}
		break;
	}
	case LCDMenu::RangeType::FeedHour:
	{

		break;
	}
	case LCDMenu::RangeType::FeedMinute:
	{
		break;
	}
	case LCDMenu::RangeType::FeedAmPm:
	{
		break;
	}
	case LCDMenu::RangeType::TimeFrequency:
	{
		//Daily, 08:30AM
		break;
	}
	default:
		break;
	}

	//return selectedMenu;
}


void LCDMenuController::SelectButton()
{
	_optionCount = 0;
	auto selectedMenu = GetSelectedMenu();

	//save to eeporm
	if (selectedMenu.TheRangeType != LCDMenu::RangeType::Nav)
		SaveRangeOption(selectedMenu.TheRangeType);

	_selectedMenuId = selectedMenu.NextMenuId;
	_selectedOptionId = 0;

	PrintMenu();
}


void LCDMenuController::CheckIfKeyPressed()
{
	int key = GetKey();
	//SerialExt::Debug("key:", key);

	//LCDMenu currentMenu = LCDExt::GetCurrentMenu();
	//LCDMenuItem currentMenuItem = LCDExt::GetCurrentMenuItem();
	//
	//SerialExt::Debug("currentMenuIndex", LCDExt::CurrentMenuIndex);

	//SerialExt::Debug("cm", currentMenu.Text);
	//SerialExt::Debug("mi", currentMenuItem.Text);

	//PrintMenu();

	switch (key) {
	case 0: //right
		ExitMainMenu();
		break;
	case 1: //up
		UpButton();
		break;
	case 2: //down
		DownButton();
		break;
	case 3: //left
		LeftButton();
		break;
	case 4: //select
		SelectButton();
		break;
	default:
		break;

	}
}