#ifndef RTCEXT_h
#define RTCEXT_h

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

		DigitalTime(int hours, int minutes, int seconds) : Hours(hours), Minutes(minutes), Seconds(seconds){}
	};


	////remeber: dependant functions must be defined first in namespace.
	///**Better to use template functions.
	namespace RTCExt{

		//static bool _initalized;
		static NextRunMemory NextFeedInfo;
		static NextRunMemory NextDoseInfo;

		//--dont copy to EAL-->
		template<typename T = void>
		int day(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr, &time);
			return timePtr->tm_mday;
		}
		template<typename T = void>
		int month(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr, &time);
			return timePtr->tm_mon + 1;
		}
		template<typename T = void>
		int year(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr,&time);
			return timePtr.tm_year + 1900;
		}
		template<typename T = void>
		int seconds(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr, &time);
			return timePtr->tm_sec;
		}
		template<typename T = void>
		int minute(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr, &time);
			return timePtr->tm_min;
		}
		template<typename T = void>
		int hour(time_t time)
		{
			tm timePtr;
			localtime_s(&timePtr, &time);
			return timePtr->tm_hour;
		}
		template<typename T = void>
		int hourFormat12(time_t t) { // the hour for the given time in 12 hour format
		
			if (hour(t) == 0)
				return 12; // 12 midnight
			else if (hour(t)  > 12)
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

		//<--dont copy to EAL--

		template<typename H = int, typename M = int, typename S = int>
		String^ FormatDigialTime(H&& hours, M&& minutes, S&& seconds)
		{
			H convH(hours);
			M convM(minutes);
			S convS(seconds);

			String^ hourString = String^(hours);
			if (hours < 10)
				hourString = "0" + hourString;
			String^ minString = String^(minutes);
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

			String^ dayString = String^(theDay);
			if (theDay < 10)
				dayString = "0" + dayString;
			String^ monthString = String^(theMonth);
			if (theMonth < 10)
				monthString = "0" + monthString;
			String^ yearString = String^(theYear);
			yearString.remove(0, 2);

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
		time_t GetRTCTime()
		{
			//int now = System::DateTime::Now.Millisecond;

			//time_t t = time(NULL);
			//tm* timePtr = localtime(&t);
			
			time_t now = time(NULL); //gets current time
		/*	struct tm * timeinfo;

			time(&now);
			timeinfo = localtime(&now);*/
			return now;
		}
		
		template<typename T = void>
		bool IsRTCTimeSet()
		{
			auto time = GetRTCTime();
			auto theYear = year(time);
			if (theYear < 2016)return false;
			return true;
		}
		template<typename T = void>
		void UpdateNextFeed(){

			auto rtcTime = GetRTCTime();
			auto runEvery = NextFeedInfo.RunEvery;
			auto countDown = NextFeedInfo.CountDown;
			auto nextRun = NextFeedInfo.NextRun;
			auto lastRun = NextFeedInfo.LastRun;

			if (!IsRTCTimeSet() || runEvery == 0)
			{
				return;// rtcTime;
			}

			//before first feeding
			if (lastRun == 0)
			{
				nextRun = rtcTime + runEvery;
				countDown = nextRun - rtcTime;
			}
			else{

				if (nextRun <= 0){

					nextRun = rtcTime + runEvery; //08:51:49
				}

				if (lastRun > 0 && nextRun <= rtcTime){
					nextRun = lastRun + runEvery;
				}
				countDown = nextRun - rtcTime; //00:00:06

				if (nextRun <= rtcTime){
					nextRun = rtcTime;
					countDown = 0;
				}
			}

			NextFeedInfo.RunEvery = runEvery;
			NextFeedInfo.CountDown = countDown;
			NextFeedInfo.NextRun = nextRun;
			NextFeedInfo.LastRun = lastRun;

		}

		//<--dont copy to EAL--
	}
}
#endif