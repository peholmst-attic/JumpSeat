#ifndef RESPONSE_DISPATCHER_HPP
#define	RESPONSE_DISPATCHER_HPP

#include "sms.hpp"
#include "phone_call.hpp"

namespace JumpSeat
{
    class ResponseDispatcher
    {
    public:
        void onReceiveSMS(const SMS& sms);     
        void onReceivePhoneCall(const PhoneCall& phoneCall);
    };
}

#endif	/* RESPONSE_DISPATCHER_HPP */

