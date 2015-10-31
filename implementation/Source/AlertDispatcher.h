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

#ifndef ALERT_DISPATCHER_H
#define	ALERT_DISPATCHER_H

#include <vector>
#include <regex>

#include "SMS.h"
#include "Alert.h"
#include "AlertTypeRepository.h"

namespace JumpSeat {

    class AlertDispatcher {
    public:
        AlertDispatcher(AlertTypeRepository& alertTypeRepository);
        void addOnAlertHandler(const OnAlertHandler& handler);
        void setAlertRegex(const std::regex& regex, const std::vector<AlertField>& fields);
        void onReceiveSMS(const SMS& sms);
    private:
        AlertTypeRepository& alertTypeRepository_;
        std::regex regex_;
        std::vector<AlertField> fields_;
        OnAlert alertSignal_;

        bool isAlert(const SMS& sms);
        Alert createAlert(const SMS& sms);
        void setAlertField(const AlertField& field, const std::string& value, Alert& alert);
        std::string trim(const std::string& s);
        
        // Prevent AlertDispatcher from being copied
        AlertDispatcher(const AlertDispatcher&);
        AlertDispatcher& operator=(const AlertDispatcher&);
    };
}

#endif	/* ALERT_DISPATCHER_H */

