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

#ifndef RESOURCE_REPOSITORY_H
#define	RESOURCE_REPOSITORY_H

#include <boost/optional.hpp>

#include "Resource.h"
#include "DB.h"

namespace JumpSeat {
    
    class ResourceRepository {
    public:
        ResourceRepository(DB& db);
        boost::optional<Resource> findByPhoneNumber(const std::string& phoneNumber);
    private:
        DB& db_;
        PreparedStatement findByPhoneNumberStmt_;
        
        // Prevent ResourceRepository from being copied
        ResourceRepository(const ResourceRepository&);
        ResourceRepository& operator=(const ResourceRepository&);
    };
}

#endif	/* RESOURCE_REPOSITORY_H */

