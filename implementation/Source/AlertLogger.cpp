#include "AlertLogger.h"
#include <iostream>

JumpSeat::AlertLogger::AlertLogger(DB& db) :
db_(DB::executeAndReturn(db, "CREATE TABLE IF NOT EXISTS alertlog (id INTEGER PRIMARY KEY, code TEXT, description TEXT, municipality TEXT, address TEXT, details TEXT, ts DATETIME);")),
insertAlertStmt_(db, "INSERT INTO alertlog (code, description, municipality, address, details, ts) VALUES (?1,?2,?3,?4,?5,?6);") {
}

void JumpSeat::AlertLogger::onReceiveAlert(const Alert& alert) {
    insertAlertStmt_.setText(1, alert.type.code);
    insertAlertStmt_.setText(2, alert.type.description);
    insertAlertStmt_.setText(3, alert.municipality.get_value_or(""));
    insertAlertStmt_.setText(4, alert.address.get_value_or(""));
    insertAlertStmt_.setText(5, alert.details.get_value_or(""));
    insertAlertStmt_.setText(6, alert.timestamp.toISO8601());
    insertAlertStmt_.execute();
}
