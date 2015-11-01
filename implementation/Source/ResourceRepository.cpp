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

#include "ResourceRepository.h"

JumpSeat::ResourceRepository::ResourceRepository(DB& db) :
    db_(DB::executeAndReturn(db, "CREATE TABLE IF NOT EXISTS resources (phone TEXT PRIMARY KEY, name TEXT, ems INTEGER, driver INTEGER, officer INTEGER, scba INTEGER, water INTEGER);")),
    findByPhoneNumberStmt_(db, "SELECT name, phone, ems, driver, officer, scba, water FROM resources WHERE phone = ?1;") {
}

boost::optional<JumpSeat::Resource> JumpSeat::ResourceRepository::findByPhoneNumber(const std::string &phoneNumber) {
    findByPhoneNumberStmt_.setText(1, phoneNumber);
    Cursor cursor = findByPhoneNumberStmt_.executeQuery();
    if (cursor.isDone()) {
        return boost::none;
    } else {
        Resource r = Resource{
            cursor.getText(0),
            cursor.getText(1),
            cursor.getInt(2) != 0,
            cursor.getInt(3) != 0,
            cursor.getInt(4) != 0,
            cursor.getInt(5) != 0,
            cursor.getInt(6) != 0
        };
        findByPhoneNumberStmt_.reset();
        return r;
    }
}
