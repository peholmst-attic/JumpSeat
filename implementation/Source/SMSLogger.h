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

