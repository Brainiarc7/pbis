/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: Logger.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#ifndef Logger_H
#define Logger_H

#include <pthread.h>
#include <string>
#include <stdarg.h>

namespace OpenSOAP {

class Logger {
	protected:
		//��å��ѥե饰
		pthread_mutex_t MutexFlag;
		//�� ���ϥե����ޥåȥ�����(generic or detail)
		std::string LogFormatType;
		//�� ���ϥ�٥�����
		int OutputLevel;
		//lock process(thread) id
		int LockID;

	public:
		Logger();
		virtual ~Logger();

		//LogFormatType menber access method.
		void SetLogFormatType(const std::string& ftype);
		void SetLogFormatType(const char * ftype);
		std::string& GetLogFormatType();
		//OutputLevel menber access method.
		void SetOutputLevel(int level);
		int GetOutputLevel();

		const char * MsgLevel2Str(int level);

	public:
		// �����֥������Ȥν�����᥽�å�
		virtual void Initialize();
		// ���������ץ󡢥������᥽�å�
		virtual void Open(){}
		virtual void Close(){}
		// ���񤭹����ѥ�å��᥽�å�
		virtual void Lock();
		virtual void UnLock();
		// ���������ϥ᥽�å�
		virtual void FFlush();
		// ���ɤ߽񤭥ݥ���Ȥ�Ĵ���᥽�å�
		virtual void SeekHead(){}
		virtual void SeekSet(long l){}
		virtual void SeekEnd(){}
		// �������������᥽�å�
		virtual int GetSize(){return 0;}
		// �����ϥ᥽�å�
		virtual int Write(std::string str);
		virtual int Write(const char * fmt,...);
		virtual int Write(const char * fmt,va_list args);
		virtual int Write(int level,std::string str);
		virtual int Write(int level,const char * fmt,va_list args);
		virtual int Write(int level,const char * fmt,...);
		virtual int Write(int level,time_t t,const char * hostname
					,const char * processname
					,pid_t pid,pthread_t tid
					,const char * fmt,va_list args);
		virtual int RawWrite(int level,const char * fmt,...);
		virtual int RawWrite(int level,const char * fmt,va_list args);
		virtual void Rotate(){};
};

}//end of namespace OpenSOAP

#endif /* Logger_H */
