#ifndef UTILS_H
#define UTILS_H

#include <vector>

using namespace std;
using namespace System;

//using namespace msclr::interop;


namespace Utils {
	namespace StaticUtils{

		//extern int startTime = System::DateTime::Now.Millisecond;
		template<typename T = String^, typename T2>
		void Debug(T ^txt, T2&& val)
		{
			T t(txt);
			F f(val);
			Console::Write(txt);
			Console::WriteLine(val);
		}
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

		//use debug prints for debug statements that should be removed, after debugging.
		template<typename T = String, typename F>
		void Debug(T&& text, F&& val)
		{
			T t(text);
			F f(val);
			//String msg = String("~DEBUG~ ") + text;
			Console::Write(text);
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

		template<typename T = void>
		void WriteLine(string text)
		{
			String^ val = ParseString(text);
			Console::WriteLine(val);
		}
		template<typename T = void>
		void WriteLine(String^ text)
		{
			Console::WriteLine(text);
		}
		template<typename T = void>
		String^ ParseString(string str)
		{
			String^ val = gcnew String(str.c_str());
			return val;
		}
		template<typename T = void>
		void MarshalString(String ^ s, string& os)
		{
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}
		template<typename T = void>
		string ParseString(String^ str)
		{
			string val;
			MarshalString(str, val);
			return val;
		}
		template<typename T = void>
		int ReadKey()
		{
			int key = -1;
			ConsoleKeyInfo cki;
			do
			{
				cki = Console::ReadKey();
				switch (cki.Key)
				{
				case ConsoleKey::RightArrow:
					key = 0;
					break;
				case ConsoleKey::UpArrow:
					key = 1;
					break;
				case ConsoleKey::DownArrow:
					key = 2;
					break;
				case ConsoleKey::LeftArrow:
					key = 3;
					break;
				case ConsoleKey::Enter:
					key = 4;
					break;
				}
				Console::WriteLine("Key: " + cki.Key.ToString());
				return key;
			} while (cki.Key != ConsoleKey::Escape);

		}

	}
}



#endif