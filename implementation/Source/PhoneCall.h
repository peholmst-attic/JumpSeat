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

#ifndef PHONE_CALL_H
#define	PHONE_CALL_H

#include <ctime>
#include <string>
#include <boost/signals2/signal.hpp>

#include "Time.h"

namespace JumpSeat {

    struct PhoneCall {
        std::string number;
        DateTime timestamp;
    };

    typedef boost::signals2::signal<void (const PhoneCall&) > OnPhoneCall;
    typedef OnPhoneCall::slot_type OnPhoneCallHandler;
    
    class PhoneCallPublisher {
    public:
        boost::signals2::connection connect(const OnPhoneCallHandler& handler) {
            return signal_.connect(handler);
        }
    protected:
        void publishPhoneCall(const PhoneCall& phoneCall) {
            signal_(phoneCall);
        }
    private:
        OnPhoneCall signal_;
    };
    
    class PhoneCallSubscriber {
    public:
        PhoneCallSubscriber(PhoneCallPublisher& publisher) : publisher_(publisher) {
            connection_ = publisher_.connect(boost::bind(&PhoneCallSubscriber::onReceivePhoneCall, this, _1));
        }
        
        virtual ~PhoneCallSubscriber() {
            connection_.disconnect();
        }
        
        virtual void onReceivePhoneCall(const PhoneCall& phoneCall) = 0;
    private:
        PhoneCallPublisher& publisher_;
        boost::signals2::connection connection_;
    };
}

#endif	/* PHONE_CALL_H */

