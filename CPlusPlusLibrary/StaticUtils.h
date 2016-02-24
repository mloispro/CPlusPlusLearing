#ifndef UTILS_H
#define UTILS_H

//#include <msclr\marshal.h>
//#include <stdlib.h>
//#include <string.h>


using namespace System;
using namespace std;

//using namespace msclr::interop;

namespace Utils {
	namespace StaticUtils{

		//extern int startTime = System::DateTime::Now.Millisecond;
		template<typename T = String^>
		void Debug(T ^val)
		{
			Console::WriteLine(val);
		}

		//T& will only take references, T&& will take ref, pointer, or val, so always do this.
		template<typename T>
		void Debug(T&& val)
		{
			T t(val);
			Console::WriteLine(val);
		}

		
		
		template<typename T>
		void DebugAddOne(T&& val)
		{
			T tmp(val);
			val = val + 1;
			Console::WriteLine(val);
		}
		template<int... T>
		auto ReadIncomingByte() -> int{
			int p = 4;
			return p;
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

		template<int... T>
		auto millis() -> int{
			//int sysTimeMS = System::TimeSpan::Milliseconds();
			/*const long double sysTime = time(0);
			const long double sysTimeMS = sysTime * 1000*/
			int startTime = System::DateTime::Now.Millisecond;
			int runTime = startTime + System::DateTime::Now.Millisecond;
			return runTime;
		}
		
	}
}


#endif

