#include "SystemClass.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR pScmdline, int iCmdshow)
{
	SystemClass * System;
	bool result;

	System = new SystemClass;
	if (!System)
	{
		return 0;
	}
	result = System->Initialize();
	if (result)
	{
		System->Run();
	}
	
	System->Shutdown();
	delete System;
	System = nullptr;

	return 0;

}