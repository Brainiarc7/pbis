/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: Timeout.cpp,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#include <iostream>
#include <stdexcept>

#if defined(WIN32)
#include <process.h>
#include "StringUtil.h"
#else
#include <pthread.h>
#include <unistd.h>
#endif

#include "Timeout.h"
#include "ServerCommon.h"
#include "AppLogger.h"

using namespace OpenSOAP;
using namespace std;

#if defined(WIN32)
int Timeout::mtCount_ = 0;
#endif

//===========================================
// ���󥹥ȥ饯��
//-------------------------------------------
// ����: �����ॢ���Ȼ���(��) 
//===========================================
Timeout::Timeout(int timeout_second)
  : timeoutSecond_(timeout_second)
    , targetThread_(0)
{
  initMutex();
}

//===========================================
// ���󥹥ȥ饯��
//-------------------------------------------
// ����: �����ॢ���Ȼ���(��) 
// ����: �����ޡ��ƻ��оݥ���å�ID
//===========================================
Timeout::Timeout(int timeout_second, 
#if defined(WIN32)
				HANDLE
#else
				pthread_t
#endif
					thr_id)
  : timeoutSecond_(timeout_second)
    , targetThread_(thr_id)
{
  initMutex();
}

//===========================================
// �ǥ��ȥ饯��
//===========================================
Timeout::~Timeout()
{
  destroyMutex();
  //added 2003/02/03
#if !defined(WIN32)
  pthread_detach(targetThread_);
#endif
}

//===========================================
// mutex���������
//===========================================
void Timeout::initMutex()
{
#if defined(WIN32)
	if (mtCount_ > 10000) {
		mtCount_ = 0;
	}
	std::string mtId = "TIMEOUTMTX" + StringUtil::toString(mtCount_++);
	isRunning_mutex_ = CreateMutex(NULL, FALSE, mtId.c_str());
#else
  int status = pthread_mutex_init(&isRunning_mutex_, NULL);
  if (0 != status) {
    //throw OpenSOAPException();
    throw std::exception();
  }
#endif
}

//===========================================
// mutex�˴�����
//===========================================
void Timeout::destroyMutex()
{
#if defined(WIN32)
	CloseHandle(isRunning_mutex_);
#else
  int status = pthread_mutex_init(&isRunning_mutex_, NULL);
  if (0 != status) {
    //throw OpenSOAPException();
    throw std::exception();
  }
#endif
}

//===========================================
// �����ॢ�����оݥ���åɻ���
//-------------------------------------------
// ����: �����ޡ��ƻ��оݥ���å�ID
//===========================================
void Timeout::setTargetThread(
#if defined(WIN32)
							HANDLE
#else
							pthread_t
#endif
								thr_t)
{
  targetThread_ = thr_t;
}

//===========================================
// �����ॢ���Ȼ��ֻ���(��)
//-------------------------------------------
// ����: �����ॢ���Ȼ���(��) 
//===========================================
void Timeout::setTimeout(int timeout_second)
{
  timeoutSecond_ = timeout_second;
}


//===========================================
// �����ޡ�����
//-------------------------------------------
// ����: Timeout���󥹥��󥹤Υݥ���
//===========================================
ThrFuncReturnType
Timeout::runTimeout(ThrFuncArgType arg)
{
    static char METHOD_LABEL[] = "Timeout::runTimeout: ";

#ifdef DEBUG
    //debug
    AppLogger::Write(APLOG_DEBUG9,"%s%s",METHOD_LABEL
                    ,"Timeout::runTimeout() called");
#endif
    
    //���󥹥��󥹾������
    // �������ƥ��å��᥽�åɤΤ���,�����ˤ�ꥤ�󥹥��󥹤�����
    //   �����𤷤ƥ��󥹥��󥹥��Ф˥�����������
    Timeout* that = (Timeout*)arg;
    if (NULL == that) {
        AppLogger::Write(APLOG_ERROR,"%s%s",METHOD_LABEL
                        ,"invalid argument...");
    }

    //������ֵٻ�
#if defined(WIN32)
    Sleep(that->timeoutSecond_*1000);
#else
    sleep(that->timeoutSecond_);
#endif

    //-------------------------------
    //��������ʹߤϥ����ॢ���Ƚ���
    //-------------------------------
    //  �����ॢ�������˽�����λ�ξ��Ͼ嵭sleep()���
    //  finish()����ܥ���åɤ���ߤ����
    
    // lock mutex
    Thread::lockMutex(that->isRunning_mutex_);

    //�¹Ծ��֥����å�
    if (that->isRunning_) {
#ifdef DEBUG
        //debug
        AppLogger::Write(APLOG_DEBUG9,"%s%s",METHOD_LABEL
                        ,"### pthread cancel call!! ###");
#endif //DEBUG
        
        //timeout proc.

#if defined(WIN32)
	if (0 == TerminateThread(that->targetThread_, 0)) {
        AppLogger::Write(APLOG_ERROR,"%s%s",METHOD_LABEL
                        ,"thread cancel error...");
	}
	else {
#ifdef DEBUG
        AppLogger::Write(APLOG_DEBUG9,"%s%s",METHOD_LABEL
                        ,"Timeout:: thread canceled.");
#endif //DEBUG
	    that->targetThreadIsCanceled_ = true;
	}
#else //defined(WIN32)
        int status = pthread_cancel(that->targetThread_);
        if (0 != status) {
            AppLogger::Write(APLOG_ERROR,"%s%s",METHOD_LABEL
                            ,"pthread cancel error...");
        }
        else {
            that->targetThreadIsCanceled_ = true;
        }
        //added 2003/01/31
        //pthread_detach(that->targetThread_);

#endif //defined(WIN32)/else
        
        that->isRunning_ = false;
    }

#ifdef DEBUG
    // for debug
    else {
        AppLogger::Write(APLOG_DEBUG9,"%s%s",METHOD_LABEL
                ,"## Timeout::runTimeout : not running. may be finished ##");
    }
#endif
//fprintf(stderr,"[%s:%s:%d][%ld]\n",__FILE__,__func__,__LINE__,AppLogger::GetLockThread());

    //release mutex
    Thread::unlockMutex(that->isRunning_mutex_);
    
#ifdef DEBUG
    //debug
    AppLogger::Write(APLOG_DEBUG9,"%s%s",METHOD_LABEL
                    ,"Timeout::runTimeout() return");
#endif
    
    ReturnThread(NULL);
}

//===========================================
//�����ॢ���ȴƻ볫��
//-------------------------------------------
// �֤��͡� ���ơ�����
//          ��:     ����
//          ���ʳ�: ���顼
//===========================================
int 
Timeout::start()
{
    static char METHOD_LABEL[] = "Timeout::start: ";

#ifdef DEBUG
    //debug
    AppLogger::Write(APLOG_DEBUG9,"%s%s",METHOD_LABEL
                    ,"Timeout::start() called");
#endif

    //�����оݥ���å���������å�
    if (0 == targetThread_) {
        AppLogger::Write(APLOG_ERROR,"%s%s",METHOD_LABEL
                        ,"target thread not set");
        return -1;
    }
    
    // lock mutex
    Thread::lockMutex(isRunning_mutex_);

    // �ե饰����
    isRunning_ = true;
    targetThreadIsCanceled_ = false;
  
    //�����ޡ�����åɳ���
#if defined(WIN32)
    timerThr_id_ = (HANDLE)_beginthread(runTimeout, 0, this);
#else
    int status = pthread_create(&timerThr_id_, 
                                NULL,
                                runTimeout, // static method
                                this);
#endif

    // release mutex
    Thread::unlockMutex(isRunning_mutex_);

#ifdef DEBUG
    //debug
    AppLogger::Write(APLOG_DEBUG9,"%s%s",METHOD_LABEL
                    ,"Timeout::start() return");
#endif

    return 0;
}

//===========================================
//�����ॢ���ȴƻ뽪λ
//-------------------------------------------
// �֤��͡� ���ơ�����
//          ��:     ����
//          ���ʳ�: ���顼
//===========================================
int 
Timeout::finish()
{
    static char METHOD_LABEL[] = "Timeout::finish: ";

#ifdef DEBUG
    //debug
    AppLogger::Write(APLOG_DEBUG9,"%s%s",METHOD_LABEL
                    ,"called");
#endif

    // lock mutex
    Thread::lockMutex(isRunning_mutex_);

    // isRunning_ �Υ����å���ԤʤäƤ���ˤ��뤫???
    if (isRunning_) {
        // �����ॢ�������˽�����λ�ʤΤ�,
        // �����ޡ���������åɤ���ߤ���
#if defined(WIN32)
	if ( 0 == TerminateThread(timerThr_id_, 0)) {
            AppLogger::Write(APLOG_ERROR,"%s%s",METHOD_LABEL
                            ,"thread cancel error");
        }
#else
        int status = pthread_cancel(timerThr_id_);
        if (0 != status) {
            AppLogger::Write(APLOG_ERROR,"%s%s",METHOD_LABEL
                            ,"pthread cancel error");
        }
#ifdef DEBUG
        else {
            AppLogger::Write(APLOG_DEBUG9,"%s%s",METHOD_LABEL
                            ,"thread cancel OK!!");
        }
#endif
        //added 2003/01/31
        pthread_detach(timerThr_id_);
#endif
    
        // �ե饰���
        isRunning_ = false;
    }
#ifdef DEBUG
    else {
        AppLogger::Write(APLOG_DEBUG9,"%s%s",METHOD_LABEL
                        ,"not Running!!");
    }
#endif

    // release mutex
    Thread::unlockMutex(isRunning_mutex_);

#ifdef DEBUG
    //debug
    AppLogger::Write(APLOG_DEBUG9,"%s%s",METHOD_LABEL
                    ,"return");
#endif
  
  return 0;
}
 
// �������åȥ���åɤ������ॢ���Ȥǥ���󥻥뤵�줿���ݤ���
// 
// true:  ����󥻥뤵��Ƥ��롣
// false: ����󥻥뤵��Ƥ��ʤ���
// 
bool
Timeout::targetThreadIsCanceled()
{
  return targetThreadIsCanceled_;
}
//--- End of Timeout.cpp ---
