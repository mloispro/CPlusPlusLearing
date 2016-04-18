#ifndef RTCEXT_h
#define RTCEXT_h

#include <inttypes.h>
#include <sys/types.h>
#include <time.h> 

//#include <StandardCplusplus.h>
#include <string>
#include <vector>
using namespace std;


using namespace System;


namespace Utils {


	//--dont copy to EAL--
	struct NextRunMemory{
		long LastRun;
		long NextRun;
		long CountDown;
		long RunEvery;
		
	};


	class DigitalTime{

	public:
		int Hours;
		int Minutes;
		int Seconds;
		short Day;
		short Month;
		short Year;

		DigitalTime(int hours, int minutes, int seconds) : Hours(hours), Minutes(minutes), Seconds(seconds){}
	};

	//struct tmElements_t{
	//	
	//	uint32_t Hour;
	//	uint32_t Minute;
	//	uint32_t Second;
	//	uint32_t Day;
	//	uint32_t Month;
	//	uint32_t Year;
	//	uint32_t Wday;
	//};

	////remeber: dependant functions must be defined first in namespace.
	///**Better to use template functions.
	namespace RTCExt{

		//static bool _initalized;
		static NextRunMemory NextFeedInfo;
		static NextRunMemory NextDoseInfo;

		//--dont copy to EAL-->
#pragma region EAL_DONT_COPY
		
#define LEAP_YEAR(Y)     ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )

		static  const uint8_t monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // API starts months from 1, this array starts from 0
		static int SECS_PER_MIN = 60;
		static int SECS_PER_HOUR = 3600;
		static int SECS_PER_DAY = 86400;

		//#define minutesToTime_t ((M)) ( (M) * SECS_PER_MIN)  
		//#define hoursToTime_t   ((H)) ( (H) * SECS_PER_HOUR)  
		//#define daysToTime_t    ((D)) ( (D) * SECS_PER_DAY) // fixed on Jul 22 2011

		static time_t _rtcTime;
		template<typename T = void>
		int now()
		{
			//int now = System::DateTime::Now.Millisecond;

			//time_t t = time(NULL);
			//tm* timePtr = localtime(&t);

			time_t t = time(NULL); //gets current time
			/*	struct tm * timeinfo;

			time(&now);
			timeinfo = localtime(&now);*/

			if (_rtcTime != 0){
				return _rtcTime;
			}

			return t;
		}

		template<typename T = void>
		int day(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr, &time);
			return timePtr.tm_mday;
		}
		template<typename T = void>
		int month(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr, &time);
			return timePtr.tm_mon + 1;
		}
		template<typename T = void>
		int year(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr, &time);
			return timePtr.tm_year + 1900;
		}
		template<typename T = void>
		int second(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr, &time);
			return timePtr.tm_sec;
		}
		template<typename T = void>
		int minute(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr, &time);
			return timePtr.tm_min;
		}
		template<typename T = void>
		int hour(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr, &time);
			return timePtr.tm_hour;
		}
		template<typename T = void>
		int hourFormat12(time_t t) { // the hour for the given time in 12 hour format

			if (hour(t) == 0)
				return 12; // 12 midnight
			else if (hour(t) > 12)
				return hour(t) - 12;
			else
				return hour(t);
		}
		template<typename T = void>
		bool isAM(time_t t) { // returns true if given time is AM
			return !isPM(t);
		}
		template<typename T = void>
		bool isPM(time_t t) { // returns true if PM
			return (hour(t) >= 12);
		}
		
		template<typename T = void>
		void SetRTCTime(int theHour, int theMinute, int theSecond, int theDay, int theMonth, int theYear)
		{
			//12/31/2025 12:59PM
			//!12/31/2025 11:59AM
			int hourAdd = 0;
			if (theHour < 12){
				hourAdd = 1;
			}

			time_t t = time(NULL);
			tm timePtr;
			localtime_s(&timePtr, &t);
			timePtr.tm_hour = theHour + hourAdd;
			timePtr.tm_min = theMinute;
			timePtr.tm_sec = theSecond;
			timePtr.tm_mday = theDay;
			timePtr.tm_mon = theMonth - 1;
			timePtr.tm_year = theYear - 1900;
			
			_rtcTime = mktime(&timePtr);

			

			//setTime(theHour, theMinute, theSecond, theDay, theMonth, theYear);
			
			//RTC.set(now());

			//todo:remove
			//String^ t2 = GetShortDateTimeString(_rtcTime); //01/23/2024 12:54AM, !01/22/2024 11:54PM, !02/23/2024 11:54AM

		}
		template<typename T = void>
		time_t GetRTCTime()
		{
			return now();
		}
#pragma endregion EAL_DONT_COPY
		//<--dont copy to EAL--

		static DigitalTime _timeTemp(0, 0, 0);

		template<typename H = int, typename M = int, typename S = int>
		String^ FormatDigialTime(H&& hours, M&& minutes, S&& seconds)
		{
			H convH(hours);
			M convM(minutes);
			S convS(seconds);

			String^ hourString = hours.ToString();
			if (hours < 10)
				hourString = "0" + hourString;
			String^ minString = minutes.ToString();
			if (minutes < 10)
				minString = "0" + minString;
			//String secString = String(seconds);
			//if (seconds < 10)
			//	secString = "0" + secString;

			//String timeString = String(hours) + ":";
			String^ timeString = hourString + ":";
			timeString += minString; //+":";
			//timeString += secString;

			return timeString;
		}
		template<typename T = DigitalTime>
		String^ FormatDigialTime(T&& time){

			T conv(time);
			String^ timeString = FormatDigialTime(time.Hours, time.Minutes, time.Seconds);

			return timeString;
		}
		template<typename T = time_t>
		DigitalTime GetDigitalTime(T&& seconds){
			T conv(seconds);

			int h, m, s;
			s = second(seconds); //seconds;
			m = minute(seconds);
			h = hourFormat12(seconds);

			DigitalTime time = DigitalTime(h, m, s);

			return time;
		}
		template<typename T = time_t>
		String^ GetDigitalTimeString(T&& seconds){
			T conv(seconds);

			DigitalTime time = GetDigitalTime(seconds);

			String^ runTime = FormatDigialTime(time);
			return runTime;
		}
		template<typename T = time_t>
		String^ GetMonthAndDateString(T&& seconds){
			T conv(seconds);

			String^ theDate;

			int theDay = day(seconds);
			int theMonth = month(seconds);
			int theYear = year(seconds);

			//SerialExt::Debug("theDay", theDay);

			String^ dayString = theDay.ToString();
			if (theDay < 10)
				dayString = "0" + dayString;
			String^ monthString = theMonth.ToString();
			if (theMonth < 10)
				monthString = "0" + monthString;
			String^ yearString = theYear.ToString();
			//yearString..Remove(0, 2);

			theDate = monthString + "/" + dayString + "/" + yearString;

			return theDate;
		}
		//returns digital date & time ##/##/#### ##:##:##
		template<typename T = time_t>
		String^ GetShortDateTimeString(T&& seconds){
			T conv(seconds);

			String^ result;

			String^ theDate = GetMonthAndDateString(seconds);
			String^ theTime = GetDigitalTimeString(seconds);

			result = theDate + " " + theTime;

			String^ am = "AM";
			if (isPM(seconds))
				am = "PM";

			result += am;

			return result;

		}

		template<typename T = void>
		bool IsRTCTimeSet()
		{
			auto time = GetRTCTime();
			auto theYear = year(time);
			if (theYear < 2016)return false;
			return true;
		}
		template<typename T = AccessoryType>
		NextRunMemory& FindNextRunInfo(T&& accType){
			if (accType == AccessoryType::Feeder)
				return NextFeedInfo;
			else if (accType == AccessoryType::DryDoser)
				return NextDoseInfo;
		}

		template<typename T = AccessoryType>
		void UpdateNextRun(T&& accType){

			auto rtcTime = GetRTCTime();
			NextRunMemory& nextRunMem = FindNextRunInfo(accType);

			int runEvery = 0;
			int countDown = 0;
			int nextRun = 0;
			int lastRun = 0;
			
			runEvery = nextRunMem.RunEvery;
			countDown = nextRunMem.CountDown;
			nextRun = nextRunMem.NextRun;
			lastRun = nextRunMem.LastRun;

			//auto runev = GetDigitalTimeString(runEvery);
			////StaticUtils::Debug(runEvery);
			//StaticUtils::WriteLine("runEvery");
			//StaticUtils::Debug(runev);
			//StaticUtils::WriteLine("rtcTime");
			//StaticUtils::Debug(rtcTime);
			

			if (!IsRTCTimeSet() || runEvery == 0)
				return;// rtcTime;

			//auto rtc = GetShortDateTimeString(rtcTime);
			//auto nr = GetShortDateTimeString(nextRun);
			//auto cd = GetTimeRemainingString(countDown);
			//auto re = GetTimeRemainingString(runEvery);

			if (lastRun == 0) //before first feeding
				lastRun = rtcTime;

			if (lastRun > rtcTime)
				lastRun = rtcTime;

			if (nextRun <= 0)
				nextRun = rtcTime + runEvery; //08:51:49

			if (lastRun > 0 && nextRun <= rtcTime)
				nextRun = lastRun + runEvery;
			
			countDown = nextRun - rtcTime; //00:00:06

			if (nextRun <= rtcTime){
				nextRun = rtcTime;
				countDown = 0;
			}
			
		/*	auto nr2 = GetShortDateTimeString(nextRun);
			auto cd2 = GetTimeRemainingString(countDown);
			auto re2 = GetTimeRemainingString(runEvery);*/
			
			nextRunMem.RunEvery = runEvery;
			nextRunMem.CountDown = countDown;
			nextRunMem.NextRun = nextRun;
			nextRunMem.LastRun = lastRun;

		}

		template<typename T=void>
		bool IsTimeToRun(AccessoryType accType){
			
			NextRunMemory& nextRunMem = FindNextRunInfo(accType);
			if (nextRunMem.RunEvery <= 0)return true; //not using rtc

			time_t runTime = RTCExt::GetRTCTime();
			UpdateNextRun(accType);
			time_t nextRun = nextRunMem.NextRun;
			//int runTime = TimerExt::GetRuntimeInSeconds();
			if (nextRun <= runTime){
				return true;
			}
			return false;
		}

		template<typename T=void>
		long ConvHoursToSec(int hour)
		{
			//T t(hour);
			long sec = (long)(hour * SECS_PER_HOUR);
			return sec;
		}
		template<typename T = void>
		int ConvSecToHour(long seconds)
		{
			//T t(hour);
			int h = (int)(seconds / SECS_PER_HOUR);
			return h;
		}

		template<typename T = long, typename N = long>
		String^ GetTimeFrequencyString(T&& runEvery, N&& nextRun)
		{
			String^ freq = "";

			String^ am = "AM";
			if (isPM(nextRun))
				am = "PM";

			String^ theTime = GetDigitalTimeString(nextRun);
			theTime = theTime + am;

			int h = ConvSecToHour(runEvery);

			if (h == 24)
				freq = ", Daily";
			else if (h = 48)
				freq = ", Every Other Day";
			
			String^ freqTime = theTime + freq;
			return freqTime;
		}

		template<typename T = long, typename M = AccessoryType>
		void SetRunEvery(T&& hour, M&& accType)
		{
			T t(hour);
			auto sec = ConvHoursToSec(hour);
			NextRunMemory& nextRunMem = FindNextRunInfo(accType);

			nextRunMem.RunEvery = sec;
			nextRunMem.NextRun = 0; //need to set to 0 so it recalculates

			UpdateNextRun(accType);
		}
		template<typename T=void>
		void SetRTCTimeFromTemp()
		{
			SetRTCTime(_timeTemp.Hours, _timeTemp.Minutes, _timeTemp.Seconds, _timeTemp.Day, _timeTemp.Month, _timeTemp.Year);
		}

		template<typename T, typename M = LCDMenu::RangeType>
		void SetTimeTemp(T&& val, M&& rangeType)
		{
			T t(val);

			//TODO: remove
			DigitalTime dt(0, 0, 0);

			if (rangeType == LCDMenu::RangeType::Year)
				_timeTemp.Year = val;
			else if (rangeType == LCDMenu::RangeType::Month)
				_timeTemp.Month = val;
			else if (rangeType == LCDMenu::RangeType::Day)
				_timeTemp.Day = val;
			else if (rangeType == LCDMenu::RangeType::Hour)
				_timeTemp.Hours = val;
			else if (rangeType == LCDMenu::RangeType::Minute)
				_timeTemp.Minutes = val;
			else if (rangeType == LCDMenu::RangeType::AmPm)
			{
				
				if (val == 0 && _timeTemp.Hours == 12) // val = 0->AM
					_timeTemp.Hours = 0;
				else if (val == 1 && _timeTemp.Hours == 12) // val = 1->PM
					_timeTemp.Hours = 23;
				else if (val == 1 && _timeTemp.Hours < 12)// val = 1->PM
					_timeTemp.Hours = _timeTemp.Hours + 12;
			}
		}
		template<typename T, typename M = LCDMenu::RangeType, typename P = AccessoryType>
		void SetNextRun(T&& val, M&& rangeType, P&& accType)
		{
			T t(val);
			M m(rangeType);
			P p(accType);

			tm timePtr;
			time_t nrTime;

			NextRunMemory& nextRunMem = FindNextRunInfo(accType);
			nrTime = time_t(nextRunMem.NextRun);

			localtime_s(&timePtr, &nrTime);

			if (rangeType == LCDMenu::RangeType::Minute)
				timePtr.tm_min = val;
			else if (rangeType == LCDMenu::RangeType::Hour)
				timePtr.tm_hour = val;
			else if (rangeType == LCDMenu::RangeType::AmPm)
			{
				int tmHour = timePtr.tm_hour;
			
				if (val == 0 && timePtr.tm_hour > 12) //AM
					timePtr.tm_hour = timePtr.tm_hour - 12;
				else if (val == 1 && timePtr.tm_hour < 12)//PM
					timePtr.tm_hour = timePtr.tm_hour + 12;
			}
			else
				return;

			auto newNrTime = mktime(&timePtr);

			nextRunMem.NextRun = newNrTime;

			UpdateNextRun(accType);
		}
		template<typename T = time_t>
		DigitalTime GetTimeRemaining(T&& seconds){
			T conv(seconds);

			int h, m;
			m = seconds / SECS_PER_MIN;
			h = seconds / SECS_PER_HOUR;
			auto min = fmod(m, 60);

			DigitalTime time = DigitalTime(h, min, 0);

			return time;
		}
		template<typename T = long>
		String^ GetTimeRemainingString(T&& seconds){
			T conv(seconds);

			DigitalTime time = GetTimeRemaining(seconds);
			auto timeString = FormatDigialTime(time.Hours, time.Minutes, time.Seconds);
			return timeString;
		}
		//<--copy to EAL--

	}

}
#endif