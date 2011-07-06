#ifndef ProcessInfo_H
#define ProcessInfo_H

#include <pthread.h>
#include <map>
#include <string>
#include "ThreadInfo.h"

#define _StaticClass

#ifdef _StaticClass
	#define STATIC_OPTION static
#else
	#define STATIC_OPTION
#endif

#define PSTAT_NORMAL	0	// normal
#define PSTAT_INIT		1	// initialize
#define PSTAT_WAIT		2	// wait
#define PSTAT_WAITTERM	3	// wait termination
#define PSTAT_HUP		4	// wait termination
#define PSTAT_USR1		5	// wait termination
#define PSTAT_USR2		6	// wait termination

namespace OpenSOAP {

class ProcessInfo {
	private:
		STATIC_OPTION std::string ProcessName;
		STATIC_OPTION std::string HostName;
		STATIC_OPTION pthread_mutex_t MutexFlag;
		STATIC_OPTION pthread_mutex_t UpdateLockFlag;
		STATIC_OPTION int LockCount;
		STATIC_OPTION std::map<pthread_t,ThreadInfo *> ThreadInfoMap;
		STATIC_OPTION int ProcessStatus;
		STATIC_OPTION int ThreadCount;
		

	private:
		STATIC_OPTION ThreadInfo * AddThreadInfo(pthread_t tid);

	public:
		ProcessInfo();
		virtual ~ProcessInfo();

		//�X���b�h���X�g�ɃX���b�h����ǉ�����B
		STATIC_OPTION ThreadInfo * AddThreadInfo();
		//�X���b�h���X�g����X���b�h�����擾����B
		STATIC_OPTION ThreadInfo * GetThreadInfo();	
		STATIC_OPTION ThreadInfo * GetThreadInfo(pthread_t tid);
		//�X���b�h���X�g����X���b�h�����폜����B
		STATIC_OPTION void DelThreadInfo();	
		STATIC_OPTION void DelThreadInfo(pthread_t tid);
		//���݂̃X���b�h���X�g��\������B
		STATIC_OPTION void PrintProcessInfo();	
		STATIC_OPTION void PrintThreadInfo();	
		//���݂̃X���b�h���X�g���`�F�b�N����B
		STATIC_OPTION void CheckThreadInfo();	//pthread_check&delete item
		STATIC_OPTION void CheckThreadInfo(pthread_t tid);
		//�v���Z�X���̐ݒ�/�擾
		STATIC_OPTION void SetProcessName(char * str);
		STATIC_OPTION std::string GetProcessName();
		//�z�X�g����ݒ�/�擾
		STATIC_OPTION void SetHostName(const char * str);
		STATIC_OPTION std::string GetHostName();
		//�X���b�h�����擾
		STATIC_OPTION int GetThreadCount();
		//�X���b�h��Ԃ̐ݒ�/�擾 
		// PSTAT_NORMAL/PSTAT_INIT/PSTAT_WAIT/PSTAT_WAITERM
		STATIC_OPTION void SetProcessStatus(int pstat);
		STATIC_OPTION int GetProcessStatus();
		//�X���b�h���X�g�̃f�[�^�X�V�p���b�N�j
		STATIC_OPTION void Lock();	
		STATIC_OPTION void UnLock();	
		//�Q�Ɨp���b�N�i��������(�ǉ�/�폜)��s�ɂ���j
		STATIC_OPTION void UpdateLock();	
		STATIC_OPTION void UpdateUnLock();	

}; //class ProcessInfo

} //namespace OpenSOAP

#endif //ProcessInfo_H

