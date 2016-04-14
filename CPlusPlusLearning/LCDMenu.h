// SerialExt.h

#ifndef LCDMENU_h
#define LCDMENU_h

//#include <StandardCplusplus.h>
#include <string>
#include <vector>
using namespace std;

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

	enum MenuType
	{
		Main,
		Clock,
		Feeder,
		LiqDoser,
		DryDoser
	};

	short Id;
	short OptionId;
	short NextMenuId;
	short  PrevMenuId;
	string Text;
	string  OptionText;
	RangeType  TheRangeType;
	MenuType TheMenuType;

	//vector<LCDMenu> MenuItems; //dont work, fuck it!!!!!!!!!!

	LCDMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, RangeType rangeType, MenuType menuType) :
		Id(id), OptionId(optionId), NextMenuId(nextMenuId), PrevMenuId(prevMenuId), Text(text), OptionText(optionText), TheRangeType(rangeType), TheMenuType(menuType)
	{
		//MenuItems();
	}
	LCDMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, RangeType rangeType) :
		LCDMenu(id, optionId, nextMenuId, prevMenuId, text, optionText, rangeType, MenuType::Main)
	{
	}

};

#endif

