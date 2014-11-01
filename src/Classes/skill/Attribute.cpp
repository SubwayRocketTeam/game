#include "pch.h"
#include "Attribute.h"

Attribute::Attribute() :
	value(0),
	bonusRate(0), bonusValue(0){
}
Attribute::Attribute(
	float _bonusValue, float _bonusRate) :
	value(0),
	bonusRate(_bonusRate), bonusValue(_bonusValue){
}
Attribute::~Attribute(){
}

float Attribute::get(){
	return (value + bonusValue)
		* (1.0f + bonusRate);
}
float &Attribute::getValue(){
	return value;
}
float &Attribute::getBonusRate(){
	return bonusRate;
}
float &Attribute::getBonusValue(){
	return bonusValue;
}