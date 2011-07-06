/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: MsgDrvCreator.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#ifndef MsgDrvCreator_H
#define MsgDrvCreator_H

#include <string>

#include "ChannelManager.h"
#include "SrvConf.h"
#include "Rule.h"
//using namespace
#include "ServerDef.h"

#include <OpenSOAP/Transport.h>

namespace OpenSOAP {

    //prototype def.
    class ChannelDescriptor;

  class MsgDrvCreator : public ChannelManager {

  private:
      //added 2004/01/04
      Rule* rule;

  public:

    MsgDrvCreator();
    virtual ~MsgDrvCreator();

  public:

    //socket address �w�� (run()���s�O����)
    //bool setSocketAddr(const std::string& addr);

    //��M�҂����s�J�n
    //void run();

  protected:
    SrvConf srvConf;
    //std::string socketAddr_;

      bool invalidMyselfUrl_;
      std::string myselfUrl_;
      OpenSOAPTransportPtr transport;

      bool checkUrl(const std::string& url);
      static
#if defined(WIN32)
      void
#else
      void*
#endif
      timeredConnectCheck(void* arg);



    //�ʐM���̃T�u�X���b�h
    //���X���b�h�֐��̎d�l�ɂ��C�{�{�N���X�ł�
    //  �X�^�e�B�b�N���\�b�h�ł���K�v������D
    //static void* connectionThread(void* arg);

    //���̃��\�b�h���T�u�N���X���Ɏ�������D
    virtual void doProc(int sockfd);
#if 0
    //virtual std::string parseReadData(const std::string& aReadData);
    virtual int parseAndOpen(const std::string& aReadData,
			     std::string& response,
			     ChannelDescriptor& chnlDesc);
#endif



    //���s���̃C���X�^���X��
    int execCount_;

  };

} // end of namespace OpenSOAP


#endif /* MsgDrvCreator_H */
