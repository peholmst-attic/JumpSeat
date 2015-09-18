#include "alert_dispatcher.hpp"
#include <iostream>

JumpSeat::AlertDispatcher::AlertDispatcher(JumpSeat::AlertTypeRepository& alertTypeRepository) :
    alertTypeRepository_(alertTypeRepository)
{
}

void JumpSeat::AlertDispatcher::addOnAlertHandler(const OnAlertHandler& handler)
{
    alertSignal_.connect(handler);
}

void JumpSeat::AlertDispatcher::setAlertRegex(const std::regex& regex, const std::vector<AlertField>& fields)
{
    regex_ = regex;
    fields_ = fields;
}

void JumpSeat::AlertDispatcher::onReceiveSMS(const SMS& sms)
{
    if (isAlert(sms))
    {
        Alert alert = createAlert(sms);
        alertSignal_(alert);
    }
}

bool JumpSeat::AlertDispatcher::isAlert(const SMS& sms)
{
    return std::regex_match(sms.message, regex_);
}

JumpSeat::Alert JumpSeat::AlertDispatcher::createAlert(const SMS& sms)
{    
    std::smatch m;
    std::regex_match(sms.message, m, regex_);
    
    Alert alert;
    for (int i = 0; i < fields_.size(); ++i)
    {
        setAlertField(fields_[i], m[i+1], alert);
    }    
    alert.message = sms.message;
    alert.timestamp = sms.timestamp;
    return alert;
}

void JumpSeat::AlertDispatcher::setAlertField(const AlertField& field, const std::string& value, Alert& alert) 
{
    switch(field) 
    {
        case AlertField::address: {
            alert.address = trim(value); 
            break;
        }
        case AlertField::code: {
            auto code = trim(value);
            auto alertType = alertTypeRepository_.findByCode(code);
            alert.type = alertType.get_value_or(AlertType{"", code});
            break;
        }
        case AlertField::municipality: {
            alert.municipality = trim(value);
            break;
        }
        case AlertField::details: {
            alert.details = trim(value);
            break;
        }
    }
}

std::string JumpSeat::AlertDispatcher::trim(const std::string& s) {
    return std::regex_replace(s, std::regex("[^\\w]+$"), "");
}
