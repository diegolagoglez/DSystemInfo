#include <Alert.h>
#include <Directory.h>
#include <MenuItem.h>
#include <String.h>
#include <Volume.h>

#include "SystemInfoWindow.h"
#include "SystemInfoView.h"

const rgb_color colWhite = { 255,255,255,255 };
const rgb_color colGray  = { 180,180,180,255 };
const rgb_color DarkBlue = { 0,100,255,255 };

const int kStatusBarBasePosY = kAppHeight - 160;
const int kStatusBarBasePosX = 25;

DSystemInfoView::DSystemInfoView(BRect frame, char* name, uint32 resizingMode, uint32 flags) :
                                BView(frame,name,resizingMode,flags | B_PULSE_NEEDED)
{
  rgb_color clGray = { 220,220,220,255 };
  SetViewColor(clGray);
  
  BString AuxString;
  
  get_system_info(&fSystemInfo);
  
  fGenInfo = new BStringView(BRect(15,12,130,25),"GeneralInfo","General Information");
  fGenInfo->SetFont(be_bold_font);
  AddChild(fGenInfo);
  fGenInfoBevel = new DBevel(BRect(135,16,kAppWidth - 16,17),"GenInfoBevel",kTopLine);
  AddChild(fGenInfoBevel);
  
  AuxString << "Kernel: " << fSystemInfo.kernel_build_date << " " << fSystemInfo.kernel_build_time;
  fKernel = new BStringView(BRect(kStatusBarBasePosX,30,kStatusBarBasePosX + 150,40),"Kernel",AuxString.String());
  AuxString.SetTo("");;
  AddChild(fKernel);
  
  AuxString << "Platform: " << GetPlatformString(fSystemInfo.platform_type);
  fPlatform = new BStringView(BRect(kStatusBarBasePosX + 160,30,kStatusBarBasePosX + 320,40),"Platform",AuxString.String());
  AuxString.SetTo("");
  AddChild(fPlatform);
  
  AuxString << "CPU: " << GetCPUString(fSystemInfo.cpu_type);
  fCPU = new BStringView(BRect(kStatusBarBasePosX,48,kStatusBarBasePosX + 150,58),"CPU",AuxString.String());
  AuxString.SetTo("");
  AddChild(fCPU);
  
  AuxString << "CPU clock: " << fSystemInfo.cpu_clock_speed / 1000000 << " MHz.";
  fCPUClock = new BStringView(BRect(kStatusBarBasePosX + 160,48,kStatusBarBasePosX + 320,58),"CPU Clock",AuxString.String());
  AuxString.SetTo("");
  AddChild(fCPUClock);
  
  AuxString << "Memory amount: " << (fSystemInfo.max_pages * B_PAGE_SIZE) / 1024 /1024 << " MB  (" << fSystemInfo.max_pages * B_PAGE_SIZE << " bytes).";
  fMemoryAmount = new BStringView(BRect(kStatusBarBasePosX,66,kStatusBarBasePosX + 320,76),"Bus clock",AuxString.String());
  AuxString.SetTo("");
  AddChild(fMemoryAmount);
  
  BMenu* Aux = new BMenu("Select a volume");
  ConstructVolumeMenu(Aux);
  fFileSystemsMenu = new BMenuField(BRect(kStatusBarBasePosX,78,kStatusBarBasePosX + 200,88),"FileSystems","File systems: ",Aux);
  fFileSystemsMenu->SetDivider(70);
  AddChild(fFileSystemsMenu);
  
  fFileSystemSpace = new BStatusBar(BRect(kStatusBarBasePosX + 5,102,kAppWidth - 15,0),"","");
  fFileSystemSpace->SetBarHeight(12);
  fFileSystemSpace->SetBarColor(DarkBlue);
  AddChild(fFileSystemSpace);
  
  fSystemRes = new BStringView(BRect(15,kStatusBarBasePosY - 20,125,kStatusBarBasePosY - 5),"SystemResources","System resources");
  fSystemRes->SetFont(be_bold_font);
  AddChild(fSystemRes);
  fSysResBevel = new DBevel(BRect(130,kStatusBarBasePosY - 13,kAppWidth - 16,kStatusBarBasePosY - 12),"SysResBevel",kTopLine);
  AddChild(fSysResBevel);
  
  fMemStatusBar = new BStatusBar(BRect(kStatusBarBasePosX,kStatusBarBasePosY,kAppWidth - 15,0),"MemStatusBar","Memory pages");
  fMemStatusBar->SetBarHeight(12);
  AddChild(fMemStatusBar);
  fSemStatusBar = new BStatusBar(BRect(kStatusBarBasePosX,kStatusBarBasePosY + 30,kAppWidth - 15,0),"SemStatusBar","Semaphores");
  fSemStatusBar->SetBarHeight(12);
  AddChild(fSemStatusBar);
  fPortsStatusBar = new BStatusBar(BRect(kStatusBarBasePosX,kStatusBarBasePosY + 60,kAppWidth - 15,0),"PortsStatusBar","Ports");
  fPortsStatusBar->SetBarHeight(12);
  AddChild(fPortsStatusBar);
  fThreadsStatusBar = new BStatusBar(BRect(kStatusBarBasePosX,kStatusBarBasePosY + 90,kAppWidth - 15,0),"ThreadsStatusBar","Threads");
  fThreadsStatusBar->SetBarHeight(12);
  AddChild(fThreadsStatusBar);
  fTeamsStatusBar = new BStatusBar(BRect(kStatusBarBasePosX,kStatusBarBasePosY + 120,kAppWidth - 15,0),"TeamsStatusBar","Teams");
  fTeamsStatusBar->SetBarHeight(12);
  AddChild(fTeamsStatusBar);
}

DSystemInfoView::~DSystemInfoView(void)
{
}

void DSystemInfoView::Pulse()
{
  UpdateSystemInfo();
}

void DSystemInfoView::Draw(BRect updateRect)
{
  BRect bounds = Bounds();
  BeginLineArray(8);
  AddLine(BPoint(bounds.left,bounds.top),BPoint(bounds.right,bounds.top),colWhite);
  AddLine(BPoint(bounds.left+1,bounds.top+1),BPoint(bounds.right-1,bounds.top+1),colWhite);
  AddLine(BPoint(bounds.left,bounds.top),BPoint(bounds.left,bounds.bottom),colWhite);
  AddLine(BPoint(bounds.left+1,bounds.top+1),BPoint(bounds.left+1,bounds.bottom-1),colWhite);
  AddLine(BPoint(bounds.right,bounds.top),BPoint(bounds.right,bounds.bottom),colGray);
  AddLine(BPoint(bounds.right-1,bounds.top+1),BPoint(bounds.right-1,bounds.bottom-1),colGray);
  AddLine(BPoint(bounds.left,bounds.bottom),BPoint(bounds.right,bounds.bottom),colGray);
  AddLine(BPoint(bounds.left+1,bounds.bottom-1),BPoint(bounds.right-1,bounds.bottom-1),colGray);
  EndLineArray();
}

void DSystemInfoView::MessageReceived(BMessage* message)
{ 
  switch(message->what) {
    default: BView::MessageReceived(message);
  }
}

void DSystemInfoView::UpdateSystemInfo(void)
{
  get_system_info(&fSystemInfo);
  
  BString strMemPages;
  strMemPages << fSystemInfo.used_pages << " used of " << fSystemInfo.max_pages << " total";
  fMemStatusBar->SetMaxValue((float)fSystemInfo.max_pages);
  fMemStatusBar->Update((float)fSystemInfo.used_pages - fMemStatusBar->CurrentValue(),"",strMemPages.String());
  
  BString strSemaphores;
  strSemaphores << fSystemInfo.used_sems << " used of " << fSystemInfo.max_sems << " max";
  fSemStatusBar->SetMaxValue((float)fSystemInfo.max_sems);
  fSemStatusBar->Update((float)fSystemInfo.used_sems - fSemStatusBar->CurrentValue(),"",strSemaphores.String());
  
  BString strPorts;
  strPorts << fSystemInfo.used_ports << " used of " << fSystemInfo.max_ports << " max";
  fPortsStatusBar->SetMaxValue((float)fSystemInfo.max_ports);
  fPortsStatusBar->Update((float)fSystemInfo.used_ports - fPortsStatusBar->CurrentValue(),"",strPorts.String());
  
  BString strThreads;
  strThreads << fSystemInfo.used_threads << " used of " << fSystemInfo.max_threads << " max";
  fThreadsStatusBar->SetMaxValue((float)fSystemInfo.max_threads);
  fThreadsStatusBar->Update((float)fSystemInfo.used_threads - fThreadsStatusBar->CurrentValue(),"",strThreads.String());
  
  BString strTeams;
  strTeams << fSystemInfo.used_teams << " used of " << fSystemInfo.max_teams << " max";
  fTeamsStatusBar->SetMaxValue((float)fSystemInfo.max_teams);
  fTeamsStatusBar->Update((float)fSystemInfo.used_teams - fTeamsStatusBar->CurrentValue(),"",strTeams.String());
}

void DSystemInfoView::UpdateFileSystemStatusBar(char* label, char* trailing, float Capacity, float FreeBytes)
{
  fFileSystemSpace->Reset();
  fFileSystemSpace->SetMaxValue((float)Capacity);
  fFileSystemSpace->Update((float)Capacity - FreeBytes,label,trailing);
}

char* DSystemInfoView::GetPlatformString(platform_type platform)
{
  switch(platform) {
    case B_BEBOX_PLATFORM: return "BeBox"; break;
    case B_MAC_PLATFORM: return "Macintosh"; break;
    case B_AT_CLONE_PLATFORM: return "IBM PC/AT or clone"; break;
    case B_ENIAC_PLATFORM: return "ENIAC"; break;
    case B_APPLE_II_PLATFORM: return "Apple II"; break;
    case B_CRAY_PLATFORM: return "Cray"; break;
    case B_LISA_PLATFORM: return "Lisa"; break;
    case B_TI_994A_PLATFORM: return "TI 994A"; break;
    case B_TIMEX_SINCLAIR_PLATFORM: return "Timex Sinclair"; break;
    case B_ORAC_1_PLATFORM: return "Orac 1"; break;
    case B_HAL_PLATFORM: return "HAL"; break;
    case B_BESM_6_PLATFORM: return "Besm 6"; break;
    case B_MK_61_PLATFORM: return "MK 61"; break;
    case B_NINTENDO_64_PLATFORM: return "Nintendo 64"; break;
    default: return "Platform unknown";
  }
}

char* DSystemInfoView::GetCPUString(cpu_type cpu)
{
  switch(cpu) {
    case B_CPU_PPC_601 : return "Power PC 601"; break;
    case B_CPU_PPC_603 : return "Power PC 603"; break;
    case B_CPU_PPC_603e : return "Power PC 603e"; break;
    case B_CPU_PPC_604 : return "Power PC 604"; break;
    case B_CPU_PPC_604e : return "Power PC 604e"; break;
    case B_CPU_PPC_750 : return "Power PC 750"; break;
    case B_CPU_PPC_686 : return "Power PC 686"; break;
    case B_CPU_AMD_29K : return "AMD 29K"; break;
    case B_CPU_X86 : return "IBM PC x86"; break;
    case B_CPU_MC6502 : return "MC6502"; break;
    case B_CPU_Z80 : return "Z80 Processor"; break;
    case B_CPU_ALPHA : return "Alpha processor"; break;
    case B_CPU_MIPS : return "MIPS processor"; break;
    case B_CPU_HPPA : return "HPPA processor"; break;
    case B_CPU_M68K : return "Motorola 68K"; break;
    case B_CPU_ARM : return "ARM processor"; break;
    case B_CPU_SH : return "SH processor"; break;
    case B_CPU_SPARC : return "Sparc processor"; break;
    case B_CPU_INTEL_X86 : return "Intel x86"; break;
    case B_CPU_INTEL_PENTIUM : return "Intel Pentium"; break;
    case B_CPU_INTEL_PENTIUM75 : return "Intel Pentium 75"; break;
    case B_CPU_INTEL_PENTIUM_486_OVERDRIVE : return "Intel Pentium 80486 Overdrive"; break;
//    case B_CPU_INTEL_PENTIUM_MMX :  return "Intel Pentium MMX"; break;
    case B_CPU_INTEL_PENTIUM_MMX_MODEL_4 : return "Intel Pentium MMX model 4"; break;
    case B_CPU_INTEL_PENTIUM_MMX_MODEL_8 : return "Intel Pentium MMX model 8"; break;
    case B_CPU_INTEL_PENTIUM75_486_OVERDRIVE : return "Intel Pentium 75 Overdrive"; break;
    case B_CPU_INTEL_PENTIUM_PRO : return "Intel Pentium Pro"; break;
//    case B_CPU_INTEL_PENTIUM_II : return "Intel Pentium II"; break;
    case B_CPU_INTEL_PENTIUM_II_MODEL_3 : return "Intel Pentium II model 3"; break;
    case B_CPU_INTEL_PENTIUM_II_MODEL_5 : return "Intel Pentium II model 5"; break;
    case B_CPU_INTEL_CELERON : return "Intel Celeron"; break;
    case B_CPU_INTEL_PENTIUM_III : return "Intel Pentium III"; break;
    case B_CPU_AMD_X86 : return "AMD x86 compatible"; break;
    case B_CPU_AMD_K5_MODEL0 : return "AMD K5 model 0"; break;
    case B_CPU_AMD_K5_MODEL1 : return "AMD K5 model 1"; break;
    case B_CPU_AMD_K5_MODEL2 : return "AMD K5 model 2"; break;
    case B_CPU_AMD_K5_MODEL3 : return "AMD K5 model 3"; break;
    case B_CPU_AMD_K6_MODEL6 : return "AMD K6 model 6"; break;
    case B_CPU_AMD_K6_MODEL7 : return "AMD K6 model 7"; break;
//    case B_CPU_AMD_K6_MODEL8 : return "AMD K6 model 8"; break;
    case B_CPU_AMD_K6_2 : return "AMD K6/2"; break;
//    case B_CPU_AMD_K6_MODEL9 : return "AMD K6 model 9"; break;
    case B_CPU_AMD_K6_III : return "AMD K6/3"; break;
    case B_CPU_AMD_ATHLON_MODEL1 : return "AMD Athlon model 1"; break;
    case B_CPU_CYRIX_X86 : return "Cyrix x86 compatible"; break;
    case B_CPU_CYRIX_6x86MX : return "Cyrix 6x86 MX"; break;
    case B_CPU_IDT_X86 : return "IDT x86 compatible"; break;
    case B_CPU_IDT_WINCHIP_C6 : return "IDT WinChip C6"; break;
    case B_CPU_IDT_WINCHIP_2 : return "IDT WinChip 2"; break;
    case B_CPU_RISE_X86 : return "Rise x86 compatible"; break;
    case B_CPU_RISE_mP6 : return "Rise mP6"; break;
    default: return "CPU type unknown"; break;
  }
}

void DSystemInfoView::ConstructVolumeMenu(BMenu* menu)
{
  BVolumeRoster volRoster;
  BVolume volume;
  BMessage* message;
  char buffer[20];
  
  volRoster.Rewind();
  while(volRoster.GetNextVolume(&volume) == B_OK) {
    if(volume.IsPersistent()) {
      volume.GetName(buffer);    
      message = new BMessage(kVolumeMessage);
      message->AddString("name",buffer);
      message->AddInt32("device",volume.Device());      
      message->AddInt64("capacity",volume.Capacity());
      message->AddInt64("freespace",volume.FreeBytes());
      menu->AddItem(new BMenuItem(buffer,message));
    }
  }
  menu->SetTargetForItems(this);
}