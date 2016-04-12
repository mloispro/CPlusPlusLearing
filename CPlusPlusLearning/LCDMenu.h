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
		ClockYear,
		ClockMonth,
		ClockDay,
		FeedHour,
		FeedMinute,
		FeedAmPm,
		FeedFrequency,
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

	//vector<LCDMenu> MenuItems; //dont work, fuck it!!!!!!!!!!

	LCDMenu(short id, short optionId, short nextMenuId, short prevMenuId, string text, string optionText, RangeType rangeType) :
		Id(id), OptionId(optionId), NextMenuId(nextMenuId), PrevMenuId(prevMenuId), Text(text), OptionText(optionText), TheRangeType(rangeType)
	{
		//MenuItems();
	}

};

#endif

