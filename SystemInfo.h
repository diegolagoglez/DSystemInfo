#ifndef _SYSTEMINFO_H_
#define _SYSTEMINFO_H_

#define DSystemInfoSignature "application/x-vnd.DSystemInfo"

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