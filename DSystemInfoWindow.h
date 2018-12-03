//************************************************
//*   D System Info release 0.2.6                *
//*   Diego Lago <diego.lago.gonzalez@gmail.com> *
//*   2018-12-03                                 *
//************************************************

#ifndef _SYSTEMINFOWINDOW_H_
#define _SYSTEMINFOWINDOW_H_

#include <fs_info.h>
#include <Menu.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <Message.h>
#include <Messenger.h>
#include <NodeMonitor.h>
#include <Window.h>

#include "DSystemInfoView.h"

const uint32 kSelectBoot     = 1000;
const uint32 kVolumeMoreInfo = 1001;

const int kAppWidth   = 350;
const int kAppHeight  = 342;

class DSystemInfoWindow : public BWindow
{
  public:
    DSystemInfoWindow(BRect frame);
    ~DSystemInfoWindow(void);
    virtual void MessageReceived(BMessage* message);
    virtual bool QuitRequested(void);
    virtual void Zoom(BPoint P,float x,float y);
    
  private:
    BMenuBar* fMenuBar;
    BMenu* fSystem;
    BMenu* fAbout;

    BVolumeRoster* volumeRoster;
    DSystemInfoView* fSysInfoView;
};

#endif
