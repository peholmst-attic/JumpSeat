#include "modem_io.hpp"

void JumpSeat::ModemIO::addOnSMSHandler(const OnSMSHandler& handler) {
    smsSignal_.connect(handler);
}

void JumpSeat::ModemIO::addOnPhoneCallHandler(const OnPhoneCallHandler& handler) {
    phoneCallSignal_.connect(handler);
}

void JumpSeat::ModemIO::signalFakeSms(const std::string& message) {
    SMS sms;
    sms.sender = "+358123456";
    sms.message = message;
    smsSignal_(sms);
}
