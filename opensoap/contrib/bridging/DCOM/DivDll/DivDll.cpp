// DivDll.cpp : DLL �G�N�X�|�[�g�̃C���v�������e�[�V����


// ����: Proxy/Stub ���
//  �ʁX�� proxy/stub DLL ���r���h���邽�߂ɂ́A�v���W�F�N�g�̃f�B���N�g���� 
//      nmake -f DivDllps.mak �����s���Ă��������B

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "DivDll.h"

#include "DivDll_i.c"
#include "DivideDll.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_DivideDll, CDivideDll)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL �G���g�� �|�C���g

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_DIVDLLLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// DLL �� OLE �ɂ���ăA�����[�h�\���ǂ����𒲂ׂ邽�߂Ɏg�p����܂�

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// �v�����ꂽ�^�̃I�u�W�F�N�g���쐬���邽�߂ɃN���X �t�@�N�g����Ԃ��܂�

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - �V�X�e�� ���W�X�g���փG���g����ǉ����܂�

STDAPI DllRegisterServer(void)
{
    // �I�u�W�F�N�g�A�^�C�v���C�u��������у^�C�v���C�u�������̑S�ẴC���^�[�t�F�C�X��o�^���܂�
	_Module.UpdateRegistryFromResourceD(IDR_DIVIDE, TRUE );
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - �V�X�e�� ���W�X�g������G���g�����폜���܂�

STDAPI DllUnregisterServer(void)
{
	_Module.UpdateRegistryFromResourceD(IDR_DIVIDE, FALSE );
    return _Module.UnregisterServer(TRUE);
}


