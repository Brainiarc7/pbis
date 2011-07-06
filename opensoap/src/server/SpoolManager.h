/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: SpoolManager.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#ifndef SpoolManager_H
#define SpoolManager_H

#include <string>

#include "ChannelManager.h"

namespace OpenSOAP {

  //prototype def.
  class ChannelDescriptor;
  class Spool;
  
  class SpoolManager : public ChannelManager {
  private:
    Spool* resSpoolPtr;
    
  public:

    SpoolManager();
    virtual ~SpoolManager();

  protected:

    //���̃��\�b�h���T�u�N���X���Ɏ�������D
    virtual void doProc(int sockfd);

    //���s���̃C���X�^���X��
    int execCount_;

  };

} // end of namespace OpenSOAP


#endif /* SpoolManager_H */
