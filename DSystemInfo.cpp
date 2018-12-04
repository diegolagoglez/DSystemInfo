#include <Screen.h>

#include "DSystemInfo.h"

DSystemInfo::DSystemInfo() : BApplication(DSystemInfoSignature)
{
  // center the app in the screen
  BScreen *Screen = new BScreen();
  BRect Bounds(Screen->Frame());
  delete Screen;
  Screen = NULL;

  BRect R;
  R.Set(Bounds.right / 2 - kAppWidth / 2, Bounds.bottom / 2 - kAppHeight / 2,
        Bounds.right / 2 + kAppWidth / 2, Bounds.bottom / 2 + kAppHeight / 2);
  SysInfoWindow = new DSystemInfoWindow(R);
  SysInfoWindow->Show();
};
