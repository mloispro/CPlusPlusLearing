#ifndef EASYUTILS_H
#define EASYUTILS_H

//#include <msclr\marshal.h>
//#include <stdlib.h>

//#include <EEWrap\EEWrap.h>


#include <vector>
using namespace System;
using namespace std;

//using namespace msclr::interop;

//template< typename T > struct EEWrap;
//namespace ee {
//
//	template< typename D, typename T >
//	class EEMultiByte{
//	public:
//
//		T EERead(void){
//			T ret;
//			//tools::EEReadBlockElement((char*)&ret + sizeof(T) - 1, uptr(&self()), sizeof(T));
//			return(ret);
//		}
//
//		D &EEWrite(const T& v){
//			//tools::EEWriteBlockElement((const char*)&v + sizeof(T) - 1, uptr(&self()), sizeof(T));
//			return self();
//		}
//	//protected: STATIC_ACCESS
//	};
//
//	template< typename D, typename T >
//	class EESingleByte{
//	public:
//
//		T EERead(void){ 
//			return int(&self()); 
//		}
//
//		D &EEWrite(const T& v){
//			//if (EERead() != v) EEPROM[int(&self())] = v;
//			return self();
//		}
//	//protected: STATIC_ACCESS
//	};
//}
//using namespace ee;
//template< typename T>
//struct EEWrap {
//	
//	operator const T() { return EERead(); }
//	EEWrap &operator =(const T &in){ return this; }
//	bool operator ==(const T &in){ return in; }
//
//	T t;
//
//};
//
//typedef EEWrap< char > int8_e;                   //char
//typedef EEWrap< unsigned char > uint8_e;         //unsigned char
//typedef EEWrap< int > int16_e;                   //int
//typedef EEWrap< unsigned int > uint16_e;         //unsigned int
//typedef EEWrap< long > int32_e;                  //long
//typedef EEWrap< unsigned long > uint32_e;        //unsigned long
//typedef EEWrap< long long > int64_e;             //long long
//typedef EEWrap< unsigned long long > uint64_e;   //unsigned long long
//typedef EEWrap< bool > bool_e;                   //bool
//typedef EEWrap< float > float_e;                 //float
//typedef EEWrap< double > double_e;               //double
//typedef EEWrap< long double > long_double_e;     //long double

//namespace ee {
//	namespace geometry {
//		namespace model {
//			namespace d2 {
//
//				bool operator==(const Point& p1, const Point& p2) {
//					return p1.x() == p2.x() && p1.y() == p2.y();
//				}
//
//			}
//		}
//	}
//}


//namespace Sched{
//	struct RunSchedule{
//
//		uint32_e Pin;
//		uint32_e LastRunInSeconds;
//		uint32_e NextRunInSeconds;
//		uint32_e RuntimeInSeconds;
//	};
//	namespace TimerExt{
//
//		static RunSchedule TheRunSchedule;
//		static RunSchedule TheRunSchedule2;
//		static RunSchedule TheRunSchedule3;
//		static RunSchedule TheRunSchedule4;
//
//		static vector<RunSchedule> RunSchedules;
//
//		template<typename T = void>
//		extern void InitSchedules()
//		{
//			TheRunSchedule.Pin = -1;
//			TheRunSchedule2.Pin = -1;
//			TheRunSchedule3.Pin = -1;
//			TheRunSchedule4.Pin = -1;
//			RunSchedules.push_back(TheRunSchedule);
//			RunSchedules.push_back(TheRunSchedule2);
//			RunSchedules.push_back(TheRunSchedule3);
//			RunSchedules.push_back(TheRunSchedule4);
//		}
//		template<typename T = uint32_e>
//		RunSchedule GetRunSchedule(T pin){
//			//T conv(pin);
//
//			RunSchedule schedule = TheRunSchedule;
//			//int runTime = TimerExt::GetRuntimeInSeconds();
//
//			if (RunSchedules.size() <= 0){
//				InitSchedules();
//				schedule.Pin = pin;
//				//schedule.RuntimeInSeconds = runTime;
//				return schedule;
//			}
//
//			//uint32_e thePin = EEPROM.; //(uint16_e)pin;
//
//			//find shedule by pin
//			bool found;
//			for (const auto& runSched : RunSchedules)
//			{
//				//const uint32_e runSchedPin = runSched.Pin;
//				//uint32_e b = *reinterpret_cast<uint32_e*>(pin);
//				//uint32_e b2 = *reinterpret_cast<uint32_e*>(runSched.Pin);
//				//int b = *reinterpret_cast<uint32_e*>(&runSched.Pin);
//				int b = 5; //const_cast<int>(runSched.Pin);
//				if (b == pin)
//				{
//					found = true;
//					schedule = runSched;
//					break;
//				}
//			}
//
//			////if not found, find first availble one.
//			//if (!found){
//			//	short&& noPin = -1;
//			//	for (const auto& runSched : RunSchedules)
//			//	{
//			//		if (runSched.Pin == noPin)
//			//		{
//			//			found = true;
//			//			schedule = runSched;
//			//			break;
//			//		}
//			//	}
//			//}
//			//schedule.Pin = pin;
//			///schedule.RuntimeInSeconds = runTime;
//
//			return schedule;
//		}
//	}
//}
#endif