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

#ifndef MODEM_IO_H
#define	MODEM_IO_H

#include <string>

#include "SMS.h"
#include "PhoneCall.h"

namespace JumpSeat {

    class ModemIO {
    public:
        void addOnSMSHandler(const OnSMSHandler& handler);
        void addOnPhoneCallHandler(const OnPhoneCallHandler& handler);
        void signalFakeSms(const std::string& message);
    private:
        OnSMS smsSignal_;
        OnPhoneCall phoneCallSignal_;

        // Prevent ModemIO from being copied
        ModemIO(const ModemIO&);
        ModemIO& operator=(const ModemIO&);
    };
}

#endif	/* MODEM_IO_H */

