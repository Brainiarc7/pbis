/*-----------------------------------------------------------------------------
 * $RCSfile: dicClient.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */
// dicClient.h : DICCLIENT �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#if !defined(AFX_DICCLIENT_H__B833339E_18A2_45AD_8A5B_6D3C3484A269__INCLUDED_)
#define AFX_DICCLIENT_H__B833339E_18A2_45AD_8A5B_6D3C3484A269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CDicClientApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� dicClient.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CDicClientApp : public CWinApp
{
public:
	CDicClientApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDicClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	//{{AFX_MSG(CDicClientApp)
	afx_msg void OnAppAbout();
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DICCLIENT_H__B833339E_18A2_45AD_8A5B_6D3C3484A269__INCLUDED_)
