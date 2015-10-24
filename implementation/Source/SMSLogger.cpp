/*
 * JumpSeat
 * Copyright (C) 2015 Petter Holmström
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
