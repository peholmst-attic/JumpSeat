#ifndef ALERT_TYPE_REPOSITORY_H
#define	ALERT_TYPE_REPOSITORY_H

#include <boost/optional.hpp>

#include "AlertType.h"
#include "DB.h"

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

#endif	/* ALERT_TYPE_REPOSITORY_H */

