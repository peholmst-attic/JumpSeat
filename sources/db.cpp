#include "db.hpp"

JumpSeat::DB::DB(const std::string& dbFile)
{
    sqlite3_open(dbFile.c_str(), &db_);
}

JumpSeat::DB::~DB()
{
    sqlite3_close(db_);
}

void JumpSeat::DB::execute(const std::string& sql)
{
    char *errMsg = 0;
    int code = sqlite3_exec(db_, sql.c_str(), 0, 0, &errMsg);
    if (code != SQLITE_OK) {
        auto errMsgStr = std::string(errMsg);
        sqlite3_free(errMsg);
        throw DBException(code, errMsgStr);
    }
}