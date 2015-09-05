#include "response_dispatcher.hpp"
#include <iostream>

void JumpSeat::ResponseDispatcher::onReceiveSMS(const SMS& sms)
{
    std::cout << "Response dispatcher received SMS: " << sms.message << std::endl;
}

void JumpSeat::ResponseDispatcher::onReceivePhoneCall(const PhoneCall& phoneCall)
{
    std::cout << "Response dispatcher received phone call from: " << phoneCall.number;
}