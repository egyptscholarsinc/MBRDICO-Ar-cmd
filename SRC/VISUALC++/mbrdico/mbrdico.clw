; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMbrdicoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mbrdico.h"

ClassCount=4
Class1=CMbrdicoApp
Class2=CMbrdicoDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_LOADING
Class4=CLoading
Resource4=IDD_MBRDICO_DIALOG

[CLS:CMbrdicoApp]
Type=0
HeaderFile=mbrdico.h
ImplementationFile=mbrdico.cpp
Filter=N

[CLS:CMbrdicoDlg]
Type=0
HeaderFile=mbrdicoDlg.h
ImplementationFile=mbrdicoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_COMBO1

[CLS:CAboutDlg]
Type=0
HeaderFile=mbrdicoDlg.h
ImplementationFile=mbrdicoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308353

[DLG:IDD_MBRDICO_DIALOG]
Type=1
Class=CMbrdicoDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_COMBO1,combobox,1344339970
Control5=IDC_CHECK1,button,1342242819

[DLG:IDD_LOADING]
Type=1
Class=CLoading
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CLoading]
Type=0
HeaderFile=Loading.h
ImplementationFile=Loading.cpp
BaseClass=CDialog
Filter=D

