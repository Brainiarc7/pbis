/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: SrvConfAttrMgr.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#ifndef SrvConfAttrMgr_H
#define SrvConfAttrMgr_H

#include <string>
#if defined(WIN32)
#include <windows.h>
#else
#include <pthread.h>
#endif
#include <list>
#include <libxml/tree.h>

#include "SrvConf.h"
#include "ThreadDef.h"

namespace OpenSOAP {

  class SrvConfAttrMgr : public SrvConf {

  public:
    SrvConfAttrMgr();
    virtual ~SrvConfAttrMgr();

    //�ʐM�J�n
    int run();

  private:
    //�f�[�^�̃����[�h���̃��b�N
      ThrMutexHandle loadXmlLock_;
    //pthread_cond_t  ;

#if defined(WIN32)
    int
#else
    //UNIX�h���C���\�P�b�g�A�h���X
    std::string 
#endif
    socketAddr_;

    //�ǂݍ��ݑΏ�XML�t�@�C���f�B���N�g��
    //std::string xmlDir_;

    //DOM�f�[�^�̃��X�g
    //std::list<xmlDocPtr> xmlList_;

    //XML�t�@�C���̓ǂݍ���
    int reloadXml();

    //xmlList_����DOM�\���J��
    //void freeXmlList();

    //�ʐM����
    static ThrFuncReturnType connectionThread(ThrFuncArgType arg);
    void connectProc(int sockfd);

    //for shm buffer
#if defined(WIN32)
    HANDLE shmMap;
    int createShm();
    void deleteShm();
#endif
    void clearShm();
    void addShm(const std::string& query, const std::string& value);
#if defined(WIN32)
    HANDLE
#else
    int 
#endif
    semid_; // SEM ID

    //  public: // for test
    std::string queryXml(const std::string& queryStr);

    typedef struct ThrDataTag {
      SrvConfAttrMgr* that;
      int sockfd;
    } ThrData;
  };

} // end of namespace OpenSOAP


#endif /* SrvConfAttrMgr_H */
