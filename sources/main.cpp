#include <cstdlib>

#include "modem_io.hpp"
#include "sms_logger.hpp"
#include "alert_dispatcher.hpp"
#include "response_dispatcher.hpp"
#include "alert_type_repository.hpp"
#include "alert_logger.hpp"

using namespace std;

int main(int argc, char** argv) {
    // Create modules
    auto modemIO = JumpSeat::ModemIO();
    auto smsLogger = JumpSeat::SMSLogger();
    auto alertTypeRepository = JumpSeat::AlertTypeRepository();
    
    auto alertDispatcher = JumpSeat::AlertDispatcher(alertTypeRepository);    
    alertDispatcher.setAlertRegex(
        std::regex("^TKU ([A-Za-z\\s]*[0-9]+)[\\w\\s],([\\w\\s]*,[\\w\\s]*),([\\w\\s]*,[\\w\\s]*,[\\w\\s]*),(.*)"),
        std::vector<JumpSeat::AlertField>{
            JumpSeat::AlertField::code, 
            JumpSeat::AlertField::municipality, 
            JumpSeat::AlertField::address,
            JumpSeat::AlertField::details
        }
    );
        
    auto responseDispatcher = JumpSeat::ResponseDispatcher();
    auto alertLogger = JumpSeat::AlertLogger();
    
    // Set up handlers
    modemIO.addOnSMSHandler(boost::bind(&JumpSeat::SMSLogger::onReceiveSMS, &smsLogger, _1));
    modemIO.addOnSMSHandler(boost::bind(&JumpSeat::AlertDispatcher::onReceiveSMS, &alertDispatcher, _1));
    modemIO.addOnSMSHandler(boost::bind(&JumpSeat::ResponseDispatcher::onReceiveSMS, &responseDispatcher, _1));
    
    alertDispatcher.addOnAlertHandler(boost::bind(&JumpSeat::AlertLogger::onReceiveAlert, &alertLogger, _1));
    
    // Send a few fake SMSes
    modemIO.signalFakeSms("TKU 432 ,PARGAS,,address,,,RVSPG11,RVSPG31,RVSPG13,RVSIT3,,description");
    modemIO.signalFakeSms("TKU 402A,PARGAS,NAGU,address,,,RVSPG11,RVSPG31,RVSPG13,RVSIT3,,description");
    modemIO.signalFakeSms("TKU 203A,PARGAS,,address1,address2,,RVSPG11,RVSPG31,,description");
    modemIO.signalFakeSms("TKU 103 ,PARGAS,,address,,name,RVSPG11,RVSPG31,,description ");
    modemIO.signalFakeSms("TKU ANNULERING AV UPPDRAG 221 ,PARGAS,NAGU,,,,");
    modemIO.signalFakeSms("Another SMS");
    
    return 0;
}

