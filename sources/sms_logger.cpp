#include <iostream>
#include <string>

#include "sms_logger.hpp"

const std::string JumpSeat::SMSLogger::DDL_ = "CREATE TABLE IF NOT EXISTS smslog (id INTEGER PRIMARY KEY, sender TEXT, msg TEXT, ts NUMERIC)";

JumpSeat::SMSLogger::SMSLogger(DB& db) : 
    db_(db)
{
    db_.execute(DDL_);
}

void JumpSeat::SMSLogger::onReceiveSMS(const SMS& sms)
{
    std::cout << "Received SMS: " << sms.message << std::endl;
}
