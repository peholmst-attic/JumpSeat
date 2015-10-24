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
    };
}

#endif	/* ALERT_DISPATCHER_H */

