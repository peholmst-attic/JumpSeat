#ifndef ALERT_TYPE_REPOSITORY_HPP
#define	ALERT_TYPE_REPOSITORY_HPP

#include <boost/optional.hpp>

#include "alert_type.hpp"

namespace JumpSeat {

    class AlertTypeRepository {
    public:
        boost::optional<AlertType> findByCode(const std::string& code) const;
    };
}

#endif	/* ALERT_TYPE_REPOSITORY_HPP */

