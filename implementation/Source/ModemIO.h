#ifndef MODEM_IO_H
#define	MODEM_IO_H

#include <string>

#include "SMS.h"
#include "PhoneCall.h"

namespace JumpSeat {

    class ModemIO {
    public:
        void addOnSMSHandler(const OnSMSHandler& handler);
        void addOnPhoneCallHandler(const OnPhoneCallHandler& handler);
        void signalFakeSms(const std::string& message);
    private:
        OnSMS smsSignal_;
        OnPhoneCall phoneCallSignal_;
    };
}

#endif	/* MODEM_IO_H */

