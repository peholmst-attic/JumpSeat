#ifndef DB_HPP
#define	DB_HPP

#include <exception>
#include <string>
#include <sqlite3.h>

namespace JumpSeat
{
    class DBException: public std::exception
    {
    public:
        DBException(const int code, const std::string& message) :
            code_(code), message_(message)
        {}
        const int code_;
        const std::string message_;
        const char* what() const noexcept { return message_.c_str(); }
    };
    
    class DB
    {
    public:
        DB(const std::string& dbFile);
        ~DB();
        void execute(const std::string& sql);        
    private:
        sqlite3* db_;
    };
}

#endif	/* DB_HPP */

