// MultiplyExe.cpp : CMultiplyExe �̃C���v�������e�[�V����
#include "stdafx.h"
#include "MultiExe.h"
#include "MultiplyExe.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiplyExe


STDMETHODIMP CMultiplyExe::Multiply(double a, double b, double *result)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������
	HRESULT ret = S_FALSE;

	if( result ) {
		*result = a * b;
		ret = S_OK;
	}

	return S_OK;
}
