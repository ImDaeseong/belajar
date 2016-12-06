# Microsoft Developer Studio Project File - Name="pikabelajarRes" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=pikabelajarRes - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pikabelajarRes.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pikabelajarRes.mak" CFG="pikabelajarRes - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pikabelajarRes - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "pikabelajarRes - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pikabelajarRes - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PIKABELAJARRES_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PIKABELAJARRES_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "pikabelajarRes - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PIKABELAJARRES_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PIKABELAJARRES_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "pikabelajarRes - Win32 Release"
# Name "pikabelajarRes - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\pikabelajarRes.cpp
# End Source File
# Begin Source File

SOURCE=.\pikabelajarRes.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\defineres.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\12_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\12_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\13_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\13_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\14_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\14_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\15_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\15_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\16_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\16_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\17_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\17_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\18_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\18_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\19_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\19_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\1_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\20_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\20_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Admin Log Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Admin Log_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Admin Log_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\admin pass1.gif"
# End Source File
# Begin Source File

SOURCE=".\admin pass2.gif"
# End Source File
# Begin Source File

SOURCE=".\client\admin pass_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\admin pass_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client\admin pass_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc10_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc10_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc11_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc11_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc12_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc12_Kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc13_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc13_Kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc14_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc14_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc15_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc15_Kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc16_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc16_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc17_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc17_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc18_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc18_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc19_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc19_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc1_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc1_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc20_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc20_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc2_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc2_Kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc3_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc3_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc4_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc4_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc5_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc5_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc6_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc6_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc7_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc7_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc8_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc8_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc9_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC\aturPc9_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Authorityadminboleh_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2-hint\Authorityadminboleh_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Authorityadminboleh_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Authorityadminmenu_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2-hint\Authorityadminmenu_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Authorityadminmenu_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Auto Lock Screen_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Auto Lock Screen_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Auto Shutdown_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Auto Shutdown_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Berhasil BlokSitus ditandai_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Berhasil BlokSitus ditandai_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Blink tabel_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Blink tabel_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\block drive_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Block gunakan postpay_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Block gunakan postpay_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Block gunakan postpay_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\block login postpay di client_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\block login postpay di client_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\block login postpay di client_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\blok daftar_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2-hint\blok daftar_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\blok daftar_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\blok drive1.gif"
# End Source File
# Begin Source File

SOURCE=".\blok drive2.gif"
# End Source File
# Begin Source File

SOURCE=".\client\blok drive_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client\blok drive_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Blok member hutang_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2-hint\Blok member hutang_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Blok member hutang_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\blok program1.gif"
# End Source File
# Begin Source File

SOURCE=".\blok program2.gif"
# End Source File
# Begin Source File

SOURCE=".\client\blok program_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\blok program_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client\blok program_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\BlokSitus bisa install kalau_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\BlokSitus bisa install kalau_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Bonus Waktu_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Bonus Waktu_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Bonus Waktu_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Buku kas_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\buku kas_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Button repay_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Button repay_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Button urut_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Button urut_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Cari user & View message_besar Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Cari user & View message_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Cari user & View message_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Cetaknota_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2-hint\Cetaknota_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Cetaknota_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\client status_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2-hint\client status_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\client status_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Ctk lap singkat_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Ctk lap singkat_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Custom display Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Custom display_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Custom display_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Daftar member Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Daftar member_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Daftar member_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Daftar penjualan Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Daftar penjualan_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Daftar penjualan_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\DB Backup_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2-hint\DB Backup_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\DB Backup_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\DeepFreeze yang bisa dikontrol _besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\DeepFreeze yang bisa dikontrol _kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\default.gif
# End Source File
# Begin Source File

SOURCE=".\client\detail biaya_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\detail biaya_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client\detail biaya_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Detail member Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Detail member_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Detail member_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Detail transfer-terima_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Detail transfer-terima_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2-hint\fungsi client_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Fungsi Login paket di client_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Fungsi Login paket di client_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Fungsi Login paket di client_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Fungsi refund Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Fungsi refund_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Fungsi refund_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\client_2\fungsi_besar.gif
# End Source File
# Begin Source File

SOURCE=.\client_2\fungsi_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\HARGA\Funsi Paket Shortcut_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Funsi Paket Shortcut_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Funsi Paket Shortcut_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Grafik member_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Grafik member_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2-hint\Gratis minimum hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Gratis minimum_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Gratis minimum_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\halaman admin_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2-hint\halaman admin_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\halaman admin_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\client\Hardware_besar.gif
# End Source File
# Begin Source File

SOURCE=".\client-hint\Hardware_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\client\Hardware_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\HARGA\Hasil selesai otomatis di tab belum bayar_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Hasil selesai otomatis di tab belum bayar_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Hasil selesai otomatis di tab belum bayar_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Hide sidebar Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Hide sidebar_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Hide sidebar_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2-hint\Hint Buku kas.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2-hint\Hint Button produk.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2-hint\Hint Button repay.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2-hint\Hint Ctk lap singkat_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2-hint\Hint Detail member.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2-hint\Hint grafik member.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2-hint\Hint Informasi penjualan.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2-hint\Hint Log member.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2-hint\Hint Manajemen warnet.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2-hint\Hint Tambah antrian.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\Hint1.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint1.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint10.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint10.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint11.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint11.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint12.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint12.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint13.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint13.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint14.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint14.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint15.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint15.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint16.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint16.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\Hint17.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint17.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\Hint18.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint18.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint19.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint19.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint2.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint2.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint20.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint20.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint3.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint3.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint4.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint4.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint5.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint5.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint6.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint6.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint7.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint7.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint8.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint8.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC-hint\hint9.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN-hint\Hint9.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2-hint\hint_Berhasil BlokSitus ditandai.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2-hint\hint_BlokSitus bisa install kalau.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2-hint\hint_DeepFreeze yang bisa dikontrol.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2-hint\Hint_Password DeepFreeze harus.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2-hint\hint_Penulisan URL website.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2-hint\hint_pikaBlockPackage.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2-hint\hint_PIKABlokPackage untuk.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2-hint\hint_Tombol BlokSitus notepad.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2-hint\hint_Tombol Normal Mode Shadow.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2-hint\hint_Window Install Blok Situs.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Informasi penjualan_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Informasi penjualan_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Input produk Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Input produk_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Input produk_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\intro.gif
# End Source File
# Begin Source File

SOURCE=.\intro2.gif
# End Source File
# Begin Source File

SOURCE=.\intro3.gif
# End Source File
# Begin Source File

SOURCE=".\client\jalankan program_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\jalankan program_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client\jalankan program_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Jumlah Diskon_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Jumlah Diskon_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Jumlah Diskon_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Kas Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\kas_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\kas_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\client\kategori_besar.gif
# End Source File
# Begin Source File

SOURCE=".\client-hint\kategori_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\client\kategori_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\HARGA_2-hint\Kelipatan harga Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2-hint\Kelipatan harga3000 hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Kelipatan harga3000_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Kelipatan harga3000_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Kelipatan harga_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Kelipatan harga_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2-hint\Kode paket hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Kode paket_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Kode paket_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2-hint\kolom pc_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\client_2\kolom_besar.gif
# End Source File
# Begin Source File

SOURCE=.\client_2\kolom_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\HARGA\Letak diseble postpay_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Letak diseble postpay_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Letak diseble postpay_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Letak Log Kode_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Letak Log Kode_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Letak Log Kode_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Letak seting postpay dari client_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Letak seting postpay dari client_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Letak seting postpay dari client_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Log member_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Log member_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2-hint\Login bebas hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Login bebas_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Login bebas_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\client\logout_besar.gif
# End Source File
# Begin Source File

SOURCE=".\client-hint\logout_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\client\logout_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Managemen DB_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2-hint\Managemen DB_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Managemen DB_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Manajemen CD Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Manajemen CD_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Manajemen CD_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Manajemen hutang Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Manajemen hutang_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Manajemen hutang_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\manajemen warnet_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\manajemen warnet_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Member Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Member_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Member_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Membuat Kode Vocher_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Membuat Kode Vocher_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Membuat Kode Vocher_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\menu konfigurasi_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2-hint\menu konfigurasi_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\menu konfigurasi_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\client\minimize_besar.gif
# End Source File
# Begin Source File

SOURCE=".\client-hint\minimize_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\client\minimize_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\mode pause_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\mode pause_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Mode selesai client_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Mode selesai client_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client\mulai gratis_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\mulai gratis_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client\mulai gratis_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\nama member Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\nama member_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\nama member_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client\option client_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\option client_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client\option client_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2-hint\Paket event hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2-hint\Paket event tanda hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Paket event tanda_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Paket event tanda_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Paket event_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Paket event_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Paket special_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2-hint\Paket spesial hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Paket spesial_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Password DeepFreeze harus_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Password DeepFreeze harus_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\client\pause_besar.gif
# End Source File
# Begin Source File

SOURCE=".\client-hint\pause_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\client\pause_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Penulisan URL website_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Penulisan URL website_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\pikaBlockPackage_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\pikaBlockPackage_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\PIKABlokPackage untuk_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\PIKABlokPackage untuk_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client\pilih client_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\pilih client_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client\pilih client_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client\pindah pc_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\pindah pc_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client\pindah pc_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Prepay member Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Prepay member_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Prepay member_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\previewhint.gif
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Produk batal Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\produk batal_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\produk batal_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\client_2\remote_besar.gif
# End Source File
# Begin Source File

SOURCE=".\client_2-hint\remote_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\client_2\remote_kecil.gif
# End Source File
# Begin Source File

SOURCE=.\client\resolusi_besar.gif
# End Source File
# Begin Source File

SOURCE=".\client-hint\resolusi_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\client\resolusi_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\HARGA\Saat paket habis menjadi selesai_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Saat paket habis menjadi selesai_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Saat paket habis menjadi selesai_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\client\security_besar.gif
# End Source File
# Begin Source File

SOURCE=".\client-hint\security_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\client\security_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Server manajemen_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Server manajemen_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Set Admin_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Set Admin_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client\set IP_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\set IP_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client\set IP_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\set notice pc user_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\set notice pc user_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Set Notice_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2-hint\Set Notice_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Set Notice_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Set print scanner_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Set print scanner_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\set printer default_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2-hint\set printer default_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\set printer default_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Set Server - Set Basic_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Set Server - Set Basic_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Set Sound_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2-hint\Set Sound_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Set Sound_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client\Set wallpaper_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\set wallpaper_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client\set wallpaper_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Harga Kode Paket_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Seting Harga Kode Paket_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Harga Kode Paket_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Harga siang dan malam_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Seting Harga siang dan malam_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Harga siang dan malam_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Paket Durasi_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Seting Paket Durasi_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Paket Durasi_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Paket Event_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Seting Paket Event_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Paket Event_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Paket Jam_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Seting Paket Jam_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Paket Jam_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Paket Member_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Seting Paket Member_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Seting Paket Member_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\HARGA\setpostpay_besar.gif
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\setpostpay_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\HARGA\setpostpay_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\HARGA\Shortcut Paket_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA-hint\Shortcut Paket_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA\Shortcut Paket_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\skin Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Skin Warna Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\skin warna_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\skin warna_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\skin_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Skin_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\client\software_besar.gif
# End Source File
# Begin Source File

SOURCE=".\client-hint\software_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\client\software_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Susunan quick menu_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2-hint\Susunan quick menu_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN_2\Susunan quick menu_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\table size_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2-hint\table size_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\table size_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Tambah antrian_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET_2\Tambah antrian_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2-hint\Tampilan login bebas hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Tampilan login bebas_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Tampilan login bebas_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client\tampilan tabel_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client-hint\tampilan tabel_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client\tampilan tabel_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\tampilan table_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2-hint\tampilan table_hint.gif"
# End Source File
# Begin Source File

SOURCE=".\client_2\tampilan table_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2-hint\Tarif per unit hint.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Tarif per unit_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\HARGA_2\Tarif per unit_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Tombol BlokSitus notepad_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Tombol BlokSitus notepad_Kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Tombol Normal Mode Shadow_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Tombol Normal Mode Shadow_kecil.gif"
# End Source File
# Begin Source File

SOURCE=.\client_2\total_besar.gif
# End Source File
# Begin Source File

SOURCE=".\client_2-hint\total_hint.gif"
# End Source File
# Begin Source File

SOURCE=.\client_2\total_kecil.gif
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Transfer terima Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Transfer terima_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Transfer terima_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET-hint\Tutup buku dan melihat laporan Hint.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Tutup buku dan melihat laporan_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\MANAJEMEN WARNET\Tutup buku dan melihat laporan_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Tutup Buku_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\SERVER MANAJEMEN\Tutup Buku_kecil.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Window Install Blok Situs_besar.gif"
# End Source File
# Begin Source File

SOURCE=".\ATUR PC_2\Window Install Blok Situs_kecil.gif"
# End Source File
# End Group
# Begin Source File

SOURCE=.\client.lst
# End Source File
# Begin Source File

SOURCE=.\zzz.png
# End Source File
# End Target
# End Project
