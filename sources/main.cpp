#include <cstdlib>

#include "modem_io.hpp"
#include "sms_logger.hpp"
#include "alert_dispatcher.hpp"
#include "response_dispatcher.hpp"
#include "alert_type_repository.hpp"

using namespace std;

int main(int argc, char** argv) {
    auto modemIO = JumpSeat::ModemIO();
    auto smsLogger = JumpSeat::SMSLogger();
    auto alertTypeRepository = JumpSeat::AlertTypeRepository();
    auto alertDispatcher = JumpSeat::AlertDispatcher(alertTypeRepository);
    auto responseDispatcher = JumpSeat::ResponseDispatcher();
    
    modemIO.addOnSMSHandler(boost::bind(&JumpSeat::SMSLogger::onReceiveSMS, &smsLogger, _1));
    modemIO.addOnSMSHandler(boost::bind(&JumpSeat::AlertDispatcher::onReceiveSMS, &alertDispatcher, _1));
    modemIO.addOnSMSHandler(boost::bind(&JumpSeat::ResponseDispatcher::onReceiveSMS, &responseDispatcher, _1));
    
    modemIO.signalFakeSms("Hello World");
    modemIO.signalFakeSms("Another SMS");
    
    return 0;
}

