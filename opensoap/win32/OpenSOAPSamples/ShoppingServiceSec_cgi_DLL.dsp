# Microsoft Developer Studio Project File - Name="ShoppingServiceSec_cgi_DLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** �ҏW���Ȃ��ł������� **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ShoppingServiceSec_cgi_DLL - Win32 Debug
!MESSAGE ����͗L����Ҳ�̧�قł͂���܂���B ������ۼު�Ă�����ނ��邽�߂ɂ� NMAKE ���g�p���Ă��������B
!MESSAGE [Ҳ�̧�ق̴���߰�] ����ނ��g�p���Ď��s���Ă�������
!MESSAGE 
!MESSAGE NMAKE /f "ShoppingServiceSec_cgi_DLL.mak".
!MESSAGE 
!MESSAGE NMAKE �̎��s���ɍ\�����w��ł��܂�
!MESSAGE ����� ײݏ��ϸۂ̐ݒ���`���܂��B��:
!MESSAGE 
!MESSAGE NMAKE /f "ShoppingServiceSec_cgi_DLL.mak" CFG="ShoppingServiceSec_cgi_DLL - Win32 Debug"
!MESSAGE 
!MESSAGE �I���\������� Ӱ��:
!MESSAGE 
!MESSAGE "ShoppingServiceSec_cgi_DLL - Win32 Release" ("Win32 (x86) Console Application" �p)
!MESSAGE "ShoppingServiceSec_cgi_DLL - Win32 Debug" ("Win32 (x86) Console Application" �p)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ShoppingServiceSec_cgi_DLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ShoppingServiceSec_cgi_DLL___Win32_Release"
# PROP BASE Intermediate_Dir "ShoppingServiceSec_cgi_DLL___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_DLL"
# PROP Intermediate_Dir "Release_DLL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "C:\OpenSOAP\include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "CONNECT_TYPE_CGI" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib OpenSOAPClient.lib OpenSOAPService.lib OpenSOAPSecurity.lib /nologo /subsystem:console /machine:I386 /out:"Release_DLL/ShoppingServiceSec.cgi.exe" /libpath:"C:\OpenSOAP\lib\DLL"

!ELSEIF  "$(CFG)" == "ShoppingServiceSec_cgi_DLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ShoppingServiceSec_cgi_DLL___Win32_Debug"
# PROP BASE Intermediate_Dir "ShoppingServiceSec_cgi_DLL___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_DLL"
# PROP Intermediate_Dir "Debug_DLL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\OpenSOAP\include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "CONNECT_TYPE_CGI" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib OpenSOAPClient.lib OpenSOAPService.lib OpenSOAPSecurity.lib /nologo /subsystem:console /debug /machine:I386 /out:"Debug_DLL/ShoppingServiceSec.cgi.exe" /pdbtype:sept /libpath:"C:\OpenSOAP\lib\DLL"

!ENDIF 

# Begin Target

# Name "ShoppingServiceSec_cgi_DLL - Win32 Release"
# Name "ShoppingServiceSec_cgi_DLL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\samples\ShoppingSec\ShSvCmn.c
# End Source File
# Begin Source File

SOURCE=..\..\samples\ShoppingSec\ShSvGetProductCount.c
# End Source File
# Begin Source File

SOURCE=..\..\samples\ShoppingSec\ShSvGetProductSpec.c
# End Source File
# Begin Source File

SOURCE=..\..\samples\ShoppingSec\ShSvGetStockQty.c
# End Source File
# Begin Source File

SOURCE=..\..\samples\ShoppingSec\ShSvMainSec.c
# End Source File
# Begin Source File

SOURCE=..\..\samples\ShoppingSec\ShSvPlaceOrderSec.c
# End Source File
# Begin Source File

SOURCE=..\..\samples\ShoppingSec\SvCmn.c
# End Source File
# Begin Source File

SOURCE=..\..\samples\ShoppingSec\SvSecCmn.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
