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

#ifndef SMS_LOGGER_H
#define	SMS_LOGGER_H

#include "SMS.h"
#include "DB.h"

namespace JumpSeat {

    class SMSLogger {
    public:
        SMSLogger(DB& db);
        void onReceiveSMS(const SMS& sms);
    private:
        DB& db_;
        PreparedStatement insertSmsStmt_;
    };
}

#endif	/* SMS_LOGGER_H */

