/*
 * JumpSeat
 * Copyright (C) 2015 Petter Holmström
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

