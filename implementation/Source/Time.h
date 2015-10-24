#ifndef TIME_H
#define	TIME_H

#include <cstring>
#include <string>

namespace JumpSeat {

    class DateTime {
    public:

        DateTime() {
            time_t now = time(NULL);
            timestamp_ = *localtime(&now);
        }

        DateTime(const std::tm timestamp) : timestamp_(timestamp) {
        }

        std::string toString(const std::string& format) const {
            char buf[100];
            strftime(buf, sizeof (buf), format.c_str(), &timestamp_);
            return std::string(buf);
        }
        
        std::string toISO8601() const {
            return toString("%FT%T");
        }
    private:
        std::tm timestamp_;
    };
}

#endif	/* TIME_H */

