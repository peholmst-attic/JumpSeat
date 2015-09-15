#include <iostream>

#include "alert_logger.hpp"

void JumpSeat::AlertLogger::onReceiveAlert(const Alert& alert)
{
    std::cout << "=====" << std::endl;
    std::cout << "Received alert: [" << alert.type.code << "] [" << alert.type.description << "] [" << alert.municipality.get_value_or("N/A") << "] [" << alert.address.get_value_or("N/A") << "] [" << alert.details.get_value_or("N/A") << "]" << std::endl;
    std::cout << "=====" << std::endl;
}
