// SerialExt.h

#ifndef LCDMENU_h
#define LCDMENU_h

//#include <StandardCplusplus.h>
#include <string>
#include <vector>
using namespace std;

#include "StaticUtils.h"
using namespace Utils;

//menu:0 item:0 nextMenu:1 menuText:Menu itemText:Feeder rangeType:None isSelected:true

class LCDMenu
{

public:
	enum RangeType
	{
		Nav,
		Year,
		Month,
		Day,
		Hour,
		Minute,
		AmPm,
		Frequency,
		TimeLong,
		TimeShort,
		TimeFrequency,
	};



	short Id;
	short OptionId;
	short NextMenuId;
	short  PrevMenuId;
	string Text;
	string  OptionText;
	RangeType  TheRangeType;
	AccessoryType AccType;

	//vector<LCDMenu> MenuItems; //dont work, fuck it!!!!!!!!!!

	LCDMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, RangeType rangeType, AccessoryType accType) :
		Id(id), OptionId(optionId), NextMenuId(nextMenuId), PrevMenuId(prevMenuId), Text(text), OptionText(optionText), TheRangeType(rangeType), AccType(accType)
	{
		//MenuItems();
	}
	LCDMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, RangeType rangeType) :
		LCDMenu(id, optionId, nextMenuId, prevMenuId, text, optionText, rangeType, AccessoryType::None)
	{
	}

};

#endif

