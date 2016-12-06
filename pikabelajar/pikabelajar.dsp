# Microsoft Developer Studio Project File - Name="pikabelajar" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=pikabelajar - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pikabelajar.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pikabelajar.mak" CFG="pikabelajar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pikabelajar - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "pikabelajar - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pikabelajar - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "pikabelajar - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "pikabelajar - Win32 Release"
# Name "pikabelajar - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CScrollTextStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\Func.cpp
# End Source File
# Begin Source File

SOURCE=.\GdipButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GdipButtonex.cpp
# End Source File
# Begin Source File

SOURCE=.\HintviewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\KbcBmp.cpp
# End Source File
# Begin Source File

SOURCE=.\KbcButton.cpp
# End Source File
# Begin Source File

SOURCE=.\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftPictureStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicPlayLayerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NoticeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PhotoPictureStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\pikabelajar.cpp
# End Source File
# Begin Source File

SOURCE=.\pikabelajar.rc
# End Source File
# Begin Source File

SOURCE=.\pikabelajarDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PikabelajrInDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PreviewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PreViewImage.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourcBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourcBitmapgif.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinButton.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashScreenEx.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TransparentImage.cpp
# End Source File
# Begin Source File

SOURCE=.\TransparentLink.cpp
# End Source File
# Begin Source File

SOURCE=.\TransparentStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowTransparent.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CGdiPlusBitmap.h
# End Source File
# Begin Source File

SOURCE=.\CScrollTextStatic.h
# End Source File
# Begin Source File

SOURCE=.\Func.h
# End Source File
# Begin Source File

SOURCE=.\GdipButton.h
# End Source File
# Begin Source File

SOURCE=.\GdipButtonex.h
# End Source File
# Begin Source File

SOURCE=.\HintviewDlg.h
# End Source File
# Begin Source File

SOURCE=.\KbcBmp.h
# End Source File
# Begin Source File

SOURCE=.\KbcButton.h
# End Source File
# Begin Source File

SOURCE=.\Label.h
# End Source File
# Begin Source File

SOURCE=.\LeftPictureStatic.h
# End Source File
# Begin Source File

SOURCE=.\MusicPlay.h
# End Source File
# Begin Source File

SOURCE=.\MusicPlayLayerDlg.h
# End Source File
# Begin Source File

SOURCE=.\NoticeDlg.h
# End Source File
# Begin Source File

SOURCE=.\PhotoPictureStatic.h
# End Source File
# Begin Source File

SOURCE=.\PictureStatic.h
# End Source File
# Begin Source File

SOURCE=.\pikabelajar.h
# End Source File
# Begin Source File

SOURCE=.\pikabelajarDlg.h
# End Source File
# Begin Source File

SOURCE=.\PikabelajrInDlg.h
# End Source File
# Begin Source File

SOURCE=.\PreviewDlg.h
# End Source File
# Begin Source File

SOURCE=.\PreViewImage.h
# End Source File
# Begin Source File

SOURCE=.\ResourcBitmap.h
# End Source File
# Begin Source File

SOURCE=.\ResourcBitmapgif.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ResultDlg.h
# End Source File
# Begin Source File

SOURCE=.\SkinButton.h
# End Source File
# Begin Source File

SOURCE=.\SplashScreenEx.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TransparentImage.h
# End Source File
# Begin Source File

SOURCE=.\TransparentLink.h
# End Source File
# Begin Source File

SOURCE=.\TransparentStatic.h
# End Source File
# Begin Source File

SOURCE=.\WindowTransparent.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Pic\1.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\10.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\11.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\2.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\3.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\4.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\5.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\6.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\7.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\8.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\9.gif
# End Source File
# Begin Source File

SOURCE=".\res\Pic\Admin Client.gif"
# End Source File
# Begin Source File

SOURCE=.\res\closebtn.gif
# End Source File
# Begin Source File

SOURCE=.\res\CLOSEBUTTON.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor.ico
# End Source File
# Begin Source File

SOURCE=.\res\default.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\Dragon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\inback.GIF
# End Source File
# Begin Source File

SOURCE=.\res\intro.gif
# End Source File
# Begin Source File

SOURCE=.\res\New_nosmoke1.gif
# End Source File
# Begin Source File

SOURCE=.\res\pikabelajar.ico
# End Source File
# Begin Source File

SOURCE=.\res\pikabelajar.rc2
# End Source File
# Begin Source File

SOURCE=.\res\skin.gif
# End Source File
# Begin Source File

SOURCE=.\res\slidebutton\SLIDER_VOLUME_FILL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\slidebutton\SLIDER_VOLUME_KNOB.BMP
# End Source File
# Begin Source File

SOURCE=.\res\splash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StandPoint_btn_001.gif
# End Source File
# Begin Source File

SOURCE=.\res\StandPoint_btn_002.gif
# End Source File
# Begin Source File

SOURCE=.\res\StandPoint_btn_003.gif
# End Source File
# Begin Source File

SOURCE=.\res\StandPoint_btn_004.gif
# End Source File
# Begin Source File

SOURCE=.\res\StandPoint_btn_008.gif
# End Source File
# Begin Source File

SOURCE=.\res\Pic\StandPoint_btn_008_1.gif
# End Source File
# Begin Source File

SOURCE=.\res\StandPoint_btn_008_1.gif
# End Source File
# Begin Source File

SOURCE=.\res\StandPoint_btn_008_2.gif
# End Source File
# Begin Source File

SOURCE=.\res\StandPoint_btn_008_3.gif
# End Source File
# End Group
# Begin Group "play"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\play\AudioPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\play\AudioPlayer.h
# End Source File
# Begin Source File

SOURCE=.\play\MP3Info.cpp
# End Source File
# Begin Source File

SOURCE=.\play\MP3Info.h
# End Source File
# End Group
# Begin Group "Banner"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Banner\BannerStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\Banner\BannerStatic.h
# End Source File
# Begin Source File

SOURCE=.\Banner\ColorString.cpp
# End Source File
# Begin Source File

SOURCE=.\Banner\ColorString.h
# End Source File
# Begin Source File

SOURCE=.\Banner\MultiColorStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\Banner\MultiColorStatic.h
# End Source File
# End Group
# Begin Group "zsliderctrl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\zsliderctrl\ZipBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\zsliderctrl\ZipBitmap.h
# End Source File
# Begin Source File

SOURCE=.\zsliderctrl\ZipSliderCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\zsliderctrl\ZipSliderCtl.h
# End Source File
# End Group
# Begin Source File

SOURCE=".\res\1-1.png"
# End Source File
# Begin Source File

SOURCE=.\res\1.PNG
# End Source File
# Begin Source File

SOURCE=.\res\2.PNG
# End Source File
# Begin Source File

SOURCE=.\res\3.PNG
# End Source File
# Begin Source File

SOURCE=.\res\4.PNG
# End Source File
# Begin Source File

SOURCE=.\res\AA.png
# End Source File
# Begin Source File

SOURCE=.\res\addfiles2.png
# End Source File
# Begin Source File

SOURCE=.\res\aturpc.png
# End Source File
# Begin Source File

SOURCE=.\res\BB.png
# End Source File
# Begin Source File

SOURCE=.\res\ADI\Benar.wav
# End Source File
# Begin Source File

SOURCE=.\res\Desita\Benar.wav
# End Source File
# Begin Source File

SOURCE=.\res\Putri\Benar.wav
# End Source File
# Begin Source File

SOURCE=.\res\Benar_Ipul.wav
# End Source File
# Begin Source File

SOURCE=.\res\Benar_putri.wav
# End Source File
# Begin Source File

SOURCE=.\res\btn_arrowL.png
# End Source File
# Begin Source File

SOURCE=.\res\btn_arrowR.png
# End Source File
# Begin Source File

SOURCE=.\res\btn_arrowR2.png
# End Source File
# Begin Source File

SOURCE=.\res\btn_close.png
# End Source File
# Begin Source File

SOURCE=.\res\btn_main_close.png
# End Source File
# Begin Source File

SOURCE=.\res\bw.png
# End Source File
# Begin Source File

SOURCE=.\res\CC.png
# End Source File
# Begin Source File

SOURCE=.\res\client.png
# End Source File
# Begin Source File

SOURCE=.\res\DD.png
# End Source File
# Begin Source File

SOURCE=.\res\FW.png
# End Source File
# Begin Source File

SOURCE=.\res\harga.png
# End Source File
# Begin Source File

SOURCE=.\res\inback.png
# End Source File
# Begin Source File

SOURCE=".\res\ADI\Jumpa lagi.wav"
# End Source File
# Begin Source File

SOURCE=.\res\man.png
# End Source File
# Begin Source File

SOURCE=.\res\managerwarnet.png
# End Source File
# Begin Source File

SOURCE=.\res\min.png
# End Source File
# Begin Source File

SOURCE=.\res\music.png
# End Source File
# Begin Source File

SOURCE=.\res\next.png
# End Source File
# Begin Source File

SOURCE=.\res\notice.png
# End Source File
# Begin Source File

SOURCE=.\res\noticeA.png
# End Source File
# Begin Source File

SOURCE=.\res\noticeB.png
# End Source File
# Begin Source File

SOURCE=.\res\noticeC.png
# End Source File
# Begin Source File

SOURCE=.\res\noticeD.png
# End Source File
# Begin Source File

SOURCE=.\res\outback.png
# End Source File
# Begin Source File

SOURCE=.\res\plus.png
# End Source File
# Begin Source File

SOURCE=.\res\pp1.png
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\result.png
# End Source File
# Begin Source File

SOURCE=.\res\ADI\Salah.wav
# End Source File
# Begin Source File

SOURCE=.\res\Desita\Salah.wav
# End Source File
# Begin Source File

SOURCE=.\res\Putri\Salah.wav
# End Source File
# Begin Source File

SOURCE=.\res\Salah_ipul.wav
# End Source File
# Begin Source File

SOURCE=.\res\Salah_putri.wav
# End Source File
# Begin Source File

SOURCE=".\res\Desita\sampai jumpa lagi.wav"
# End Source File
# Begin Source File

SOURCE=".\res\Putri\Sampai jumpa lagi.wav"
# End Source File
# Begin Source File

SOURCE=".\res\ADI\Selamat datang.wav"
# End Source File
# Begin Source File

SOURCE=".\res\Desita\Selamat datang.wav"
# End Source File
# Begin Source File

SOURCE=".\res\Putri\Selamat datang.wav"
# End Source File
# Begin Source File

SOURCE=.\res\servermanager.png
# End Source File
# Begin Source File

SOURCE=.\res\set1.png
# End Source File
# Begin Source File

SOURCE=.\res\SETFB.png
# End Source File
# Begin Source File

SOURCE=.\res\SETPLAYER.png
# End Source File
# Begin Source File

SOURCE=.\res\SETPLAYER_STOP.png
# End Source File
# Begin Source File

SOURCE=.\res\SETYM1.png
# End Source File
# Begin Source File

SOURCE=.\res\SETYM2.png
# End Source File
# Begin Source File

SOURCE=.\res\SETYOUTUBE.png
# End Source File
# Begin Source File

SOURCE=.\res\SKIN1_layer.png
# End Source File
# Begin Source File

SOURCE=.\res\SKIN2_in.png
# End Source File
# Begin Source File

SOURCE=.\res\ulangi.png
# End Source File
# Begin Source File

SOURCE=.\res\woman.png
# End Source File
# Begin Source File

SOURCE=.\res\ZOOM.png
# End Source File
# Begin Source File

SOURCE=.\res\zzz.png
# End Source File
# End Target
# End Project
