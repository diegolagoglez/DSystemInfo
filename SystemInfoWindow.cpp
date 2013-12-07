#include <Alert.h>
#include <String.h>

#include "SystemInfo.h"
#include "SystemInfoView.h"
#include "SystemInfoWindow.h"

DSystemInfoWindow::DSystemInfoWindow(BRect frame) : BWindow(frame,"D System Info",B_TITLED_WINDOW,B_NOT_RESIZABLE)
{
  fSysInfoView = new DSystemInfoView(Bounds(),"SystemInfoView",B_FOLLOW_ALL_SIDES,B_WILL_DRAW | B_PULSE_NEEDED);
  fSysInfoView->AttachedToWindow();
  AddChild(fSysInfoView);
}

void DSystemInfoWindow::MessageReceived(BMessage* message)
{
  const char* volName;
  int32 DevID;
  int64 Capacity, FreeBytes;
  BString label,trailing;
  
  switch(message->what) {
    case kVolumeMessage: {
      volName = message->FindString("name");
      DevID = message->FindInt32("device");
      Capacity = message->FindInt64("capacity");
      FreeBytes = message->FindInt64("freespace");
      label << volName;
      if(Capacity <= 250000000) {
        trailing << (Capacity - FreeBytes) / 1024 << " KB used of " << Capacity / 1024 << " KB total"; 
      } else {
        trailing << (Capacity - FreeBytes) / 1024 / 1024 << " MB used of " << Capacity / 1024 / 1024 << " MB total"; 
      }
      fSysInfoView->UpdateFileSystemStatusBar((char*)label.String(),(char*)trailing.String(),Capacity,FreeBytes);
      break;
    }
    default: BWindow::MessageReceived(message); break;
  }
}

bool DSystemInfoWindow::QuitRequested(void)
{
  (DSystemInfo*)be_app->PostMessage(B_QUIT_REQUESTED);
  return true;
}

void DSystemInfoWindow::Zoom(BPoint P,float x,float y)
{
  (BAlert*)(new BAlert("chairman","D System Info r1.0\n\n...made by Diego Lago a.k.a. chairman (from Spain)\n\nThanks to Héctor López a.k.a. Leven for his help and thanks to all the people who help me when I need it. Thanks to Be Inc. for make BeOS.\n\nchairman@bemail.org","hehe!"))->Go();
}