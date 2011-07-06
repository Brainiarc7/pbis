OpenSOAP DCOM �u���b�W���O�T�[�r�X�g�p����


1�DDCOM �R���|�[�l���g�̓o�^
   DCOM �R���|�[�l���g�̓o�^�̓N���C�A���g�}�V���ƃT�[�o�[�}�V�������ɕK�v�ł��D

1.1 �K�v�ȃt�@�C��
1.1.1 DLL�T�[�o�[�̏ꍇ�F
      (1)***.dll�F
		  	�N���X����񋟂���t�@�C��
      (2)***ps.dll�F
			�v���L�V�[�X�^�u�C���^�[�t�F�[�X����񋟂���t�@�C��
1.1.2 EXE�T�[�o�[�̏ꍇ�F
      (1)***.exe�F
			�N���X����񋟂���t�@�C��
      (2)***ps.dll�F
			�v���L�V�[�X�^�u�C���^�[�t�F�[�X����񋟂���t�@�C��

1.2 �N���X�ƃv���L�V�[�X�^�u�C���^�[�t�F�[�X�̓o�^
1.2.1 DLL�T�[�o�[�̏ꍇ
      (1) �N���X�̓o�^�F
          	regsvr32 ***.dll
      (2) �v���L�V�[�X�^�u�C���^�[�t�F�[�X�̓o�^�F
          	regsvr32 ***ps.dll
1.2.2 EXE�T�[�o�[�̏ꍇ�F
      (1) �N���X�̓o�^�F
			***.exe /regserver
      (2) �v���L�V�[�X�^�u�C���^�[�t�F�[�X�̓o�^�F
			regsvr32 ***ps.dll

1.3	�o�^�̊m�F
    OLE/COM Object Viewer(OleView.exe)���N�����C[View]���j���[��[Expert Mode]���I������Ă��邱�Ƃ��m�F���������D���ɁC[All Objects]�̃c���[���I�[�v�����C[*** Class]���o�^���ꂽ���Ƃ��m�F�ł��܂��D

2�DOpenSOAP DCOM �u���b�W���O�T�[�r�X�̍쐬
2.1 �K�v�ȃt�@�C��
	(1) ***.tlb
		DCOM�R���|�[�l���g�I�u�W�F�N�g�̃^�C�v���C�u�����t�@�C��

2.2 �T�[�r�X�̍쐬
	OpenSOAP DCOM�u���b�W���O�T�[�r�X��OpenSOAP�T�[�r�X�̈��ނł���CDCOM�̃R���|�[�l���g�𗘗p���鑤�ł��邽�߁COpenSOAP DCOM�u���b�W���O�T�[�r�X��DCOM�̃N���C�A���g���ɂȂ�܂��D
	�쐬����Ƃ��C"***.tlb"��import���C�ȉ��̊֐����g�p���ă����[�g�}�V�����DCOM�I�u�W�F�N�g���Ăяo���C���p���܂��D
    CoCreateInstanceEx()

2.3 �T���v��(C����): 
	�ڍׂ�DCOM�u���b�W���O�T���v�����Q�l�ɁD

	�Ⴆ�΁C�ȈՉ��Z�̈����Z�͈ȉ��̂悤�ɂȂ�܂��D

#define _WIN32_DCOM

#import "SubExe.tlb"

#include <iostream>

int
Subtract(double a,
         double b,
         double *r) {
    int ret = OPENSOAP_PARAMETER_BADVALUE;

	HRESULT hr = CoInitialize(NULL);

	if (FAILED(hr)) {
		std::cerr << "COM Initialize failed" << std::endl;
		ret = OPENSOAP_MEM_ERROR;
		return ret;
	}

	try{
		SUBEXELib::ISubtractExePtr subService;
		COSERVERINFO serverInfo;
		MULTI_QI multiQi;

		serverInfo.dwReserved1 = NULL;
		serverInfo.pwszName = L"MIHARU";/* name of remote DCOM server machine */
		serverInfo.pAuthInfo = NULL;
		serverInfo.dwReserved2 = NULL;

		multiQi.pIID = &__uuidof(SUBEXELib::ISubtractExe);
		multiQi.pItf = NULL;
		multiQi.hr = S_OK;

		hr = CoCreateInstanceEx(__uuidof(SUBEXELib::SubtractExe),
								NULL,
								CLSCTX_REMOTE_SERVER,
								&serverInfo,
								1,
								&multiQi);
		if(FAILED(hr)) {
			_com_issue_error(hr);
		}

		SUBEXELib::ISubtractExe* pInt =
			 static_cast<SUBEXELib::ISubtractExe*>(multiQi.pItf);
		subService.Attach(pInt);

		*r = subService->Subtract(a, b);
	}

	catch (const _com_error & err) {
		hr = err.Error();
		cerr
			<< err.ErrorMessage()
			<< "0x"
			<<	hex
			<<	hr
			<<	endl;
	}

	CoUninitialize();

	ret = OPENSOAP_NO_ERROR;
    return ret;
}

3. DLL�T�[�o�[�����s�����邽�߂̐ݒ�
3.1 �㗝�v���Z�X
	�V�X�e���ŃT�|�[�g����Ă���㗝�v���Z�XDllHost.exe���g���CDLL�T�[�o�[�Ƀ����[�g�A�N�Z�X�ł���悤�ɂ��܂��D
3.2 �㗝�v���Z�X�̐ݒ�
    OLE/COM Object Viewer(OleView.exe)���N�����C[View]���j���[��[Expert Mode]���I������Ă��邱�Ƃ��m�F���������D���ɁC[All Objects]�̃c���[���I�[�v�����C��������[*** Class]��T���܂��D
	�c���[�r���[�̒��ŃN���X��I�����C�E���̃E�B���h�E�g��[Implementation]�����[Improc Server]��I�����܂��D
	[Use Surrogate Process]�{�b�N�X���N���b�N���܂��D�������C[Path to Custom Surrogate]�{�b�N�X�̒����ύX����Ă���Ƃ����|�����o����Ȃ��ƁCObject Viewer��DllSurrogate�l��ǉ����܂���D���̂��߁C[Path to Custom Surrogate]�{�b�N�X�̒��ɃX�y�[�X������͂�����C������폜���܂��D��������΁CDllHost.exe�㗝�v���Z�X�ɁC�T�[�o�[���֘A�����܂��D�ʂ̃I�u�W�F�N�g�̃G���g�����N���b�N����΁C���W�X�g�����X�V����܂��D

4�DEXE�T�[�o�[�����s�����邽�߂̐ݒ�
	���ʂȐݒ�͗v��܂���D

5�DDCOM�̓���m�F
5.1 DLL�T�[�o�[�̏ꍇ�F
	DCOM��DLL�T�[�o�[�ɑ�������}�V���̃^�X�N�}�l�[�W�����J���܂��DOpenSOAP DCOM�u���b�W���O�T�[�r�X����DCOM�T�[�o�[����DCOM�I�u�W�F�N�g���Ăяo�����C�^�X�N�}�l�[�W����DllHost.exe�̃v���Z�X���N�����ꂽ���Ƃ��m�F�ł��܂��D

5.2 EXE�T�[�o�[�̏ꍇ�F
	DCOM��EXE�T�[�o�[�ɑ�������}�V���̃^�X�N�}�l�[�W�����J���܂��DOpenSOAP DCOM�u���b�W���O�T�[�r�X����DCOM�T�[�o�[����DCOM�I�u�W�F�N�g���Ăяo�����C�^�X�N�}�l�[�W����EXE�T�[�o�[�ɑ�������***.exe�̃v���Z�X���N�����ꂽ���Ƃ��m�F�ł��܂��D
