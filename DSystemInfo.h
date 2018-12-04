//************************************************
//*   D System Info release 0.2.6                *
//*   Diego Lago <diego.lago.gonzalez@gmail.com> *
//*   2018-12-03                                 *
//************************************************

#ifndef _SYSTEMINFO_H_
#define _SYSTEMINFO_H_

#define DSystemInfoSignature "application/x-vnd.DSystemInfo"

#include <Application.h>

#include "DSystemInfoWindow.h"

class DSystemInfo : public BApplication
{
  public:
    DSystemInfo();
    
  private:
    DSystemInfoWindow* SysInfoWindow;
};


#endif
