#ifndef UTILS_H
#define UTILS_H

//#include <ctime>
//#include <string>
//using namespace std;

namespace Utils {
	namespace StaticUtils{

		int startTime = System::DateTime::Now.Millisecond;

		//T& will only take references, T&& will take ref, pointer, or val, so always do this.
		template<typename T>
		void Debug(T&& val)
		{
			Console::WriteLine(val);
		}
		
		template<typename T>
		void DebugAddOne(T&& val)
		{
			T tmp(val);
			val = val + 1;
			Console::WriteLine(val);
		}
		int ReadIncomingByte(){
			return 4;
		}
		template<int... T>
		auto TestAutoInt() -> int{
			int p = 49;
			return p;
		}
		template<typename T>
		auto TestAuto(T val) -> decltype(val){
			T p = 49;
			return p;
		}
		int millis()
		{
			//int sysTimeMS = System::TimeSpan::Milliseconds();
			/*const long double sysTime = time(0);
			const long double sysTimeMS = sysTime * 1000;*/
			int runTime = startTime + System::DateTime::Now.Millisecond;
			return runTime;
		}
		String^ FormatTime(int hours, int minutes, int seconds)
		{
			/*Serial.print(":");
			if (digits < 10)
				Serial.print('0');
			Serial.print(digits);*/
			String^ hourString = hours.ToString();
			if (hours < 10)
				hourString = "0" + hourString;
			String^ minString = minutes.ToString();
			if (minutes < 10)
				minString = "0" + minString;
			String^ secString = seconds.ToString();
			if (seconds < 10)
				secString = "0" + secString;
			//String timeString = String(hours) + ":";
			String^ timeString = hourString + ":";
			timeString += minString + ":";
			timeString += secString;
			return timeString;
		}
		String^ GetRuntime(){
			int h, m, s;
			s = millis() / 1000;
			m = s / 60;
			h = s / 3600;
			s = s - m * 60;
			m = m - h * 60;
			//Serial.print(h);
			//PrintDigits(m);
			//PrintDigits(s);
			//Serial.println();
			String^ runTime = FormatTime(h, m, s);
			return runTime;
		}
		void PrintRuntime(){
			String^ runtime = GetRuntime();
			Console::WriteLine(runtime);
		}
		

		
	}
}


#endif

