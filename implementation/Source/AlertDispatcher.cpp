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

#include "AlertDispatcher.h"
#include <iostream>

JumpSeat::AlertDispatcher::AlertDispatcher(JumpSeat::AlertTypeRepository& alertTypeRepository) :
alertTypeRepository_(alertTypeRepository) {
}

void JumpSeat::AlertDispatcher::addOnAlertHandler(const OnAlertHandler& handler) {
    alertSignal_.connect(handler);
}

void JumpSeat::AlertDispatcher::setAlertRegex(const std::regex& regex, const std::vector<AlertField>& fields) {
    regex_ = regex;
    fields_ = fields;
}

void JumpSeat::AlertDispatcher::onReceiveSMS(const SMS& sms) {
    if (isAlert(sms)) {
        Alert alert = createAlert(sms);
        alertSignal_(alert);
    }
}

bool JumpSeat::AlertDispatcher::isAlert(const SMS& sms) {
    return std::regex_match(sms.message, regex_);
}

JumpSeat::Alert JumpSeat::AlertDispatcher::createAlert(const SMS& sms) {
    std::smatch m;
    std::regex_match(sms.message, m, regex_);

    Alert alert;
    for (int i = 0; i < fields_.size(); ++i) {
        setAlertField(fields_[i], m[i + 1], alert);
    }
    alert.message = sms.message;
    alert.timestamp = sms.timestamp;
    return alert;
}

void JumpSeat::AlertDispatcher::setAlertField(const AlertField& field, const std::string& value, Alert& alert) {
    switch (field) {
        case AlertField::address:
        {
            alert.address = trim(value);
            break;
        }
        case AlertField::code:
        {
            auto code = trim(value);
            auto alertType = alertTypeRepository_.findByCode(code);
            alert.type = alertType.get_value_or(AlertType{"", code});
            break;
        }
        case AlertField::municipality:
        {
            alert.municipality = trim(value);
            break;
        }
        case AlertField::details:
        {
            alert.details = trim(value);
            break;
        }
    }
}

std::string JumpSeat::AlertDispatcher::trim(const std::string& s) {
    return std::regex_replace(s, std::regex("[^\\w]+$"), "");
}
