//************************************************
//*   D System Info release 0.2.6                *
//*   Diego Lago <diego.lago.gonzalez@gmail.com> *
//*   2018-12-03                                 *
//************************************************

#include "DSystemInfo.h"

int main(void)
{
  DSystemInfo* SystemInfo = new DSystemInfo();
  SystemInfo->Run();
  delete SystemInfo;
  return 0;
};
