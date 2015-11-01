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

#ifndef ALERT_LOGGER_H
#define	ALERT_LOGGER_H

#include "Alert.h"
#include "DB.h"

namespace JumpSeat {

    class AlertLogger : public AlertSubscriber {
    public:
        AlertLogger(DB& db, AlertPublisher& alertPublisher);
        void onReceiveAlert(const Alert& alert) override;
    private:
        DB& db_;
        PreparedStatement insertAlertStmt_;

        // Prevent AlertLogger from being copied
        AlertLogger(const AlertLogger&);
        AlertLogger& operator=(const AlertLogger&);
    };
}

#endif	/* ALERT_LOGGER_H */

