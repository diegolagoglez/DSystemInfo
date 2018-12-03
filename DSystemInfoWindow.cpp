#include <Alert.h>
#include <String.h>

#include "DSystemInfo.h"
#include "DSystemInfoWindow.h"

DSystemInfoWindow::DSystemInfoWindow(BRect frame) : BWindow(frame,"D System Info",B_TITLED_WINDOW,B_NOT_RESIZABLE)
{
  fSysInfoView = new DSystemInfoView(BRect(0, 20, Bounds().right, Bounds().bottom),"DSystemInfoView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_PULSE_NEEDED);
  fSysInfoView->AttachedToWindow();
  AddChild(fSysInfoView);
  fSysInfoView->UpdateSystemInfo();
  
  fMenuBar = new BMenuBar(BRect(0,0,Bounds().right,20),"MenuBar");
  fSystem = new BMenu("System");
  fSystem->AddItem(new BMenuItem("Volume more info...",new BMessage(kVolumeMoreInfo)));
//  fSystem->AddSeparatorItem();
//  fSystem->AddItem(new BMenuItem("Preferences...",NULL));
  fSystem->AddSeparatorItem();
  fSystem->AddItem(new BMenuItem("Quit",new BMessage(B_QUIT_REQUESTED)));
  fMenuBar->AddItem(fSystem);
  fAbout = new BMenu("About");
  fAbout->AddItem(new BMenuItem("About D System Info...",new BMessage(B_ABOUT_REQUESTED)));
  fMenuBar->AddItem(fAbout);
  AddChild(fMenuBar);
    
  BMessenger msgr(this);
  volumeRoster = new BVolumeRoster();
  volumeRoster->StartWatching(msgr);   // to control when a volume is mounted/unmounted
}

DSystemInfoWindow::~DSystemInfoWindow(void)
{
  volumeRoster->StopWatching();   // stop the volume roster
  delete volumeRoster;
  fSysInfoView->RemoveSelf();
  delete fSysInfoView;
}

void
DSystemInfoWindow::MessageReceived(BMessage* message)
{
  int32 DeviceID = 0;
  char volName[20];
  int64 Capacity, FreeBytes;
  BString label,trailing;
  
  switch(message->what) {
    case kVolumeMessage: {
      message->FindInt32("DevID",&DeviceID);
      fSysInfoView->SetDevice((dev_t)DeviceID);
      fSysInfoView->GetVolName(volName);
      Capacity = fSysInfoView->VolumeCapacity();
      FreeBytes = fSysInfoView->VolumeFreeBytes();
      label << volName;
      if(Capacity <= 250000000) {
        trailing << (Capacity - FreeBytes) / 1024 << " KB used - " << FreeBytes / 1024 << " KB free - " << Capacity / 1024 << " KB total"; 
      } else {
        trailing << (Capacity - FreeBytes) / 1024 / 1024 << " MB used - " << FreeBytes / 1024 / 1024 << " MB free - " << Capacity / 1024 / 1024 << " MB total"; 
      }
      fSysInfoView->UpdateFileSystemStatusBar((char*)label.String(),(char*)trailing.String(),Capacity,FreeBytes);
      break;
    }
    
    case kVolumeMoreInfo: {
      BMessenger* mes = new BMessenger(fSysInfoView);
      mes->SendMessage(new BMessage(kVolumeMoreInfo));
      delete mes;
      break;
    }
    
    case B_ABOUT_REQUESTED: {
      (new BAlert("Diego","D System Info release 0.2.6.\nBuild: 2018-12-03\n\nCreated by Diego Lago\n\nThanks to Héctor López for his help and discover BeOS to me. Thanks to all the people who help me when I need it. Thanks to Be Inc. for make BeOS and thanks to Haiku team.\n\ndiego.lago.gonzalez@gmail.com","hehe!"))->Go();
      break;
    }
    
    case B_NODE_MONITOR: {     // a volume has been mounted/unmounted
      Lock();
      fSysInfoView->RebuildFileSystemMenu();
      Unlock();
      int32 opcode;
      message->FindInt32("opcode",&opcode);
      switch(opcode) {
        case B_DEVICE_MOUNTED: // device mounted
          break;
        case B_DEVICE_UNMOUNTED:  // if the device unmounted is showing, select boot
          BMessenger mes(fSysInfoView);
          mes.SendMessage(kSelectBoot);
          break;
      }     
      break;
    }    
    default: BWindow::MessageReceived(message); break;
  }
}

bool
DSystemInfoWindow::QuitRequested(void)
// close the window and the app
{
  be_app->PostMessage(B_QUIT_REQUESTED);
  return true;
}

void
DSystemInfoWindow::Zoom(BPoint P,float x,float y)
// About box when you press... ZOOM
{
  PostMessage(B_ABOUT_REQUESTED);
}
