/*-----------------------------------------------------------------------------
 * $RCSfile: dicClientDoc.cpp,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */
// dicClientDoc.cpp : CDicClientDoc �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "dicClient.h"

#include "dicClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDicClientDoc

IMPLEMENT_DYNCREATE(CDicClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CDicClientDoc, CDocument)
	//{{AFX_MSG_MAP(CDicClientDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDicClientDoc �N���X�̍\�z/����

CDicClientDoc::CDicClientDoc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CDicClientDoc::~CDicClientDoc()
{
}

BOOL CDicClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDicClientDoc �V���A���C�[�[�V����

void CDicClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDicClientDoc �N���X�̐f�f

#ifdef _DEBUG
void CDicClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDicClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDicClientDoc �R�}���h
