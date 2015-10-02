#ifndef ALERT_TYPE_REPOSITORY_HPP
#define	ALERT_TYPE_REPOSITORY_HPP

#include <boost/optional.hpp>

#include "alert_type.hpp"
#include "db.hpp"

namespace JumpSeat {

    class AlertTypeRepository {
    public:
        AlertTypeRepository(DB& db);
        boost::optional<AlertType> findByCode(const std::string& code);
    private:
        DB& db_;
        PreparedStatement findByCodeStmt_;
    };
}

#endif	/* ALERT_TYPE_REPOSITORY_HPP */

