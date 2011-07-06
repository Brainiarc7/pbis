// DiskInfo.cpp : CDiskInfo �̃C���v�������e�[�V����
#include "stdafx.h"
#include "ServerInfo.h"
#include "DiskInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CDiskInfo


STDMETHODIMP CDiskInfo::GetFreeDiskSpace(const wchar_t *wszDrive, hyper *hypFreeBytes)
{
	// TODO: ���̈ʒu�ɃC���v�������g�p�̃R�[�h��ǉ����Ă�������

	USES_CONVERSION;

	DWORD dwSectorsPerCluster;
	DWORD dwBytesPerSector;
	DWORD dwBytesPerCluster;
	DWORD dwNumberOfFreeClusters;
	DWORD dwTotalNumberOfClusters;

	// Win95 OSR2���OGetDiskFreeSpaceEx()�𗘗p���邱�Ƃ��ł��Ȃ�����,�����ł�
	// GetDiskFreeSpace()���g�p����.
	GetDiskFreeSpace(W2T(wszDrive), &dwSectorsPerCluster,
		&dwBytesPerSector, &dwNumberOfFreeClusters,
		&dwTotalNumberOfClusters);

	// 1�N���X�^����̃o�C�g����DWORD�Ɋi�[����
	dwBytesPerCluster = dwSectorsPerCluster * dwBytesPerSector;

	// �������C�f�B�X�N��̃o�C�g���́C���Ӑ[����������K�v������D
	*hypFreeBytes = UInt32x32To64(dwNumberOfFreeClusters,
		dwBytesPerCluster);

	return S_OK;
}
