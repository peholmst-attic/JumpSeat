#ifndef ALERT_DISPATCHER_HPP
#define	ALERT_DISPATCHER_HPP

#include <vector>
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
        void setAlertRegex(const std::regex& regex, const std::vector<AlertField>& fields);
        void onReceiveSMS(const SMS& sms);  
    private:
        const AlertTypeRepository& alertTypeRepository_;
        std::regex regex_;      
        std::vector<AlertField> fields_; 
        OnAlert alertSignal_;
        
        bool isAlert(const SMS& sms);
        Alert createAlert(const SMS& sms);
        void setAlertField(const AlertField& field, const std::string& value, Alert& alert);
        std::string trim(const std::string& s);
    };
}

#endif	/* ALERT_DISPATCHER_HPP */

