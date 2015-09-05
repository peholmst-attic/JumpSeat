#include "alert_dispatcher.hpp"
#include <iostream>

void JumpSeat::AlertDispatcher::onReceiveSMS(const SMS& sms)
{
    std::cout << "Alert dispatcher received SMS: " << sms.message << std::endl;
}
