//#pragma once
#ifndef APICLASS_H
#define APICLASS_H

//#include <iostream>
//#include "stdafx.h"
using namespace System;
using namespace System::Threading;

typedef void(*timer_callback)(void);
class ApiClass
{
private:
	timer_callback callbacks[10];
	long delays[10];
	int toBeCalled[10];
public:
	ApiClass();
	int SetTimeout(long d, timer_callback f);
	void Run();
};
#endif

