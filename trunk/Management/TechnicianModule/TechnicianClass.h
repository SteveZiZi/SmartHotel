#pragma once
//=================================================================================
#ifdef _USRDLL
	#define TECHNICIAN_API(type) type __declspec(dllexport)
#else
	#define TECHNICIAN_API(type) type __declspec(dllexport)
#endif



extern "C"
{
	TECHNICIAN_API(int)  WakeUpTechnicianModule(unsigned long * lParam);
}