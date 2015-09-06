#include "modem_io.hpp"

void JumpSeat::ModemIO::addOnSMSHandler(const OnSMSHandler& handler)
{
    smsSignal_.connect(handler);
}

void JumpSeat::ModemIO::addOnPhoneCallHandler(const OnPhoneCallHandler& handler) {
    phoneCallSignal_.connect(handler);
}

void JumpSeat::ModemIO::signalFakeSms(const std::string& message)
{
    time_t now = time(0);
    SMS sms;
    sms.message = message;
    sms.timestamp = *localtime(&now);
    smsSignal_(sms);
}
