#include "SMSLogger.h"

JumpSeat::SMSLogger::SMSLogger(DB& db) :
db_(DB::executeAndReturn(db, "CREATE TABLE IF NOT EXISTS smslog (id INTEGER PRIMARY KEY, sender TEXT, msg TEXT, ts DATETIME);")),
insertSmsStmt_(db, "INSERT INTO smslog (sender, msg, ts) VALUES (?1,?2,?3);") {
}

void JumpSeat::SMSLogger::onReceiveSMS(const SMS& sms) {
    insertSmsStmt_.setText(1, sms.sender);
    insertSmsStmt_.setText(2, sms.message);
    insertSmsStmt_.setText(3, sms.timestamp.toISO8601());
    insertSmsStmt_.execute();
}
