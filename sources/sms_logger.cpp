#include <iostream>

#include "sms_logger.hpp"

void JumpSeat::SMSLogger::onReceiveSMS(const SMS& sms)
{
    std::cout << "Received SMS: " << sms.message << std::endl;
}
