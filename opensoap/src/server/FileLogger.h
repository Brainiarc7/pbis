#ifndef FileLogger_H
#define FileLogger_H

#include <stdio.h>
#include <string>
#include <stdarg.h>

#include "Logger.h"

namespace OpenSOAP {

class FileLogger :public Logger  {
	protected:
		std::string FileName;
		int    FileDescriptor;
		FILE * FilePointer;

	public:
		FileLogger();
		FileLogger(std::string filename){Initialize();FileName=filename;}
		FileLogger(FILE *){}
		~FileLogger();

		void Initialize();
		void SetFileName(const std::string& fn);
		void SetFilePointer(FILE * fp);
		std::string& GetFileName();
		FILE * GetFilePointer();

	public:
		void Open();
		void Close();
		void Lock();
		void UnLock();
		void UnLock(int id);
		void FFlush();
		void SeekHead();
		void SeekSet(long l);
		void SeekEnd();
		int GetSize();

		//ľ�ܻ��ꤷ��ʸ����񤭹�������
		int RawWrite(int level,const char * fmt,va_list args);

		void Rotate();
};

}//end of namespace OpenSOAP

#endif /* FileLogger_H */
