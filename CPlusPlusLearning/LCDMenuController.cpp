#include "LCDMenuController.h"

using namespace Controllers;

LCDMenuController::LCDMenuController()
{
	//_selectedMenu = LCDMenu();
	CreateMenus();
}
	

void LCDMenuController::AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, LCDMenu::RangeType rangeType, LCDMenu::MenuType menuType)
{
	LCDMenu menu(id, optionId, nextMenuId, prevMenuId, text, optionText, rangeType, menuType);
	_menus.push_back(menu);
}
void LCDMenuController::AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, LCDMenu::RangeType rangeType)
{
	AddMenu(id, optionId, nextMenuId, prevMenuId, text, optionText, rangeType, LCDMenu::MenuType::Main);
}


void LCDMenuController::CreateMenus()
{

	if (_menus.size() > 0)
		_menus.clear();

	//menus
	AddMenu(mainMenu, 0, feedMenu, mainMenu, "Menu: [>] Exit", "Feeder", LCDMenu::RangeType::Nav);
	AddMenu(mainMenu, 1, clockMenu, mainMenu, "Menu: [>] Exit", "Clock", LCDMenu::RangeType::Nav);

	//feed menus
	AddMenu(feedMenu, 0, feedTimeMenu, mainMenu, "Feeder: [<] Back", "Feed Time", LCDMenu::RangeType::Nav, LCDMenu::MenuType::Feeder);
	AddMenu(feedMenu, 1, feedFreqMenu, mainMenu, "Feeder: [<] Back", "Set Feed Time", LCDMenu::RangeType::Nav, LCDMenu::MenuType::Feeder);
	AddMenu(feedTimeMenu, 0, feedTimeMenu, feedMenu, "Feed Time: [<] Back", "Not Set", LCDMenu::RangeType::TimeFrequency, LCDMenu::MenuType::Feeder);
	AddMenu(feedFreqMenu, 0, feedHourMenu, feedMenu, "Feed Frequency: [<] Back", "Frequency", LCDMenu::RangeType::Frequency, LCDMenu::MenuType::Feeder);
	AddMenu(feedHourMenu, 0, feedMinMenu, feedFreqMenu, "Feed Hour: [<] Back", "Hour", LCDMenu::RangeType::Hour, LCDMenu::MenuType::Feeder);
	AddMenu(feedMinMenu, 0, feedAmPmMenu, feedHourMenu, "Feed Minute: [<] Back", "Minute", LCDMenu::RangeType::Minute, LCDMenu::MenuType::Feeder);
	AddMenu(feedAmPmMenu, 0, feedMenu, feedMinMenu, "Feed AM-PM: [<] Back", "AM PM", LCDMenu::RangeType::AmPm, LCDMenu::MenuType::Feeder);

	//clock menus
	AddMenu(clockMenu, 0, clockMenu, mainMenu, "Clock: [<] Back", "Time", LCDMenu::RangeType::TimeLong, LCDMenu::MenuType::Clock);
	AddMenu(clockMenu, 1, clockYearMenu, clockMenu, "Clock: [<] Back", "Set Clock Time", LCDMenu::RangeType::Nav, LCDMenu::MenuType::Clock);
	AddMenu(clockYearMenu, 0, clockMonthMenu, clockMenu, "Clock: [<] Back", "Year", LCDMenu::RangeType::Year, LCDMenu::MenuType::Clock);
	AddMenu(clockMonthMenu, 0, clockDayMenu, clockYearMenu, "Clock: [<] Back", "Month", LCDMenu::RangeType::Month, LCDMenu::MenuType::Clock);
	AddMenu(clockDayMenu, 0, clockMenu, clockMonthMenu, "Clock: [<] Back", "Day", LCDMenu::RangeType::Day, LCDMenu::MenuType::Clock);


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
String^ LCDMenuController::GetRangeOption(LCDMenu::RangeType rangeType)
{

	if (rangeType == LCDMenu::RangeType::Frequency)
	{
		LimitRange(0, 1);
		if (_optionCount <= 0)
		{
			return "Daily";
		}
		else if (_optionCount >= 1)
		{
			return "Every Other Day";
		}

	}
	else if (rangeType == LCDMenu::RangeType::Hour)
	{
		LimitRange(0, 12);
		//String hour = "01";
		String^ hour = "01";
		if (_optionCount <= _upperLimit && _optionCount >= _lowerLimit)
		{
			//hour = String(_optionCount);
			hour = System::Convert::ToString(_optionCount);
			if (_optionCount < 10)
				hour = "0" + hour;
		}
		return hour;
		//return StaticUtils::ParseString(hour);

	}
	else if (rangeType == LCDMenu::RangeType::Minute)
	{
		LimitRange(0, 59);

		String^ minute = "01";
		if (_optionCount <= _upperLimit && _optionCount >= _lowerLimit)
		{
			//hour = String(_optionCount);
			minute = System::Convert::ToString(_optionCount);
			if (_optionCount < 10)
				minute = "0" + minute;
		}
		return minute;
		//return StaticUtils::ParseString(minute);

	}
	else if (rangeType == LCDMenu::RangeType::AmPm)
	{
		LimitRange(0, 1);
		if (_optionCount <= 1)
			return "AM";
		else
			return "PM";
	}
	else if (rangeType == LCDMenu::RangeType::TimeFrequency)
	{
		//Daily, 08:30AM
		return "Get From RTC";
	}
	else if (rangeType == LCDMenu::RangeType::Year)
	{
		LimitRange(2016, 2050);
		String^ txt = "2016";
		if (_optionCount <= _upperLimit && _optionCount >= _lowerLimit)
		{
			//hour = String(_optionCount);
			txt = System::Convert::ToString(_optionCount);
		}
		return txt;
		//return StaticUtils::ParseString(txt);
	}
	else if (rangeType == LCDMenu::RangeType::Month)
	{
		LimitRange(1, 12);
		String^ txt = "01";
		if (_optionCount <= _upperLimit && _optionCount >= _lowerLimit)
		{
			//hour = String(_optionCount);
			txt = System::Convert::ToString(_optionCount);
			if (_optionCount < 10)
				txt = "0" + txt;
		}
		return txt;
		//return StaticUtils::ParseString(txt);
	}
	else if (rangeType == LCDMenu::RangeType::Day)
	{
		LimitRange(1, 31);
		String^ txt = "01";
		if (_optionCount <= _upperLimit && _optionCount >= _lowerLimit)
		{
			//hour = String(_optionCount);
			txt = System::Convert::ToString(_optionCount);
			if (_optionCount < 10)
				txt = "0" + txt;
		}
		return txt;
		//return StaticUtils::ParseString(txt);
	}
	else
		return "";


}

void LCDMenuController::SaveRangeOption(LCDMenu::RangeType rangeType, LCDMenu::MenuType menuType)
{
	//SerialExt::Debug("save", selectedMenu.OptionText);

	if (rangeType == LCDMenu::RangeType::Frequency &&
		menuType == LCDMenu::MenuType::Feeder)
	{
		if (_optionCount == 0) //Daily
		{
			RTCExt::SetFeedEvery(24);
		}
		else // ot day
		{
			RTCExt::SetFeedEvery(48);
		}
		
	}
	else if ((rangeType == LCDMenu::RangeType::Hour ||
		rangeType == LCDMenu::RangeType::Minute ||
		rangeType == LCDMenu::RangeType::AmPm) &&
		(menuType == LCDMenu::MenuType::Feeder))
	{
		RTCExt::SetFeedNextRun(_optionCount, rangeType);
	}
	else if (rangeType == LCDMenu::RangeType::TimeFrequency)
	{
		//Daily, 08:30AM
	}
	else if ((rangeType == LCDMenu::RangeType::Year ||
		rangeType == LCDMenu::RangeType::Month ||
		rangeType == LCDMenu::RangeType::Day ||
		rangeType == LCDMenu::RangeType::Hour ||
		rangeType == LCDMenu::RangeType::Minute) &&
		(menuType == LCDMenu::MenuType::Clock))
	{
		RTCExt::SetTimeTemp(_optionCount, rangeType);
	}
	else if (rangeType == LCDMenu::RangeType::AmPm &&
		menuType == LCDMenu::MenuType::Clock)
	{
		RTCExt::SetTimeTemp(_optionCount, rangeType);
		RTCExt::SetRTCTimeFromTemp();
	}
	
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

void LCDMenuController::PrintLine(short lineNum, String^ text)
{
	//T t(text);
	//_lcd.setCursor(0, lineNum);
	//_lcd.print(text);
	StaticUtils::WriteLine(text);
}


void LCDMenuController::PrintMenu(LCDMenu menu)
{
	/*SerialExt::Debug("menu", menu.Text);
	SerialExt::Debug("option", menu.OptionText);
	*/

	//auto menu = GetSelectedMenu();
	//String optionText = menu.OptionText;
	String^ optionText = StaticUtils::ParseString(menu.OptionText);
	
	String^ rangeOptionText = GetRangeOption(menu.TheRangeType);

	if (rangeOptionText != "")
	{
		optionText = rangeOptionText;
		//optionText = StaticUtils::ParseString(rangeOptionText);
	}

	StaticUtils::WriteLine(menu.Text);
	StaticUtils::WriteLine(optionText);

	//Clear();
	//PrintLine(0, menu.Text);
	//PrintLine(1, optionText);
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

void LCDMenuController::SelectMainMenu()
{
	//_accessingMenu = true;
	_selectedMenuId = 0;
	_selectedOptionId = 0;

	auto menu = GetSelectedMenu();
	PrintMenu(menu);

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

void LCDMenuController::LimitRange(int lower, int upper)
{
	_lowerLimit = lower;
	_upperLimit = upper;
	if (_optionCount <= lower)
	{
		_optionCount = lower; //limit
	}
	else if (_optionCount >= upper)
	{
		_optionCount = upper; //limit
	}
}

void LCDMenuController::NextOption()
{
	

	//bool optionChanged = false;
	if (_selectedOptionId >= 0)
	{
		short nextOptionId = _selectedOptionId + 1;
		auto nextMenu = GetMenu(_selectedMenuId, nextOptionId);
		if (nextMenu.Id == _selectedMenuId && nextMenu.OptionId == nextOptionId)
		{
			_selectedOptionId = nextOptionId;
			//optionChanged = true;
		}
	}

	auto selectedMenu = GetSelectedMenu();
	
	//if (selectedMenu.TheRangeType != LCDMenu::RangeType::Nav && selectedMenu.Changeable)
	//GetRangeOption(selectedMenu.TheRangeType);
	
	_optionCount++;
	PrintMenu(selectedMenu);

	
}



void LCDMenuController::PreviousOption()
{
	

	//bool optionChanged = false;
	if (_selectedOptionId > 0)
	{
		short prevOptionId = _selectedOptionId - 1;
		auto prevMenu = GetMenu(_selectedMenuId, prevOptionId);
		if (prevMenu.Id == _selectedMenuId && prevMenu.OptionId == prevOptionId)
		{
			_selectedOptionId = prevOptionId;
			//optionChanged = true;
		}
	}

	auto selectedMenu = GetSelectedMenu();

	
	//GetRangeOption(selectedMenu.TheRangeType);
	
	_optionCount--;
	PrintMenu(selectedMenu);
}


void LCDMenuController::LeftButton()
{
	//navigates back
	_optionCount = 0;
	auto selectedMenu = GetSelectedMenu();
	auto prevMenu = GetMenu(selectedMenu.PrevMenuId, 0);
	SetSelectedMenu(prevMenu);
	PrintMenu(prevMenu);
}




void LCDMenuController::SelectButton()
{
	
	auto selectedMenu = GetSelectedMenu();
	SaveRangeOption(selectedMenu.TheRangeType, selectedMenu.TheMenuType);
	_optionCount = 0;

	auto nextMenu = GetMenu(selectedMenu.NextMenuId, 0);
	SetSelectedMenu(nextMenu);
	PrintMenu(nextMenu);

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
		PreviousOption();
		break;
	case 2: //down
		NextOption();
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
void LCDMenuController::PrintTime()
{
	auto time = RTCExt::GetRTCTime();
	//auto theMonth = month(time);

	auto dateTimeString = RTCExt::GetShortDateTimeString(time);

	//SerialExt::Debug("dtStringp", dateTimeString);

	PrintLine(0, "Clock:");
	PrintLine(1, dateTimeString);
	//delay(_scrollDelay);
}
//template<typename T =void>
void LCDMenuController::PrintFeedInfo()
{
	for (int i = 0; i <= 3; i++)
	{
		RTCExt::UpdateNextFeed();

		String^ nextFeed;
		String^ lastFeed;
		String^ countDown;

		switch (i) {
		case 0:
			lastFeed = RTCExt::GetShortDateTimeString(RTCExt::NextFeedInfo.LastRun);

			PrintLine(0, "Last Feed:");
			PrintLine(1, lastFeed);
			break;
		case 1:
			countDown = RTCExt::GetTimeRemainingString(RTCExt::NextFeedInfo.CountDown);

			PrintLine(0, "Count Down:");
			PrintLine(1, countDown);
			break;
		case 2:
			nextFeed = RTCExt::GetShortDateTimeString(RTCExt::NextFeedInfo.NextRun);

			PrintLine(0, "Next Feed:");
			PrintLine(1, nextFeed);
			break;
		default:
			break;
		}
		//delay(_scrollDelay);
	}
}
