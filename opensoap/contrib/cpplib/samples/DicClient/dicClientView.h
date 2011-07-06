/*-----------------------------------------------------------------------------
 * $RCSfile: dicClientView.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */
// dicClientView.h : CDicClientView �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DICCLIENTVIEW_H__EA8A3F3B_6EBC_48AD_A02A_851C3244EC66__INCLUDED_)
#define AFX_DICCLIENTVIEW_H__EA8A3F3B_6EBC_48AD_A02A_851C3244EC66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpenSOAPInitializer.h"
#include "dicMethod.h"
#include <vector>

class CDicClientView : public CHtmlView
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CDicClientView();
	DECLARE_DYNCREATE(CDicClientView)

// �A�g���r���[�g
public:
	CDicClientDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDicClientView)
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // �\�z��̍ŏ��̂P�x�����Ăяo����܂��B
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CDicClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CDicClientView)
	afx_msg void OnSearch();
	afx_msg void OnDblclkItemlist();
	afx_msg void OnSelchangeItemlist();
	afx_msg void OnSelchangeDiclist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ChangeStatusMessage(const string& mes);
	CWnd* GetDlgItem(int nID);
	void GetDic();
	void SearchItem(const string& keyword);

//	std::vector<std::string> gdiList;
	SearchDicItem sdi;
	GetDicList gdl;

	Initializer initializer;
};

#ifndef _DEBUG  // dicClientView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CDicClientDoc* CDicClientView::GetDocument()
   { return (CDicClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DICCLIENTVIEW_H__EA8A3F3B_6EBC_48AD_A02A_851C3244EC66__INCLUDED_)
