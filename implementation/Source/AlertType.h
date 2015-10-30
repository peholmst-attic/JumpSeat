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

#ifndef ALERT_TYPE_H
#define	ALERT_TYPE_H

#include <string>

namespace JumpSeat {

    static const std::string DEFAULT_COLOR = "FFFF0000";
    
    struct AlertType {
        AlertType() :
            colorHexCode(DEFAULT_COLOR) {}
        AlertType(std::string code, std::string description) :
            code(code),
            description(description),
            colorHexCode(DEFAULT_COLOR) {}
        
        std::string code;
        std::string description;
        std::string colorHexCode;
    };
}

#endif	/* ALERT_TYPE_H */

