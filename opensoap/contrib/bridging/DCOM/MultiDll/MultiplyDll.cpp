// MultiplyDll.cpp : CMultiplyDll �̃C���v�������e�[�V����
#include "stdafx.h"
#include "MultiDll.h"
#include "MultiplyDll.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiplyDll


STDMETHODIMP CMultiplyDll::Multiply(double a, double b, double *result)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
	HRESULT ret = S_FALSE;

	if( result ) {
		*result = a * b;
		ret = S_OK;
	}

	return ret;
}
