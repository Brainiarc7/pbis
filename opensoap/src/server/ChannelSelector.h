/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: ChannelSelector.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#ifndef ChannelSelector_H
#define ChannelSelector_H

#include <string>
#include <OpenSOAP/Defines.h>
#include "ChannelDescriptor.h"

namespace OpenSOAP {

    //ChannelManager�Ƃ̂��Ƃ�ɂ��Descriptor���𓾂�
    class OPENSOAP_CLASS ChannelSelector {
        
    public:
        virtual ~ChannelSelector();
        
    protected:
        ChannelSelector();
#if defined(WIN32)
        ChannelSelector(const int addr);
#else
        ChannelSelector(const std::string& addr);
#endif
        
    public:
        virtual int open(ChannelDescriptor& chnlDesc, 
                         const int waitSecond = ChannelDescriptor::NO_WAIT);
        virtual int close(ChannelDescriptor& chnlDesc);
        
    protected:
#if defined(WIN32)
        void setSocketAddr(const int addr);
#else
        void setSocketAddr(const std::string& addr);
#endif
        
        //ChannelManager�Ƃ̒ʐM�o�H�m��
        int connectChannelManager();
        
        virtual std::string makeSendOpenMessage(const int waitSecond);
        virtual std::string makeSendCloseMessage();

        //ChannelManager�Ƃ̒ʐM�o�H�w��
#if defined(WIN32)
	int
#else
        std::string
#endif
    	socketAddr_;
        
    };

} // end of namespace OpenSOAP


#endif /* ChannelSelector_H */
