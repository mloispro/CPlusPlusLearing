#include "ApiClassExt.h"

#include "StaticUtils.h"
using namespace Utils;

ApiClassExt::ApiClassExt()
{
}
String^ ApiClassExt::FormatTime(int hours, int minutes, int seconds)
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
String^ ApiClassExt::GetRuntime(){
	int h, m, s;
	s = StaticUtils::millis() / 1000;
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
void ApiClassExt::PrintRuntime(){
	String^ runtime = GetRuntime();
	//String^ result = msclr::interop::marshal_as<String^>(runtime);
	Console::WriteLine(runtime);
}