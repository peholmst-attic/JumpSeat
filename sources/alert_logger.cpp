#include <iostream>

#include "alert_logger.hpp"

void JumpSeat::AlertLogger::onReceiveAlert(const Alert& alert)
{
    std::cout << "Received alert: " << alert.message << std::endl;
}
