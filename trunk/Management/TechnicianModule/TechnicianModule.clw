; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=3
Class1=CTechnicianModuleApp
LastClass=CTechnicianDlg
NewFileInclude2=#include "TechnicianModule.h"
ResourceCount=2
NewFileInclude1=#include "stdafx.h"
Class2=CTechnicianDlg
LastTemplate=CDialog
Resource1=IDD_MAIN_DIALOG
Class3=CAddRoomDlg
Resource2=IDD_ADD_ROOM_DIALOG

[CLS:CTechnicianModuleApp]
Type=0
HeaderFile=TechnicianModule.h
ImplementationFile=TechnicianModule.cpp
Filter=N

[DLG:IDD_MAIN_DIALOG]
Type=1
Class=CTechnicianDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EXPORT,button,1342242817
Control4=IDC_SETTING,button,1342242817
Control5=IDC_TAB_STAGE,SysTabControl32,1342177536
Control6=IDC_CUSTOM,static,1342308352
Control7=IDC_BTN_ADD_RT,button,1342242816
Control8=IDC_TREE_ROOMNAME,SysTreeView32,1350631431
Control9=IDC_IMPORT,button,1342242817

[CLS:CTechnicianDlg]
Type=0
HeaderFile=TechnicianDlg.h
ImplementationFile=TechnicianDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_TREE_ROOMNAME

[DLG:IDD_ADD_ROOM_DIALOG]
Type=1
Class=CAddRoomDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_ROOM_NAME,static,1342308352
Control4=IDC_EDIT_ROOM_NAME,edit,1350631552
Control5=IDC_STATIC_CON_METHOD,static,1342308352
Control6=IDC_COMBO_CON_METHOD,combobox,1344339971

[CLS:CAddRoomDlg]
Type=0
HeaderFile=AddRoomDlg.h
ImplementationFile=AddRoomDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAddRoomDlg

