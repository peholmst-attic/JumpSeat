#include <iostream>

#include "alert_logger.hpp"

void JumpSeat::AlertLogger::onReceiveAlert(const Alert& alert)
{
    std::cout << "=====" << std::endl;
    std::cout << "Received alert: " << alert.municipality.value() << ": " << alert.address.value() << std::endl;
    std::cout << "=====" << std::endl;
}
