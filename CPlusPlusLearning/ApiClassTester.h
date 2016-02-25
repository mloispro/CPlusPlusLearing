#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include "stdafx.h"
using namespace System;

#ifndef UTILS_H
#include "StaticUtils.h"
using namespace Utils;
#endif

//using namespace Utils;

//#include "ApiClass.h"
#include "ApiClassExt.h"
using namespace System::Threading;

namespace Tests{
	namespace ApiClassTester{
		
		void ApiCallback(){
			
			StaticUtils::Debug("Api_Callback");
		}
		void Test(){
			/*ApiClass apiClass;
			apiClass.SetTimeout(3000, ApiCallback);
			apiClass.Run();*/

			ApiClassExt apiClassExt;
			String^ runtime = apiClassExt.GetRuntime();
			apiClassExt.SetTimeout(3000, ApiCallback);
			apiClassExt.Run();
		}
		
	}
}

//class ApiClassTester
//{
//private:
//	void ApiCallback();
//public:
//	ApiClassTester();
//	void Test();
//	
//};
#endif

