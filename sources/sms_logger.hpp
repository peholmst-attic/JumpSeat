#ifndef SMS_LOGGER_HPP
#define	SMS_LOGGER_HPP

#include "sms.hpp"
#include "db.hpp"

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

#endif	/* SMS_LOGGER_HPP */

