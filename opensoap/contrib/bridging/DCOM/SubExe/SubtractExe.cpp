// SubtractExe.cpp : CSubtractExe �̃C���v�������e�[�V����
#include "stdafx.h"
#include "SubExe.h"
#include "SubtractExe.h"

/////////////////////////////////////////////////////////////////////////////
// CSubtractExe


STDMETHODIMP CSubtractExe::Subtract(double a, double b, double *result)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������

	HRESULT ret = S_FALSE;

	if(result) {
		*result = a - b;
		ret = S_OK;
	}

	return ret;
}
