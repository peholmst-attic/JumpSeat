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

#include "AlertLogger.h"
#include <iostream>

JumpSeat::AlertLogger::AlertLogger(DB& db, AlertPublisher& alertPublisher) :
    AlertSubscriber(alertPublisher),
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
