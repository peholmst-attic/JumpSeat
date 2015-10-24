#ifndef RESPONSE_DISPATCHER_H
#define	RESPONSE_DISPATCHER_H

#include "SMS.h"
#include "PhoneCall.h"

namespace JumpSeat {

    class ResponseDispatcher {
    public:
        void onReceiveSMS(const SMS& sms);
        void onReceivePhoneCall(const PhoneCall& phoneCall);
    };
}

#endif	/* RESPONSE_DISPATCHER_H */

