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

#ifndef SMS_H
#define	SMS_H

#include <string>
#include <boost/signals2/signal.hpp>

#include "Time.h"

namespace JumpSeat {

    struct SMS {
        std::string sender;
        std::string message;
        DateTime timestamp;
    };

    typedef boost::signals2::signal<void (const SMS&)> OnSMS;
    typedef OnSMS::slot_type OnSMSHandler;
    
    class SMSPublisher {
    public:
        boost::signals2::connection connect(const OnSMSHandler& handler) {
            return signal_.connect(handler);
        }
    protected:
        void publishSMS(const SMS& sms) {
            signal_(sms);
        }
    private:
        OnSMS signal_;
    };
    
    class SMSSubscriber {
    public:
        SMSSubscriber(SMSPublisher& publisher) : publisher_(publisher) {
            connection_ = publisher_.connect(boost::bind(&SMSSubscriber::onReceiveSMS, this, _1));
        }
        
        virtual ~SMSSubscriber() {
            connection_.disconnect();
        }
        
        virtual void onReceiveSMS(const SMS& sms) = 0;
    private:
        SMSPublisher& publisher_;
        boost::signals2::connection connection_;
    };
    
}

#endif	/* SMS_H */

