/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: TTLManager.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#ifndef TTLManager_H
#define TTLManager_H

#include <string>

#include "ChannelManager.h"

namespace OpenSOAP {

  //prototype def.
  class ChannelDescriptor;
  class TTL;
  
  class TTLManager : public ChannelManager {
  private:
    TTL* ttlPtr;
    
  public:

    TTLManager();
    virtual ~TTLManager();

  protected:

    //���̃��\�b�h���T�u�N���X���Ɏ�������D
    virtual void doProc(int sockfd);

    //���s���̃C���X�^���X��
    int execCount_;

  };

} // end of namespace OpenSOAP


#endif /* TTLManager_H */
