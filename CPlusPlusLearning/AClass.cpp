#include "AClass.h"

AClass::AClass(int shared) :_shared(shared){}

void AClass::AMethod(){

}
void AClass::Init(int b){
	b = 2;
}
void AClass::StaticMethod(){
	//StaticMember = 5;
}