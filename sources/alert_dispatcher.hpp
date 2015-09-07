#ifndef ALERT_DISPATCHER_HPP
#define	ALERT_DISPATCHER_HPP

#include <regex>

#include "sms.hpp"
#include "alert.hpp"
#include "alert_type_repository.hpp"

namespace JumpSeat
{
    class AlertDispatcher
    {
    public:
        AlertDispatcher(const AlertTypeRepository& alertTypeRepository);
        void addOnAlertHandler(const OnAlertHandler& handler);
        void setAlertRegex(const std::regex& regex);
        void setAlertFormat(const std::string& format);
        void onReceiveSMS(const SMS& sms);  
    private:
        const AlertTypeRepository& alertTypeRepository_;
        std::regex regex_;        
        OnAlert alertSignal_;
        
        bool isAlert(const SMS& sms);
        std::string extractCode(const SMS& sms);
        Alert createAlert(const SMS& sms);
    };
}

#endif	/* ALERT_DISPATCHER_HPP */

