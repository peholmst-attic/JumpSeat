#include <iostream>

#include "db.hpp"

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

void JumpSeat::PreparedStatement::throwOnError(const int code, const std::string& message) {
    if (code != SQLITE_OK) {
        throw DBException(code, message);
    }
}