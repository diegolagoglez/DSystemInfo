//**********************************
//*   D System Info release 2.5    *
//*   Created by chairman (Spain)  *
//*   22/Dec/2000                  *
//**********************************

#ifndef _SYSTEMINFOVIEW_H_
#define _SYSTEMINFOVIEW_H_

#include <Button.h>
#include <Font.h>
#include <Menu.h>
#include <MenuField.h>
#include <OS.h>
#include <StatusBar.h>
#include <StringView.h>
#include <View.h>
#include <VolumeRoster.h>

#include "Reusable/Bevel.h"

const uint32 kVolumeMessage = 6598;
const uint32 kFSMoreInfo    = 6599;

class DSystemInfoView : public BView
{
  public:
    DSystemInfoView(BRect frame, char* name, uint32 resizingMode, uint32 flags);
    virtual ~DSystemInfoView(void);
    virtual void Pulse();
    virtual void Draw(BRect updateRect);                // draw some lines
    virtual void MessageReceived(BMessage* message);
    
    void SetDevice(dev_t deviceID);
    dev_t GetDevice(void);
    void GetVolName(char*);
    void RebuildFileSystemMenu(void);
    int64 VolumeCapacity(void);
    int64 VolumeFreeBytes(void);
    void UpdateSystemInfo(void);
    void UpdateFileSystemStatusBar(char* label, char* trailing, float Capacity, float FreeBytes);
    
  private:
    system_info fSystemInfo;
    BVolume* volumeInfo;
    dev_t bootVolume;
    int64 lastCapacity;
    
    BFont* DSIPlainFont;
    BFont* DSIBoldFont;
        
    BStringView* fGenInfo;
    DBevel* fGenInfoBevel;
    BStringView* fKernel;
    BStringView* fPlatform;
    BStringView* fCPU;
    BStringView* fCPUClock;
    BStringView* fMemoryAmount;
    BMenuField* fFileSystemsMenu;
    BStatusBar* fFileSystemSpace;
    
    BStringView* fSystemRes;
    DBevel* fSysResBevel;
    BStatusBar* fMemStatusBar;
    BStatusBar* fSemStatusBar;
    BStatusBar* fPortsStatusBar;
    BStatusBar* fThreadsStatusBar;
    BStatusBar* fTeamsStatusBar;
    
    char* GetPlatformString(platform_type platform); 
    char* GetCPUString(cpu_type cpu);
    char* GetFSStatDev(void);
    
    void ConstructVolumeMenu(BMenu*);
};

#endif