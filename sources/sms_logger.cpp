#include <iostream>
#include <string>

#include "sms_logger.hpp"

JumpSeat::SMSLogger::SMSLogger(DB& db) :
db_(DB::executeAndReturn(db, "CREATE TABLE IF NOT EXISTS smslog (id INTEGER PRIMARY KEY, sender TEXT, msg TEXT, ts DATETIME);")),
insertSmsStmt_(db, "INSERT INTO smslog (sender, msg) VALUES (?1,?2);") {
}

void JumpSeat::SMSLogger::onReceiveSMS(const SMS& sms) {
    insertSmsStmt_.reset();
    insertSmsStmt_.setText(1, sms.sender);
    insertSmsStmt_.setText(2, sms.message);
    insertSmsStmt_.execute();
    // TODO What about timestamps?
    std::cout << "Received SMS: " << sms.message << std::endl;
}
