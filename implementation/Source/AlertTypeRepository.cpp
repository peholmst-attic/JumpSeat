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

#include "AlertTypeRepository.h"

JumpSeat::AlertTypeRepository::AlertTypeRepository(DB& db) :
db_(DB::executeAndReturn(db, "CREATE TABLE IF NOT EXISTS alerttypes (code TEXT PRIMARY KEY, description TEXT);")),
findByCodeStmt_(db, "SELECT code, description FROM alerttypes WHERE code = ?1;") {
}

boost::optional<JumpSeat::AlertType> JumpSeat::AlertTypeRepository::findByCode(const std::string& code) {
    findByCodeStmt_.setText(1, code);
    Cursor cursor = findByCodeStmt_.executeQuery();
    if (cursor.isDone()) {
        return boost::none;
    } else {
        AlertType at = AlertType{cursor.getText(0), cursor.getText(1)};
        findByCodeStmt_.reset();
        return at;
    }
}
