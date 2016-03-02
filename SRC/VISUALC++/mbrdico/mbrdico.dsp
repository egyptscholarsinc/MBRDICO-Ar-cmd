# Microsoft Developer Studio Project File - Name="mbrdico" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=mbrdico - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mbrdico.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mbrdico.mak" CFG="mbrdico - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mbrdico - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "mbrdico - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mbrdico - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "../../Include/" /I "../../VISUALC++/mbrolatools" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../../../BINARY/mbrdico.exe"

!ELSEIF  "$(CFG)" == "mbrdico - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "../../Include/" /I "../../VISUALC++/mbrolatools" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../../../BINARY/mbrdico.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "mbrdico - Win32 Release"
# Name "mbrdico - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "TTS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Letter2Phone\DecisionTree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Engine\Dictionary.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Letter2Phone\Feature.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Letter2Phone\Letter2Phone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Letter2Phone\letter2phonelr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Letter2Phone\letter2phonerl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\PhoFile\LPhonemePlus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\PhoFile\LPitchPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\PhoFile\Phoneme.cpp
# End Source File
# Begin Source File

SOURCE=..\..\PhoFile\PhonemePlus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\PhoFile\PitchPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Engine\Speak.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Engine\SpeakAmerican.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Engine\SpeakArabic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Engine\SpeakFrench.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Engine\VpError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Engine\ZPhoneme.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\loading.cpp
# End Source File
# Begin Source File

SOURCE=.\mbrdico.cpp
# End Source File
# Begin Source File

SOURCE=.\mbrdico.rc
# End Source File
# Begin Source File

SOURCE=.\mbrdicodlg.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\txt2speech.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\Include\DecisionTree.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\Dictionary.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\Feature.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\Letter2Phone.hpp
# End Source File
# Begin Source File

SOURCE=.\loading.h
# End Source File
# Begin Source File

SOURCE=..\..\Include\LPhonemePlus.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\LPitchPoint.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\LToken.hpp
# End Source File
# Begin Source File

SOURCE=.\mbrdico.h
# End Source File
# Begin Source File

SOURCE=.\mbrdicoDlg.h
# End Source File
# Begin Source File

SOURCE=..\mbrolatools\mbrplay.h
# End Source File
# Begin Source File

SOURCE="..\VISUALC++\mbrolatools\mbrplay.h"
# End Source File
# Begin Source File

SOURCE=..\..\Include\Phoneme.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\PhonemePlus.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\PitchPoint.hpp
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\Include\Speak.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\SpeakAmerican.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\SpeakArabic.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\SpeakFrench.hpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\txt2speech.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\VpError.hpp
# End Source File
# Begin Source File

SOURCE=..\..\Include\ZPhoneme.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\mbrdico.ico
# End Source File
# Begin Source File

SOURCE=.\res\mbrdico.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\mbrolatools\mbrplay.lib
# End Source File
# End Target
# End Project
