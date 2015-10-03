#ifndef ALERT_LOGGER_HPP
#define	ALERT_LOGGER_HPP

#include "alert.hpp"
#include "db.hpp"

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

#endif	/* ALERT_LOGGER_HPP */

