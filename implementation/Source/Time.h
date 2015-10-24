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

#ifndef TIME_H
#define	TIME_H

#include <cstring>
#include <string>

namespace JumpSeat {

    class DateTime {
    public:

        DateTime() {
            time_t now = time(NULL);
            timestamp_ = *localtime(&now);
        }

        DateTime(const std::tm timestamp) : timestamp_(timestamp) {
        }

        std::string toString(const std::string& format) const {
            char buf[100];
            strftime(buf, sizeof (buf), format.c_str(), &timestamp_);
            return std::string(buf);
        }
        
        std::string toISO8601() const {
            return toString("%FT%T");
        }
    private:
        std::tm timestamp_;
    };
}

#endif	/* TIME_H */

