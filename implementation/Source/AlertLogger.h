#ifndef ALERT_LOGGER_H
#define	ALERT_LOGGER_H

#include "Alert.h"
#include "DB.h"

namespace JumpSeat {

    class AlertLogger {
    public:
        AlertLogger(DB& db);
        void onReceiveAlert(const Alert& alert);
    private:
        DB& db_;
        PreparedStatement insertAlertStmt_;
    };
}

#endif	/* ALERT_LOGGER_H */

