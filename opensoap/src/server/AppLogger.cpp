#if HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <stdarg.h>		//vsnprintf
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "AppLogger.h"

#include "ProcessInfo.h"
#include "Exception.h"
#include "SrvErrorCode.h"
#include "StringUtil.h"
#include "SrvConf.h"
#include "ServerCommon.h"

#define LOG_TYPE_UNKNOWN	-1
#define LOG_TYPE_STDOUT		0
#define LOG_TYPE_STDERR		1
#define LOG_TYPE_FILE		2
#define LOG_TYPE_SYSLOG		3
#define LOG_TYPE_NOLOG		4

typedef struct _log_type_lists {
	int code;
	char * name;
} LOG_TYPE_LISTS;

//log type & string mapping
static LOG_TYPE_LISTS LogTypeLists[]={
	{LOG_TYPE_STDOUT,"stdout"},
	{LOG_TYPE_STDERR,"stderr"},
	{LOG_TYPE_FILE,"file"},
	{LOG_TYPE_SYSLOG,"syslog"},
	{LOG_TYPE_NOLOG,"none"},
	{LOG_TYPE_UNKNOWN,NULL}
};

using namespace std;
using namespace OpenSOAP;

static const std::string CLASS_SIG = "AppLogger::";

// common
static const char QUERY_OPT[]				= "=?";
static const char QUERY_LOG_SIGNATURE[]		= "/server_conf/Logging/";
static const char QUERY_LOG_LEVEL[] 		= "LogLevel";
static const char QUERY_LOG_FORMAT[] 		= "LogFormat";
static const char QUERY_LOG_TYPE[] 			= "LogType";
// for file
static const char QUERY_FILELOG_FILENAME[] 	= "FileName";
static const char QUERY_FILELOG_FILESIZE[]	= "FileSize";
static const char QUERY_FILELOG_BASE[]		= "Application";
// for syslog
static const char QUERY_SYSLOG_OPTION[]		= "Option";
static const char QUERY_SYSLOG_FACILITY[]	= "Facility";
static const char QUERY_SYSLOG_LEVEL[]		= "DefaultLevel";
static const char QUERY_SYSLOG_BASE[]		= "System";

static const char *LogBaseLists[2]			={"System","Application"};

static std::string genericemptyfmt		=",";
static std::string detailemptyfmt		=",,,,";

//Logger CLASS member
Logger * AppLogger::AppLogPtr[2]={NULL,NULL};	//Logger class pointer
int AppLogger::AppLogNum=2;			//Number of log files
string AppLogger::AppLogBase[2];	//Log base name in server.conf
pthread_mutex_t AppLogger::AppLogLock=PTHREAD_MUTEX_INITIALIZER;
struct tm 	AppLogger::LogDate;
bool		AppLogger::AppLogUpdating=false;
bool 		AppLogger::AppLogInitNG=true;
bool 		AppLogger::AppLogFirstInit=true;
apploglockid_t	AppLogger::AppLogLockThread=0;

/*============================================================================
Logger CLASS 
=============================================================================*/
/*
�ؿ������󥹥ȥ饯��
	������ȥǥե���ȥ����֥�������(stderr)�κ���
������
	log1=�����ƥ���ѤΥ١����ǥ��쥯�ȥ��server.conf)
		default:System
	log2=���ץꥱ���������ѤΥ١����ǥ��쥯�ȥ��server.conf)
		default:Application
��ꡧ�ʤ�
	����������롣
�㳰���ʤ�
���͡�
	�����Х��ѿ�������Τ����������롣
*/
AppLogger::AppLogger() {
	AppLogger(NULL,NULL);
}

AppLogger::AppLogger(const char * log1,const char * log2) {
	if (!AppLogFirstInit) {
		return;
	}
	AppLogBase[0]=(log1)?log1:LogBaseLists[0];
	AppLogBase[1]=(log2)?log2:LogBaseLists[1];
	AppLogUpdating=false;
	AppLogInitNG=true;
	AppLogFirstInit=true;
	pthread_mutex_init(&AppLogLock,NULL);	//��å����֥������Ȥν����
	AppLogLockThread=0;

	//initialize empty message format
	MsgInfo msg;
	string msgfmt=msg.toString(APLOG_DEBUG4);
	genericemptyfmt+=msgfmt;
	genericemptyfmt+=",";
	detailemptyfmt+=msgfmt;
	detailemptyfmt+=",";

	// create default logger object
	AppLogPtr[0]=new Logger();		//���Υ��֥������Ȥϥ��顼���֤��ʤ�
	if (AppLogPtr[0]) {
		AppLogPtr[0]->SetLogFormatType("detail");
		AppLogPtr[0]->SetOutputLevel(6);
	}
}

/*
�ؿ����ǥ��ȥ饯��
	�����֥��ȤΥ������ڤӡ�����
��ꡧ�ʤ�
	�����������
�㳰���ʤ�
���͡�
*/
AppLogger::~AppLogger(){
	int i;
	for (i=0;i<AppLogNum;i++){
		if (AppLogPtr[i]!=NULL){
			try{
				AppLogPtr[i]->Close();		//�������֥������ȤΥ�����
			}
			catch (...) {
				Logger errlog;
				errlog.Write("Logger close error");
			}
			delete AppLogPtr[i];			//�������֥������Ȥκ��
		}
		AppLogPtr[i]=NULL;
	}
	AppLogUpdating=false;
	AppLogInitNG=true;
	AppLogFirstInit=true;
	pthread_mutex_destroy(&AppLogLock);			//��å����֥������Ȥβ���
}

/*
�ؿ����������֥������Ⱥ�����������
������
	initmode
		LOG_INIT(0)
		LOG_UPDATE(1)
��ꡧ�ʤ�
�㳰���ʤ�
���͡�
*/
void AppLogger::Initialize() {
	int i;
	int type=LOG_TYPE_UNKNOWN;
	const char * logbase=NULL;
	time_t t=time(NULL);
	struct tm *tm=localtime(&t);
	Logger * logger=NULL;
	Logger * loggerbackup=NULL;
	bool exceptflg=false;
	bool initflg=false;
	int timeout=1000000;
	apploglockid_t CurrentTID=GetCurrentThreadID();
	static apploglockid_t UpdateTID=0;

	if (AppLogUpdating || !AppLogInitNG || isMyLock()) {
		if (UpdateTID==CurrentTID) return;
		//���åץǡ�����ϡ����⤻�������
		//��ť�å����ⲿ�⤻�������
		while (AppLogFirstInit && (timeout >0)) {
			usleep(1000);
			timeout-=1000;
		}
		return;
	}

	Lock();
	if (AppLogUpdating || !AppLogInitNG) {
		while (AppLogFirstInit && (timeout >0)) {
			usleep(1000);
			timeout-=1000;
		}
		return;
	}
	AppLogUpdating=true;	//Update��ȴ��������false�ˤ��뤳�Ȥ�˺��ʤ����ȡ�
	UpdateTID=CurrentTID;
	UnLock();

	LogDate.tm_mday=tm->tm_mday;
	LogDate.tm_mon=tm->tm_mon;
	LogDate.tm_year=tm->tm_year;

	for (i=0;i<AppLogNum;i++){
		logbase=AppLogBase[i].c_str();
		try{
			// for application configuration load
			GetConfLogType(logbase,&type);
			logger=CreateLog(logbase,type);
			initflg=true;
		}
		catch(...){
			// for default configurration load
			try{
				GetConfLogType(LogBaseLists[i],&type);
				logger=CreateLog(LogBaseLists[i],type);
				AppLogBase[i]=LogBaseLists[i];
				initflg=true;
			}
			catch(...){
				Write(LOG_WARNING
					,"Logger create error . log[%d]base[%s]"
					,i,LogBaseLists[i]);
				exceptflg=true;		//�����ԲĤξ���㳰�Ȥ��롣
			}
		}
		if (initflg) {
			loggerbackup=AppLogPtr[i];
			try{
				Lock();			//���������ѹ��ɻߤ˥�å�����
				AppLogPtr[i]=logger;
				UnLock();		//���������ѹ��ɻߤ˥�å�����
				if (loggerbackup) {
					try{
						loggerbackup->Close();
					}
					catch(Exception e) {
						Write(LOG_ERR,"log close error!");
						Write(e);
					}
					catch(...){
						Write(LOG_ERR,"log close error!");
					}
					delete loggerbackup;
				}
			}
			catch(...){
				//�����ԲĤξ���㳰�Ȥ��롣
				exceptflg=true;
			}
		}
		else {
			Write(LOG_ERR,"Log create error!(log%d)",i);
		}
		type=LOG_TYPE_UNKNOWN;
		initflg=false;
		logger=NULL;
	}
	AppLogInitNG=exceptflg;
	AppLogUpdating=false;
	UpdateTID=0;
	if (AppLogFirstInit) {
		AppLogFirstInit=false;
		if (AppLogInitNG) {
			Write(APLOG_DEBUG,"Logger initialize error!");
			Exception e(-1,OPENSOAPSERVER_RUNTIME_ERROR
						,APLOG_ERROR,__FILE__,__LINE__);
			e.SetErrText("Logger initialize error!");
			throw(e);
		}
		Write(APLOG_DEBUG5,"Logger initialize OK!");
	}
}
void AppLogger::Update() {
	AppLogInitNG=true;
	Initialize() ;
}
void AppLogger::Update(const char * log1,const char * log2) {
	AppLogBase[0]=(log1)?log1:LogBaseLists[0];
	AppLogBase[1]=(log2)?log2:LogBaseLists[1];
	Update() ;
}

/*
�ؿ�����å��Ѵؿ�
	��å���ˡ
		Ʊ�쥹��åɤ���Υ�å��ξ��
			�㳰ȯ��
		��å��ʤ��ޤ��ϡ��̥���åɤ���Υ�å��ξ��
			��å��Ԥ�(��å��ȥ�å�����åɤ�����)
*/
void AppLogger::Lock(){
	char buff[16];
	struct stat st;
	apploglockid_t	pid=GetCurrentThreadID();
	apploglockid_t  tid=0;
        int timeout=1000000;

	if (AppLogLockThread==pid) {
		throw Exception(-1,OPENSOAPSERVER_THREAD_LOCK_ERROR
						,APLOG_ERROR,__FILE__,__LINE__);
	}
	
	//���ߥ�å����Ƥ��륹��åɤǤʤ����
	timeout=1000000;
	while (pthread_mutex_trylock(&AppLogLock) && (timeout>0)){
		tid=AppLogLockThread;
		//check locking thread
		if (tid!=0 && ProcessInfo::GetThreadInfo((pthread_t)tid)==NULL){
			//��å����Ƥ���Ϥ��Υ���åɤ��ʤ����˥����å����롣
			UnLock(tid);
		}
		else {
			usleep(10);
			timeout-=10;
		}
	}
	AppLogLockThread=(apploglockid_t)pid;		//��å������������������ꤹ�롣
}
/*
�ؿ�����ʬ����å����Ƥ��뤫Ĵ�٤�ؿ�
��ꡧ
	ture	=��ʬ����å����Ƥ������
	false	=��ʬ����å����Ƥ��ʤ��ʥ�å��ʤ����ޤ���¾�ͤ���å����Ƥ���)
�㳰���ʤ�
*/
bool AppLogger::isMyLock(){
	return (AppLogLockThread==GetCurrentThreadID())? true : false ;
}
/*
�ؿ��������å��Ѵؿ�
	Ʊ�쥹��åɤ���Τߥ����å���ǽ
*/
void AppLogger::UnLock(){
	UnLock(GetCurrentThreadID());
}
/*
�ؿ��������å��Ѵؿ�
	����å�ID����ꤹ�뤳�ȤǶ���Ū�˥����å���ǽ
������
	GetLockThread()���֤��ͤ���ꤹ�롣
*/
void AppLogger::UnLock(apploglockid_t tid){
	if (AppLogLockThread==tid) {
		AppLogLockThread=0;
		pthread_mutex_unlock(&AppLogLock);
	}
}
/*
�ؿ��������å�����å�ID�����ؿ�
	����Ū�˥����å����뤿��ˡ�����åɤ�ID�����
*/
apploglockid_t AppLogger::GetLockThread(){
	return AppLogLockThread;
}

Logger * AppLogger::CreateLog(const char * base,int type){
	Logger * log=NULL;
	switch (type){
		case LOG_TYPE_SYSLOG :
			log=(Logger *)CreateSysLogger(base);
			break;
		case LOG_TYPE_FILE :
			log=(Logger *)CreateFileLogger(base);
			break;
		case LOG_TYPE_STDOUT :
			log=CreateLogger(base);
			break;
		case LOG_TYPE_STDERR :
			log=CreateLogger(base);
			break;
		case LOG_TYPE_NOLOG :
			log=NULL;
			break;
		case LOG_TYPE_UNKNOWN:
		default :
			Write(ERR_WARN
				,"Logger create faild (unkown logtype)");
			throw Exception(-1,OPENSOAPSERVER_RUNTIME_ERROR
							,APLOG_ERROR,__FILE__,__LINE__);
			break;
	}
	return log;
}

SysLogger * AppLogger::CreateSysLogger(const char * base){
	SysLogger * log=NULL;
	string str;
	int i;

	try {
		log=new SysLogger();
	}
	catch(Exception except) {
		Write(APLOG_ERROR,"syslog object create error!");
		except.AddFuncCallStack();
		throw (except);
	}
	try {
		if (GetConfAttrIntWithBase(base,QUERY_SYSLOG_OPTION,&i)){
			log->SetSyslogOption(i);
		}
	 	else {
			Write(APLOG_DEBUG5,"No entry for %s in server.conf"
					,"syslog option");
		}	
		if (GetConfAttrIntWithBase(base,QUERY_SYSLOG_FACILITY,&i)){
			log->SetSyslogFacility(i);
		}
	 	else {
			Write(APLOG_DEBUG5,"No entry for %s in server.conf"
					,"syslog facility");
		}	
		if (GetConfAttrIntWithBase(base,QUERY_SYSLOG_LEVEL,&i)){
			log->SetSyslogLevel(i);
		}
	 	else {
			Write(APLOG_DEBUG5,"No entry for %s in server.conf"
					,"syslog default level");
		}	
		if (GetConfAttrIntWithBase(base,QUERY_LOG_LEVEL,&i)){
			log->SetOutputLevel(i);
		}
	 	else {
			Write(APLOG_DEBUG5,"No entry for %s in server.conf"
					,"syslog output level");
		}	
		if (GetConfLogFormatType(base,str)){
			log->SetLogFormatType(str);
		}
	 	else {
			Write(APLOG_DEBUG5,"No entry for %s in server.conf"
					,"syslog format type");
		}	
	}
	catch (...) {	
		Write(APLOG_DEBUG5,"unable to get configuration data from server.conf");
	}
	return log;
}

FileLogger * AppLogger::CreateFileLogger(const char * base){
	FileLogger * log=NULL;
	string str;
	int i;

	try {
		log=new FileLogger();
	}
	catch(Exception except) {
		Write(APLOG_ERROR,"filelog object create error!");
		except.AddFuncCallStack();
		throw (except);
	}
	try {
		if (GetConfAttrStringWithBase(base,QUERY_FILELOG_FILENAME,str)){
			log->SetFileName(str);
		}
	 	else {
			Write(APLOG_DEBUG5,"No entry for %s in server.conf"
					,"file path&name");
		}
		if (GetConfAttrIntWithBase(base,QUERY_LOG_LEVEL,&i)){
			log->SetOutputLevel(i);
		}
	 	else {
			Write(APLOG_DEBUG5,"No entry for %s in server.conf"
					,"file output level");
		}
		if (GetConfLogFormatType(base,str)){
			log->SetLogFormatType(str);
		}
	 	else {
			Write(APLOG_DEBUG5,"No entry for %s in server.conf"
					,"file format type");
		}
	}
	catch (...) {	
		Write(APLOG_DEBUG5,"unable to get configuration data from server.conf");
	}
	return log;
}
Logger * AppLogger::CreateLogger(const char * base){
	Logger * log=NULL;
	string str;
	int i;
	
	log=new Logger();
	try {
		if (GetConfAttrIntWithBase(base,QUERY_LOG_LEVEL,&i)){
			log->SetOutputLevel(i);
		}
	 	else {
			Write(APLOG_DEBUG5,"No entry for %s in server.conf"
					,"stderr output level");
		}
		if (GetConfLogFormatType(base,str)){
			log->SetLogFormatType(str);
		}
	 	else {
			Write(APLOG_DEBUG5,"No entry for %s in server.conf"
					,"stderr format type");
		}
	}
	catch (...) {	
		Write(APLOG_DEBUG5,"unable to get configuration data from server.conf");
	}
	return log;
}

void AppLogger::Write(Exception e) {
	std::string OutputMsg="";
	//Message Infomation
	std::string MsgID="";
	//Thread Infomation
	ThreadInfo	 * ti=NULL;
	std::string ftype;
	int i=0;
	bool exceptflg=false;
	bool writeflg=false;
	int timeout=1000000;

	struct tm * t;
	//Write format
	static const char genericfmt[]="%d,%s,%s";
	static const char detailfmt[]="%d,%08x,%d,%s,%s,%s";

	t=localtime(&(e.tm));

	if (isMyLock()){
		Logger errlog;
		errlog.Write(APLOG_ERROR,"dead lock error!");
		return;
	}
	if ((AppLogInitNG && !AppLogUpdating)||AppLogFirstInit) {
		Initialize();
	}
	else {
		while (AppLogFirstInit && (timeout >0)) {
			usleep(1000);
			timeout-=1000;
		}
	}
	try{
		//Get Thread Infomation
		ti=ProcessInfo::GetThreadInfo();
		if (ti!=NULL) {	
            MsgID=ti->GetMsgInfo()->toString(APLOG_DEBUG4);
		}
		else {
			MsgInfo msg;
			MsgID=msg.toString(APLOG_DEBUG4);
		}
	}
	catch(...){
		AppLogger::Write(ERR_ERROR,"Can't get message infomation.");
		// No action. Do not throw.
	}
	OutputMsg=(e.szMsg.length()>0)?e.szMsg:e.GetDetailErrText();
	for (i=0;i<AppLogNum;i++){
		if (AppLogPtr[i]!=NULL && 
			e.GetErrLevel() <= AppLogPtr[i]->GetOutputLevel()){
			try{
				AppLogPtr[i]->Open();
				AppLogPtr[i]->Lock();
				AppLogPtr[i]->SeekEnd();
				ftype=AppLogPtr[i]->GetLogFormatType();
				if (!strcmp(ftype.c_str(),"detail")){
					// write applog
					AppLogPtr[i]->Write(LOG_ERR
							,detailfmt
							,e.nErrCode
							,e.nDetailCode
							,e.nSysErrNo
							,e.szFuncStack.c_str()
							,MsgID.c_str()
							,OutputMsg.c_str()
							);
				}
				else {
					// write syslog
					AppLogPtr[i]->Write(LOG_ERR
							,genericfmt
							,e.nErrCode
							,MsgID.c_str()
							,OutputMsg.c_str()
							);
				}
				AppLogPtr[i]->FFlush();
				AppLogPtr[i]->UnLock();
				AppLogPtr[i]->Close();
				writeflg=true;
			}
			catch(...){
				AppLogPtr[i]->FFlush();
				AppLogPtr[i]->UnLock();
				AppLogPtr[i]->Close();
				exceptflg=true;
				// Do not throw.
			}
		}
	}

	if (exceptflg) {
		//�㳰��ȯ�����Ƥ��ơ�Update��Ǥʤ���硣
		AppLogInitNG=true;
		if (exceptflg) {
			AppLogger::Write(ERR_ERROR,"Logger write faild");
		}
	}
}

void AppLogger::Write(int level,std::string str) {
	Write(level,str.c_str());
}

void AppLogger::Write(std::string str) {
	Write(LOG_INFO,str.c_str());
}

void AppLogger::Write(const char * fmt,...){
	va_list args;
	bool exceptflg=false;
	bool execflg=false;
	int i;

	if (isMyLock()){
		//2�ť�å���
		Logger errlog;
		errlog.Write(APLOG_ERROR,"dead lock error!");
		return;
	}

	for (i=0;i<AppLogNum;i++){
		if (AppLogPtr[i]!=NULL && 
			LOG_INFO<= AppLogPtr[i]->GetOutputLevel()){
			execflg=true;
		}
	}
	if (execflg==false) {
		return ;
	}

	if ((AppLogInitNG && !AppLogUpdating)||AppLogFirstInit) {
		Initialize();
	}

	//va_�ϴؿ��Υ���å��б������������Τʤ��ᡢ��å���������
	try{
		Lock();
	}
	catch(...){
		return ;
	}

	va_start(args, fmt);
	try{
		Write(LOG_INFO,fmt,args);
	}
	catch(...){
		exceptflg=true;
	}
	va_end(args);
	UnLock();

	if (exceptflg) {
		//�㳰��ȯ�����Ƥ��ơ�Update��Ǥʤ���硣
		AppLogInitNG=true;
	}
}

void AppLogger::Write(int level,const char * fmt,...){
	va_list args;
	bool exceptflg=false;
	bool execflg=false;
	int i;

	if (isMyLock()){
		//2�ť�å���
		Logger errlog;
		errlog.Write(APLOG_ERROR,"dead lock error!");
		return;
	}

	for (i=0;i<AppLogNum;i++){
		if (AppLogPtr[i]!=NULL && 
			level<= AppLogPtr[i]->GetOutputLevel()){
			execflg=true;
		}
	}

	if (execflg==false) {
		return ;
	}

	if ((AppLogInitNG && !AppLogUpdating)||AppLogFirstInit) {
		//̤������ޤ��ϡ���������顼���֤ǡ����åץǡ�����Ǥʤ�����
		//���٥��åץǡ��Ȥ�Ԥ���
		Initialize();
	}

	//va_�ϴؿ��Υ���å��б������������Τʤ��ᡢ��å���������
	try{
		Lock();
	}
	catch(...){
		return ;
	}

	va_start(args, fmt);
	try{
		Write(level,fmt,args);
	}
	catch(...){
		exceptflg=true;
	}
	va_end(args);
	UnLock();

	if (exceptflg) {
		//�㳰��ȯ�����Ƥ��ơ�Update��Ǥʤ���硣
		AppLogInitNG=true;
	}
}
/*
��ꡧ�ʤ�
�㳰������
	���Ϥ˼��Ԥ��������㳰���֤���
���͡�
	�������֥������ȤΥ�å�����Ѥ��ƥ�å���Ԥ���
��ա�
	�ܴؿ��ϡ�Logger,SysLogger,FileLogger���饹�ʳ���
	OpenSOAPServer���饹��ƤФʤ����ȡ�
	¾�Υ��饹��ǡ��ܥ��饹���ƤФ줿���˥롼�פ����ǽ�������뤿�ᡣ
	�ޤ���ɬ����AppLogger���饹�Υ�å��ǥ�å���˸ƤӽФ����ȡ�
*/
void AppLogger::Write(int level,const char * fmt,va_list args){
	string wfmt;
	string ftype;
	int i=0;
	bool checkflg=false;	//���Ϥ��������� true=���ԡ�false=������
	bool outputflg=false;	//ɸ�२�顼���� true=���ϡ�false=�ʤ���
	bool exceptflg=false;
	
	for (i=0;i<AppLogNum;i++){
		if (AppLogPtr[i]!=NULL && level <= AppLogPtr[i]->GetOutputLevel()){
			checkflg=true;
			ftype=AppLogPtr[i]->GetLogFormatType();
			wfmt= (!strcmp(ftype.c_str(),"detail"))? 
					detailemptyfmt:genericemptyfmt;
			wfmt += fmt;
			try{
				AppLogPtr[i]->Open();
				AppLogPtr[i]->Lock();
				AppLogPtr[i]->SeekEnd();
				AppLogPtr[i]->Write(level,wfmt.c_str(),args);
				AppLogPtr[i]->FFlush();
				AppLogPtr[i]->UnLock();
				AppLogPtr[i]->Close();
				checkflg=false;
			}
			catch(...){
				try{
					AppLogPtr[i]->FFlush();
					AppLogPtr[i]->UnLock();
					AppLogPtr[i]->Close();
				}
				catch(...){
				}
				exceptflg=true;
			}
			if (checkflg) outputflg=true;
		}
	}
	if (outputflg){
		//���٤Ƥν��Ϥ˼��Ԥ������
		Logger errlog;
		errlog.Write(level,wfmt.c_str(),args);
	}
	if (exceptflg) {
		//���ٰʾ塢���Ϥ˼���(�㳰��ȯ���ˤ������
		throw Exception(-1,OPENSOAP_IO_ERROR,LOG_ERR,__FILE__,__LINE__);
	}
}

/*
��ꡧ����
	����ʸ�����Ŭ�礷����
	����ʸ���󤬼����Ǥ��ʤ��ä����(n=0)�ϡ�i�Ϲ�������ʤ���
	����ʸ�����Ŭ�礹���Τ�ʣ�����������Ƭ�����Ѥ���ޤ���
*/
int AppLogger::GetConfAttrInt(const char * key,int * i){
	return GetConfAttrIntWithBase(NULL,key,i);	
}

int AppLogger::GetConfAttrIntWithBase(const char * base,const char * key,int * i){
	int n=0;
	std::string buff;
	try{
		//�������б�����ǡ���ʸ����μ���
		n=GetConfAttrStringWithBase(base,key,buff);
		//�ǡ���ʸ����μ�����������å�
		if (n) {
			StringUtil::fromString(buff, *i);
		}
	}
	catch(...){
	}
	if (base!=NULL&&n<=0){
		n=GetConfAttrInt(key,i);
	}
	
	return n;	
}

/*
��ꡧ����
	����ʸ�����Ŭ�礷����
	����ʸ���󤬼����Ǥ��ʤ��ä����(n=0)�ϡ�buff�Ϲ�������ʤ���
	����ʸ�����Ŭ�礹���Τ�ʣ�����������Ƭ�����Ѥ���ޤ���
*/
int AppLogger::GetConfAttrString(const char * key,std::string& buff){
	return GetConfAttrStringWithBase(NULL,key,buff);
}

int AppLogger::GetConfAttrStringWithBase(const char * base
										,const char * key,std::string& buff){
	SrvConf	srvconf;
	std::vector<std::string> attrs;
	std::string queryStr;
	attrs.clear();
	
	int n=0;
	try{
		//�����꡼ʸ����κ���
		queryStr =  QUERY_LOG_SIGNATURE;
		if (base != NULL) {
			queryStr += base;
			queryStr += "/";
		}
		queryStr+=key;
		queryStr+=QUERY_OPT;
		srvconf.query(queryStr, attrs);
		if (attrs.size() > 0) {
			buff=attrs[0];
		}
		n=attrs.size();
	}
	catch(...){
	}
	return n;
}

/*
function:
	get /server_conf/Logging/xxxx/LogType=/? in server.conf
return:
	number of elements;	
	kn=
		LOG_TYPE_STDOUT	<-"stdout"  <----- same stderr
		LOG_TYPE_STDERR	<-"stderr"
		LOG_TYPE_FILE	<-"file"
		LOG_TYPE_SYSLOG	<-"syslog"
		LOG_TYPE_NOLOG	<-"none"
*/
int AppLogger::GetConfLogType(const char * base,int* kn){
	int n=0;
	int i=0;
	std::string buff;
	*kn=-1;
	n=GetConfAttrStringWithBase(base,QUERY_LOG_TYPE,buff);
	if (n <= 0) {
		return n;
	}
	for(i=0;LogTypeLists[i].code!=-1&&*kn==-1;i++) {
		if (!strcmp(buff.c_str(),LogTypeLists[i].name)) {
			*kn=LogTypeLists[i].code;
		}
	}
	if (*kn==-1) {
		n=0;
	}
	return n;
}

/*
function:
	get /server_conf/Logging/xxxx/LogFormat=/? in server.conf
return:
	number of elements;

	buff=
		"generic"
		"detail"
*/
int AppLogger::GetConfLogFormatType(const char * base,std::string& buff){
	return GetConfAttrStringWithBase(base,QUERY_LOG_FORMAT,buff);
}

int AppLogger::RotateCheck(){
	time_t t;
	time(&t);
	struct tm *tm=localtime(&t);
	if (LogDate.tm_mday!=tm->tm_mday||
		LogDate.tm_mon!=tm->tm_mon ||
		LogDate.tm_year!=tm->tm_year) {
		return -1;
	}
	return 0;
}

void AppLogger::Rotate(){
	int i;
	for (i=0;i<AppLogNum;i++){
		if (AppLogPtr[i]!=NULL){
			try{
				AppLogPtr[i]->Rotate();
				AppLogger::Write(LOG_INFO,"Rotate Log!");
			}
			catch(Exception e){
				e.AddFuncCallStack();
				AppLogger::Write(LOG_ERR,"Rotate log error!");
				AppLogger::Write(e);
			}
			catch(...){
				AppLogger::Write(LOG_ERR,"Rotate log error(unknown)!");
			}
		}
	}
}

apploglockid_t AppLogger::GetCurrentThreadID(){
  return pthread_self();
}
