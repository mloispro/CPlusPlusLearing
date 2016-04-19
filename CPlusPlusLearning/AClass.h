//#pragma once
class AClass
{
private:
	void Init(int b);
protected:
	int _shared;
public:
	int Shakes;
	AClass(int b);

	void AMethod();
	//static int StaticMember;
	static void StaticMethod();
};

