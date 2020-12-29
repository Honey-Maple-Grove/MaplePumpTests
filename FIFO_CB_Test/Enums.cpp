#include "Enums.h"


String EnumsClass::EnumStr(EnumsClass::Interupt interupt) {
	switch (interupt)
	{
	case EnumsClass::CheckInTemp:
		return "CheckInTemp";
		break;
	case EnumsClass::CheckMinSensors:
		return "CheckMinSensors"; 
		break;
	case EnumsClass::CheckSapFloat:
		return "CheckSapFloat";
		break;
	case EnumsClass::CheckSapLines:
		return "CheckSapLines";
		break;
	case EnumsClass::Void:
		return "Void";
		break;
	case EnumsClass::FifoPush:
		return "FifoPush - ";
		break;
	case EnumsClass::LifoPush:
		return "LifoPush - ";
		break;
	}
}