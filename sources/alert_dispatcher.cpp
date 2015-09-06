#include "alert_dispatcher.hpp"
#include <iostream>

JumpSeat::AlertDispatcher::AlertDispatcher(const JumpSeat::AlertTypeRepository& alertTypeRepository) :
    alertTypeRepository_(alertTypeRepository)
{
}

void JumpSeat::AlertDispatcher::addOnAlertHandler(const OnAlertHandler& handler)
{
    alertSignal_.connect(handler);
}

void JumpSeat::AlertDispatcher::setAlertRegex(const std::regex& regex)
{
    regex_ = regex;
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
    return false; // TODO
}

JumpSeat::Alert JumpSeat::AlertDispatcher::createAlert(const SMS& sms)
{
    return Alert(); // TODO
}