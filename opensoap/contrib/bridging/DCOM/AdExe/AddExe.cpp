// AddExe.cpp : CAddExe �̃C���v�������e�[�V����
#include "stdafx.h"
#include "AdExe.h"
#include "AddExe.h"

/////////////////////////////////////////////////////////////////////////////
// CAddExe


STDMETHODIMP CAddExe::Add(double a, double b, double *result)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
	HRESULT ret = S_FALSE;

	if( result ) {
		*result = a + b;
		ret = S_OK;
	}

	return ret;
}
