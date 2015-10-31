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
#include <cstdio>

namespace JumpSeat {
    
    class DateTime {
    public:

        DateTime() {
            timestamp_ = time(NULL);
        }

        DateTime(const time_t timestamp) : timestamp_(timestamp) {
        }

        std::string toString(const std::string& format) const {
            char buf[100];
            strftime(buf, sizeof (buf), format.c_str(), localtime(&timestamp_));
            return std::string(buf);
        }
        
        std::string toISO8601() const {
            return toString("%FT%T");
        }
        
        time_t getTimestamp() const {
            return timestamp_;
        }
    private:
        time_t timestamp_;
    };
    
    class Duration {
    public:
        
        Duration(const DateTime from, const DateTime to) : from_(from), to_(to) {
            diffInSeconds_ = (long) difftime(to.getTimestamp(), from.getTimestamp());
            seconds_ = (int) diffInSeconds_ % 60;
            minutes_ = (int) (diffInSeconds_ / 60) % 60;
            hours_ = (int) diffInSeconds_ / 3600;
        }
        
        int getHours() const {
            return hours_;
        }
        
        int getMinutes() const {
            return minutes_;
        }
        
        int getSeconds() const {
            return seconds_;
        }
        
        DateTime getFrom() const {
            return from_;
        }
        
        DateTime getTo() const {
            return to_;
        }
        
        std::string toString() const {
            char buf[15];
            sprintf(buf, "%02d:%02d:%02d", hours_, minutes_, seconds_);
            return std::string(buf);
        }
    private:
        DateTime from_;
        DateTime to_;
        long diffInSeconds_;
        int hours_;
        int minutes_;
        int seconds_;
    };

}

#endif	/* TIME_H */

