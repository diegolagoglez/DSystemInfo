#include <Alert.h>
#include <Directory.h>
#include <MenuItem.h>
#include <String.h>
#include <Volume.h>

#include "DSystemInfoView.h"
#include "DSystemInfoWindow.h"

const rgb_color colWhite = { 255,255,255,255 };
const rgb_color colGray  = { 180,180,180,255 };
const rgb_color DarkBlue = { 255,130,95,255 };
const rgb_color clGray   = { 220,220,220,255 };

const int kGenInfoBasePosY   = kAppHeight - 329;
const int kStatusBarBasePosY = kAppHeight - 180;
const int kStatusBarBasePosX = 25;

DSystemInfoView::DSystemInfoView(BRect frame, char* name, uint32 resizingMode, uint32 flags) :
                                BView(frame,name,resizingMode,flags | B_PULSE_NEEDED)
{  
  DSIPlainFont = new BFont();
  DSIPlainFont->SetFamilyAndFace("Swis721 BT",B_REGULAR_FACE);
  DSIPlainFont->SetSize(10);
  
  DSIBoldFont = new BFont();
  DSIBoldFont->SetFamilyAndFace("Swis721 BT",B_BOLD_FACE);
  DSIBoldFont->SetSize(12);

  SetViewColor(clGray);
    
  BString AuxString;
  
  volumeInfo = new BVolume();
  BVolumeRoster volRoster;
  volRoster.Rewind();
  volRoster.GetBootVolume(volumeInfo);
  bootVolume = volumeInfo->Device();
  lastCapacity = 0;
  
  get_system_info(&fSystemInfo);
  
  fGenInfo = new BStringView(BRect(15,kGenInfoBasePosY,130,kGenInfoBasePosY + 13),"GeneralInfo","General Information");
  fGenInfo->SetFont(DSIBoldFont);
  AddChild(fGenInfo);
  fGenInfoBevel = new DBevel(BRect(135,kGenInfoBasePosY + 5,kAppWidth - 16,kGenInfoBasePosY + 6),"GenInfoBevel",kTopLine);
  AddChild(fGenInfoBevel);
  
  AuxString << "Kernel: " << fSystemInfo.kernel_build_date << " " << fSystemInfo.kernel_build_time;
  fKernel = new BStringView(BRect(kStatusBarBasePosX,kGenInfoBasePosY + 19,kStatusBarBasePosX + 150,kGenInfoBasePosY + 29),"Kernel",AuxString.String());
  fKernel->SetFont(DSIPlainFont);
  AuxString.SetTo("");;
  AddChild(fKernel);
  
//  AuxString << "Platform: " << GetPlatformString(fSystemInfo.platform_type);
  AuxString << "Platform: UNIMPLEMENTED";
  fPlatform = new BStringView(BRect(kStatusBarBasePosX + 160,kGenInfoBasePosY + 18,kStatusBarBasePosX + 320,kGenInfoBasePosY + 28),"Platform",AuxString.String());
  fPlatform->SetFont(DSIPlainFont);
  AuxString.SetTo("");
  AddChild(fPlatform);

//  AuxString << "CPU: " << GetCPUString(fSystemInfo.cpu_type);
  AuxString << "CPU: UNIMPLEMENTED";
  fCPU = new BStringView(BRect(kStatusBarBasePosX,kGenInfoBasePosY + 36,kStatusBarBasePosX + 150,kGenInfoBasePosY + 46),"CPU",AuxString.String());
  fCPU->SetFont(DSIPlainFont);
  AuxString.SetTo("");
  AddChild(fCPU);
  
//  AuxString << "CPU clock: " << fSystemInfo.cpu_clock_speed / 1000000 << " MHz.";
  AuxString << "CPU clock: UNIMPLEMENTED";
  fCPUClock = new BStringView(BRect(kStatusBarBasePosX + 160,kGenInfoBasePosY + 36,kStatusBarBasePosX + 320,kGenInfoBasePosY + 46),"CPU Clock",AuxString.String());
  fCPUClock->SetFont(DSIPlainFont);
  AuxString.SetTo("");
  AddChild(fCPUClock);

  AuxString << "Memory amount: " << (fSystemInfo.max_pages * B_PAGE_SIZE) / 1024 /1024 << " MB  (" << fSystemInfo.max_pages * B_PAGE_SIZE << " bytes).";
  fMemoryAmount = new BStringView(BRect(kStatusBarBasePosX,kGenInfoBasePosY + 54,kStatusBarBasePosX + 320,kGenInfoBasePosY + 64),"Bus clock",AuxString.String());
  fMemoryAmount->SetFont(DSIPlainFont);
  AuxString.SetTo("");
  AddChild(fMemoryAmount);
  
  BMenu* Aux = new BMenu("Select a volume");
  ConstructVolumeMenu(Aux);
  Aux->SetFont(DSIPlainFont);
  fFileSystemsMenu = new BMenuField(BRect(kStatusBarBasePosX,kGenInfoBasePosY + 68,kStatusBarBasePosX + 200,kGenInfoBasePosY + 78),"FileSystems","File systems: ",Aux);
  fFileSystemsMenu->SetFont(DSIPlainFont);
  fFileSystemsMenu->SetDivider(70);
  AddChild(fFileSystemsMenu);
  
  fFileSystemSpace = new BStatusBar(BRect(kStatusBarBasePosX + 5,kGenInfoBasePosY + 92,kAppWidth - 15,0),"","");
  fFileSystemSpace->SetBarHeight(12);
  fFileSystemSpace->SetFont(DSIPlainFont);
  fFileSystemSpace->SetBarColor(DarkBlue);
  AddChild(fFileSystemSpace);
  
  fSystemRes = new BStringView(BRect(15,kStatusBarBasePosY - 20,125,kStatusBarBasePosY - 5),"SystemResources","System Resources");
  fSystemRes->SetFont(DSIBoldFont);
  AddChild(fSystemRes);
  fSysResBevel = new DBevel(BRect(130,kStatusBarBasePosY - 13,kAppWidth - 16,kStatusBarBasePosY - 12),"SysResBevel",kTopLine);
  AddChild(fSysResBevel);
  
  fMemStatusBar = new BStatusBar(BRect(kStatusBarBasePosX,kStatusBarBasePosY,kAppWidth - 15,0),"MemStatusBar","Memory pages");
  fMemStatusBar->SetBarHeight(12);
  fMemStatusBar->SetFont(DSIPlainFont);
  AddChild(fMemStatusBar);
  fSemStatusBar = new BStatusBar(BRect(kStatusBarBasePosX,kStatusBarBasePosY + 30,kAppWidth - 15,0),"SemStatusBar","Semaphores");
  fSemStatusBar->SetBarHeight(12);
  fSemStatusBar->SetFont(DSIPlainFont);
  AddChild(fSemStatusBar);
  fPortsStatusBar = new BStatusBar(BRect(kStatusBarBasePosX,kStatusBarBasePosY + 60,kAppWidth - 15,0),"PortsStatusBar","Ports");
  fPortsStatusBar->SetBarHeight(12);
  fPortsStatusBar->SetFont(DSIPlainFont);
  AddChild(fPortsStatusBar);
  fThreadsStatusBar = new BStatusBar(BRect(kStatusBarBasePosX,kStatusBarBasePosY + 90,kAppWidth - 15,0),"ThreadsStatusBar","Threads");
  fThreadsStatusBar->SetBarHeight(12);
  fThreadsStatusBar->SetFont(DSIPlainFont);
  AddChild(fThreadsStatusBar);
  fTeamsStatusBar = new BStatusBar(BRect(kStatusBarBasePosX,kStatusBarBasePosY + 120,kAppWidth - 15,0),"TeamsStatusBar","Teams");
  fTeamsStatusBar->SetBarHeight(12);
  fTeamsStatusBar->SetFont(DSIPlainFont);
  AddChild(fTeamsStatusBar);
}

DSystemInfoView::~DSystemInfoView(void)
{
}

void
DSystemInfoView::SetDevice(dev_t deviceID)
// sets the device to show in the status bar
{
  volumeInfo->SetTo(deviceID);
}

dev_t
DSystemInfoView::GetDevice(void)
// gets the device id
{
  return volumeInfo->Device();
}

void
DSystemInfoView::GetVolName(char* vol)
// gets the name of the volume selected
{
  volumeInfo->GetName(vol);
}

void
DSystemInfoView::RebuildFileSystemMenu(void)
// this is called when a volume is mounted/unmounted
{  
  BMenu* Aux = new BMenu("Select a volume");
  ConstructVolumeMenu(Aux);
  Aux->SetFont(DSIPlainFont);
  fFileSystemsMenu->RemoveSelf();
  delete fFileSystemsMenu;
  fFileSystemsMenu = new BMenuField(BRect(kStatusBarBasePosX,kGenInfoBasePosY + 68,kStatusBarBasePosX + 200,kGenInfoBasePosY + 78),"FileSystems","File systems: ",Aux);
  fFileSystemsMenu->SetFont(DSIPlainFont);
  fFileSystemsMenu->SetDivider(70);
  AddChild(fFileSystemsMenu);
}

int64
DSystemInfoView::VolumeCapacity(void)
// returns the capacity of the volume selected
{
  return volumeInfo->Capacity();
}

int64
DSystemInfoView::VolumeFreeBytes(void)
// returns the free bytes of the volume selected
{
  return volumeInfo->FreeBytes();
}

void
DSystemInfoView::Pulse()
// update the status bars each 500 milisecs
{
  UpdateSystemInfo();
}

void
DSystemInfoView::Draw(BRect updateRect)
// draw some lines in the view
{
  BRect bounds = Bounds();
  SetHighColor(clGray);
  FillRect(bounds);
  BeginLineArray(8);
  AddLine(BPoint(bounds.left,bounds.top),BPoint(bounds.right,bounds.top),colWhite);
//  AddLine(BPoint(bounds.left+1,bounds.top+1),BPoint(bounds.right-1,bounds.top+1),colWhite);
  AddLine(BPoint(bounds.left,bounds.top),BPoint(bounds.left,bounds.bottom),colWhite);
//  AddLine(BPoint(bounds.left+1,bounds.top+1),BPoint(bounds.left+1,bounds.bottom-1),colWhite);
  AddLine(BPoint(bounds.right,bounds.top),BPoint(bounds.right,bounds.bottom),colGray);
//  AddLine(BPoint(bounds.right-1,bounds.top+1),BPoint(bounds.right-1,bounds.bottom-1),colGray);
  AddLine(BPoint(bounds.left,bounds.bottom),BPoint(bounds.right,bounds.bottom),colGray);
//  AddLine(BPoint(bounds.left+1,bounds.bottom-1),BPoint(bounds.right-1,bounds.bottom-1),colGray);
  EndLineArray();
}

void
DSystemInfoView::MessageReceived(BMessage* message)
{ 
  switch(message->what) {
    case kSelectBoot: {          // if a volume is unmounted select the boot volume
      SetDevice(bootVolume);
      UpdateSystemInfo();
      break;
    }
    case kVolumeMoreInfo: {
      BAlert* FSMoreInfo = new BAlert("FSMoreInfo",(char*)GetFSStatDev(),"OK");
      FSMoreInfo->Go();
      break;
    }
    default: BView::MessageReceived(message);
  }
}

void
DSystemInfoView::UpdateSystemInfo(void)
// update the status bars
{
  char volName[20];
  BString label, trailing;
  volumeInfo->GetName(volName);
  int64 Capacity = volumeInfo->Capacity();
  int64 FreeBytes = volumeInfo->FreeBytes();
  label << volName;
  if(Capacity <= 250000000) {
    trailing << (Capacity - FreeBytes) / 1024 << " KB used - " << FreeBytes / 1024 << " KB free - " << Capacity / 1024 << " KB total"; 
  } else {
    trailing << (Capacity - FreeBytes) / 1024 / 1024 << " MB used - " << FreeBytes / 1024 / 1024 << " MB free - " << Capacity / 1024 / 1024 << " MB total"; 
  }
  UpdateFileSystemStatusBar((char*)label.String(),(char*)trailing.String(),Capacity,FreeBytes);

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

void
DSystemInfoView::UpdateFileSystemStatusBar(char* label, char* trailing, float Capacity, float FreeBytes)
// update the file system status bar
{
  fFileSystemSpace->Reset();
  fFileSystemSpace->SetMaxValue((float)Capacity);
  fFileSystemSpace->Update((float)Capacity - FreeBytes,label,trailing);
}

/*char* 
DSystemInfoView::GetPlatformString(platform_type platform)
// gets the platform name
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
}*/

/*char*
DSystemInfoView::GetCPUString(cpu_type cpu)
// gets the CPU name
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
}*/

char*
DSystemInfoView::GetFSStatDev(void)
{
  BString R;
  char* retBuffer = NULL;
  char volName[32];
  fs_info info;
  fs_stat_dev(volumeInfo->Device(),&info);
  volumeInfo->GetName(volName);
  R << "\"" << volName << "\" volume info:\n\n";
  R << "Device ID: " << info.dev << "\nVolume flags:";
  if(info.flags & B_FS_IS_READONLY) R << "\n  - Volume is read-only media";
  if(info.flags & B_FS_IS_REMOVABLE) R << "\n  - Volume is removable media";
  if(info.flags & B_FS_IS_PERSISTENT) R << "\n  - Volume is persistent";
  if(info.flags & B_FS_IS_SHARED) R << "\n  - Volume is shared on a network";
  if(info.flags & B_FS_HAS_MIME) R << "\n  - Volume supports MIME typing system";
  if(info.flags & B_FS_HAS_ATTR) R << "\n  - Volume supports node attributes";
  if(info.flags & B_FS_HAS_QUERY) R << "\n  - Volume supports BeOS query mechanism ";
  R << "\nBolck size: " << info.block_size << "\nIO size: " << info.io_size << "\nTotal blocks: " << info.total_blocks;
  R << "\nFree blocks: " << info.free_blocks << "\nDevice name: " << info.device_name;
  R << "\nVolume name: " << info.volume_name << "\nFile system name: " << info.fsh_name;
  retBuffer = new char[R.Length()];
  strcpy(retBuffer,R.String());
  return retBuffer;
}

void
DSystemInfoView::ConstructVolumeMenu(BMenu* menu)
// contruct the menu field with all the volumes mounted
{
  BVolumeRoster volRoster;
  BVolume* volume = new BVolume();
  BMessage* message;
  char buffer[B_FILE_NAME_LENGTH];
  dev_t DeviceID;
  
  volRoster.Rewind();
  while(volRoster.GetNextVolume(volume) == B_OK) {
    if(volume->IsPersistent()) {
      volume->GetName(buffer);
      DeviceID = volume->Device();
      message = new BMessage(kVolumeMessage);
      message->AddInt32("DevID",DeviceID);
      menu->AddItem(new BMenuItem(buffer,message));
    }
  }
  delete volume;
  menu->SetTargetForItems(this);
}
