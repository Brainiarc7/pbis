// DivideDll.cpp : CDivideDll �̃C���v�������e�[�V����
#include "stdafx.h"
#include "DivDll.h"
#include "DivideDll.h"

/////////////////////////////////////////////////////////////////////////////
// CDivideDll


STDMETHODIMP CDivideDll::Divide(double a, double b, double *result)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������

	HRESULT ret = S_FALSE;

	if( result && b ) {
		*result = a / b;
		ret = S_OK;
	}

	return ret;
}
