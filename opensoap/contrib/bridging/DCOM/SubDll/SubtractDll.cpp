// SubtractDll.cpp : CSubtractDll �̃C���v�������e�[�V����
#include "stdafx.h"
#include "SubDll.h"
#include "SubtractDll.h"

/////////////////////////////////////////////////////////////////////////////
// CSubtractDll


STDMETHODIMP CSubtractDll::Subtract(double a, double b, double *result)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
	HRESULT ret = S_FALSE;

	if(result) {
		*result = a - b;
		ret = S_OK;
	}

	return ret;
}
