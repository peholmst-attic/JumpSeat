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

#include "ModemIO.h"

void JumpSeat::ModemIO::addOnSMSHandler(const OnSMSHandler& handler) {
    smsSignal_.connect(handler);
}

void JumpSeat::ModemIO::addOnPhoneCallHandler(const OnPhoneCallHandler& handler) {
    phoneCallSignal_.connect(handler);
}

void JumpSeat::ModemIO::signalFakeSms(const std::string& message) {
    SMS sms;
    sms.sender = "+358123456";
    sms.message = message;
    smsSignal_(sms);
}
