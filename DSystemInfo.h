//**********************************
//*   D System Info release 2.5    *
//*   Created by chairman (Spain)  *
//*   22/Dec/2000                  *
//**********************************

#ifndef _SYSTEMINFO_H_
#define _SYSTEMINFO_H_

#define SystemInfoSignature "application/x-vnd.DSystemInfo"

#include <Application.h>

#include "DSystemInfoWindow.h"

class DSystemInfo : public BApplication
{
  public:
    DSystemInfo(char* sig);
    
  private:
    DSystemInfoWindow* SysInfoWindow;
};


#endif