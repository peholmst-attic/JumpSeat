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

#include "DB.h"

JumpSeat::DB::DB(const std::string& dbFile) {
    sqlite3_open(dbFile.c_str(), &db_);
}

JumpSeat::DB::~DB() {
    sqlite3_close(db_);
}

void JumpSeat::DB::execute(const std::string& sql) {
    char *errMsg = 0;
    int code = sqlite3_exec(db_, sql.c_str(), 0, 0, &errMsg);
    if (code != SQLITE_OK) {
        auto errMsgStr = std::string(errMsg);
        sqlite3_free(errMsg);
        throw DBException(code, errMsgStr);
    }
}

JumpSeat::DB& JumpSeat::DB::executeAndReturn(DB& db, const std::string& sql) {
    db.execute(sql);
    return db;
}

JumpSeat::PreparedStatement::PreparedStatement(DB& db, const std::string& sql) {
    throwOnError(sqlite3_prepare_v2(db.db_, sql.c_str(), -1, &stmt_, NULL),
            "error preparing statement");
}

JumpSeat::PreparedStatement::~PreparedStatement() {
    sqlite3_finalize(stmt_);
}

void JumpSeat::PreparedStatement::reset() {
    throwOnError(sqlite3_reset(stmt_),
            "error reseting statement");
}

void JumpSeat::PreparedStatement::setNull(const int index) {
    throwOnError(sqlite3_bind_null(stmt_, index),
            "error setting null");
}

void JumpSeat::PreparedStatement::setText(const int index, const std::string& value) {
    throwOnError(sqlite3_bind_text(stmt_, index, value.c_str(), -1, SQLITE_TRANSIENT),
            "error setting text");
}

void JumpSeat::PreparedStatement::setInt(const int index, const int value) {
    throwOnError(sqlite3_bind_int(stmt_, index, value),
            "error setting int");
}

void JumpSeat::PreparedStatement::setDouble(const int index, const double value) {
    throwOnError(sqlite3_bind_double(stmt_, index, value),
            "error setting double");
}

void JumpSeat::PreparedStatement::execute() {
    int code = sqlite3_step(stmt_);
    if (code == SQLITE_DONE) {
        reset();
    } else {
        throw DBException(code, "unexpected result while executing statement");
    }
}

JumpSeat::Cursor JumpSeat::PreparedStatement::executeQuery() {
    return Cursor(*this);
}

void JumpSeat::PreparedStatement::throwOnError(const int code, const std::string& message) const {
    if (code != SQLITE_OK) {
        throw DBException(code, message);
    }
}

JumpSeat::Cursor::Cursor(PreparedStatement& preparedStatement) :
preparedStatement_(preparedStatement),
isDone_(false) {
    next();
}

void JumpSeat::Cursor::next() {
    if (!isDone_) {
        int code = sqlite3_step(preparedStatement_.stmt_);
        if (code == SQLITE_DONE) {
            isDone_ = true;
            preparedStatement_.reset();
        } else if (code != SQLITE_ROW) {
            throw DBException(code, "unexpected result while executing query statement");
        }
    }
}

int JumpSeat::Cursor::getInt(const int index) const {
    throwIfDone();
    return sqlite3_column_int(preparedStatement_.stmt_, index);
}

double JumpSeat::Cursor::getDouble(const int index) const {
    throwIfDone();
    return sqlite3_column_double(preparedStatement_.stmt_, index);
}

std::string JumpSeat::Cursor::getText(const int index) const {
    throwIfDone();
    auto text = (const char*) sqlite3_column_text(preparedStatement_.stmt_, index);
    return std::string(text);
}

bool JumpSeat::Cursor::isNull(const int index) const {
    throwIfDone();
    return sqlite3_column_type(preparedStatement_.stmt_, index) == SQLITE_NULL;
}

bool JumpSeat::Cursor::isDone() const {
    return isDone_;
}

void JumpSeat::Cursor::throwIfDone() const {
    if (isDone_) {
        throw CursorException("no more data to read from cursor");
    }
}
