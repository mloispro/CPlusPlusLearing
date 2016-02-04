#ifndef UTILS_H
#define UTILS_H


namespace Utils {
	namespace Print{

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
	}
}


#endif

