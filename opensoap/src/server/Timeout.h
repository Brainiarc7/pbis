/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: Timeout.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#ifndef Timeout_H
#define Timeout_H

#if defined(WIN32)
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "ThreadDef.h"

namespace OpenSOAP {

  class Timeout {
  public:
    Timeout(int timeout_second);
#if defined(WIN32)
	Timeout(int timeout_second, HANDLE thr_id);
#else
    Timeout(int timeout_second, pthread_t thr_id);
#endif
    ~Timeout();

  public:
#if defined(WIN32)
	void setTargetThread(HANDLE thr_t);
#else
    void setTargetThread(pthread_t thr_t);
#endif
    void setTimeout(int timeout_second);

    //�^�C�}�[�Ď��J�n(�Ώۏ����J�n�O �ďo)
    int start();

    //�^�C�}�[�Ď��I��(�Ώۏ����I���� �ďo)
    int finish();

    // �^�[�Q�b�g�X���b�h���L�����Z������Ă��邩�H
    bool targetThreadIsCanceled();
    
    //private:
  protected:
    bool isRunning_;    
    bool targetThreadIsCanceled_;
    int timeoutSecond_;

#if defined(WIN32)
      static int mtCount_;
#endif

      ThrFuncHandle targetThread_;
      ThrFuncHandle timerThr_id_;
      ThrMutexHandle isRunning_mutex_;

    void initMutex();
    void destroyMutex();

      static
      ThrFuncReturnType runTimeout(ThrFuncArgType arg);
  };
}

#endif /* Timeout_H */
