//**********************************
//*   D System Info release 2.5    *
//*   Created by chairman (Spain)  *
//*   22/Dec/2000                  *
//**********************************

#include "SystemInfo.h"

int main(void)
{
  DSystemInfo* SystemInfo = new DSystemInfo(DSystemInfoSignature);
  SystemInfo->Run();
  SystemInfo->Lock();
  SystemInfo->Quit();
  SystemInfo->Unlock();
  return 0;
};