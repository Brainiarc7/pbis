/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: ChannelManager.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#ifndef ChannelManager_H
#define ChannelManager_H

#include <sys/types.h>
#include <string>

#include <OpenSOAP/Defines.h>
#include "ThreadDef.h"

namespace OpenSOAP {

    //prototype def.
    class ChannelDescriptor;
    
    class OPENSOAP_CLASS ChannelManager {
        
    public:
        ChannelManager();
        virtual ~ChannelManager();
        
    public:
        
        //socket address �w�� (run()���s�O����)
#if defined(WIN32)
        bool setSocketAddr(const int addr);
#else
        bool setSocketAddr(const std::string& addr);
#endif
        
        // Socket �쐬�̍ۂ̃}�X�N�̎w��
#if defined(WIN32)
        void setMask(int newMask);
#else
        void setMask(::mode_t newMask);
#endif
        //��M�҂����s�J�n
        void run();
        
    protected:
#if defined(WIN32)
	int
#else
        std::string 
#endif
        socketAddr_;
#if defined(WIN32)
	int
#else
	::mode_t 
#endif
        newMask_, curMask;
        bool setMaskFlag;
        //�ʐM���̃T�u�X���b�h
        //���X���b�h�֐��̎d�l�ɂ��C�{�{�N���X�ł�
        //  �X�^�e�B�b�N���\�b�h�ł���K�v������D
	static
        ThrFuncReturnType connectionThread(ThrFuncArgType arg);
        
        //���̃��\�b�h���T�u�N���X���Ɏ�������D
        virtual void doProc(int sockfd);

        typedef struct ThrDataTag {
            ChannelManager* that;
            int sockfd;
        } ThrData;

    };

} // end of namespace OpenSOAP


#endif /* ChannelManager_H */
