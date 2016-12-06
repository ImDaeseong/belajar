; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMusicPlay
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "pikabelajar.h"

ClassCount=10
Class1=CPikabelajarApp
Class2=CPikabelajarDlg

ResourceCount=10
Resource2=IDD_PIKABELAJAR_DIALOG
Resource3=IDD_DIALOG_HINTVIEW (English (U.S.))
Resource1=IDR_MAINFRAME
Class3=CPikabelajrInDlg
Resource4=IDD_PIKABELAJAR_DIALOG (English (U.S.))
Class4=PreviewDlg
Resource5=IDD_DIALOG_NOTICE (English (U.S.))
Class5=HintviewDlg
Resource6=IDD_DIALOG_PLAY (English (U.S.))
Class6=NoticeDlg
Class7=HidebtnDlg
Resource7=IDD_PIKABELAJARIN_DIALOG (English (U.S.))
Class8=ResultDlg
Resource8=IDD_DIALOG_RESULT (English (U.S.))
Class9=CMusicPlay
Resource9=IDD_DIALOG_PREVIEW (English (U.S.))
Class10=CMusicPlayLayerDlg
Resource10=IDD_DIALOG_PLAYLAYER (English (U.S.))

[CLS:CPikabelajarApp]
Type=0
HeaderFile=pikabelajar.h
ImplementationFile=pikabelajar.cpp
Filter=N

[CLS:CPikabelajarDlg]
Type=0
HeaderFile=pikabelajarDlg.h
ImplementationFile=pikabelajarDlg.cpp
Filter=D
LastObject=CPikabelajarDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_PIKABELAJAR_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CPikabelajarDlg

[DLG:IDD_PIKABELAJAR_DIALOG (English (U.S.))]
Type=1
Class=CPikabelajarDlg
ControlCount=15
Control1=IDC_BUTTON_CLOSE,button,1342242816
Control2=IDC_BUTTON_LEFT,button,1342242816
Control3=IDC_BUTTON_RIGHT,button,1342242816
Control4=IDC_BUTTON_SUARALAKI,button,1342242816
Control5=IDC_BUTTON_SUARAPUTRI,button,1342242816
Control6=IDC_BUTTON_SETTING1,button,1342242816
Control7=IDC_BUTTON_SETTING2,button,1342242816
Control8=IDC_BUTTON_SETTING3,button,1342242816
Control9=IDC_BUTTON_SETTING4,button,1342242816
Control10=IDC_BUTTON_SETTING5,button,1342242816
Control11=IDC_BUTTON_YM1,button,1342242816
Control12=IDC_BUTTON_YM2,button,1342242816
Control13=IDC_BUTTON_YOUTUBE,button,1342242816
Control14=IDC_BUTTON_FACEBOOK,button,1342242816
Control15=IDC_BUTTON_MUSIC,button,1342242816

[DLG:IDD_PIKABELAJARIN_DIALOG (English (U.S.))]
Type=1
Class=CPikabelajrInDlg
ControlCount=15
Control1=IDC_STATIC_SPLASH,static,1342308352
Control2=IDC_STATIC_BANNER,static,1342308352
Control3=IDC_STATIC_DISPICTURE,static,1342308352
Control4=IDC_STATIC_TANYA,static,1342308352
Control5=IDC_STATIC_JAWAB1,static,1342308352
Control6=IDC_STATIC_JAWAB2,static,1342308352
Control7=IDC_STATIC_JAWAB3,static,1342308352
Control8=IDC_STATIC_JAWAB4,static,1342308352
Control9=IDC_BUTTON_JAWAB1,button,1342177280
Control10=IDC_BUTTON_JAWAB2,button,1342177280
Control11=IDC_BUTTON_JAWAB3,button,1342177280
Control12=IDC_BUTTON_JAWAB4,button,1342177280
Control13=IDC_BUTTON_TANYA,button,1342177280
Control14=IDC_BUTTON_ZOOM,button,1342177280
Control15=IDC_STATIC_HINTIMAGE,static,1342308352

[CLS:CPikabelajrInDlg]
Type=0
HeaderFile=PikabelajrInDlg.h
ImplementationFile=PikabelajrInDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CPikabelajrInDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_PREVIEW (English (U.S.))]
Type=1
Class=PreviewDlg
ControlCount=2
Control1=IDC_STATIC_PREVIEW,static,1342308352
Control2=IDC_IMAGE,static,1342177294

[CLS:PreviewDlg]
Type=0
HeaderFile=PreviewDlg.h
ImplementationFile=PreviewDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_CLOSE
VirtualFilter=dWC

[CLS:HintviewDlg]
Type=0
HeaderFile=HintviewDlg.h
ImplementationFile=HintviewDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=HintviewDlg

[DLG:IDD_DIALOG_HINTVIEW (English (U.S.))]
Type=1
Class=HintviewDlg
ControlCount=2
Control1=IDC_STATIC_PREVIEW,static,1342308352
Control2=IDC_IMAGE,static,1342177294

[DLG:IDD_DIALOG_NOTICE (English (U.S.))]
Type=1
Class=NoticeDlg
ControlCount=0

[CLS:NoticeDlg]
Type=0
HeaderFile=NoticeDlg.h
ImplementationFile=NoticeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=NoticeDlg

[CLS:HidebtnDlg]
Type=0
HeaderFile=HidebtnDlg.h
ImplementationFile=HidebtnDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=HidebtnDlg

[DLG:IDD_DIALOG_RESULT (English (U.S.))]
Type=1
Class=ResultDlg
ControlCount=5
Control1=IDC_STATIC_MESSAGE,static,1342308352
Control2=IDC_STATIC_MESSAGE2,static,1342308352
Control3=IDC_STATIC_MESSAGE3,static,1342308352
Control4=IDC_BUTTON_ULANG,button,1342242816
Control5=IDC_BUTTON_LANGJUT,button,1342242816

[CLS:ResultDlg]
Type=0
HeaderFile=ResultDlg.h
ImplementationFile=ResultDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_LANGJUT
VirtualFilter=dWC

[CLS:CMusicPlay]
Type=0
HeaderFile=MusicPlay.h
ImplementationFile=MusicPlay.cpp
BaseClass=CDialog
Filter=D
LastObject=CMusicPlay
VirtualFilter=dWC

[DLG:IDD_DIALOG_PLAY (English (U.S.))]
Type=1
Class=CMusicPlay
ControlCount=12
Control1=IDC_STATIC_SEARCH,static,1342308352
Control2=IDC_STATIC_TIME,static,1342308352
Control3=IDC_STATIC_BANNER,static,1342308352
Control4=IDC_VOLUME,msctls_trackbar32,1208025112
Control5=IDC_BUTTON_PLAYSTOP,button,1208025088
Control6=IDC_BUTTON_PHILIHFOLDER,button,1342242816
Control7=IDC_BUTTON_SUARAMIN,button,1342242816
Control8=IDC_BUTTON_SUARAPLUS,button,1342242816
Control9=IDC_BUTTON_PLAY,button,1342242816
Control10=IDC_BUTTON_PLAYLEFT,button,1342242816
Control11=IDC_BUTTON_PLAYNEXT,button,1342242816
Control12=IDC_SLIDER1,msctls_trackbar32,1342177304

[CLS:CMusicPlayLayerDlg]
Type=0
HeaderFile=MusicPlayLayerDlg.h
ImplementationFile=MusicPlayLayerDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMusicPlayLayerDlg

[DLG:IDD_DIALOG_PLAYLAYER (English (U.S.))]
Type=1
Class=CMusicPlayLayerDlg
ControlCount=0

