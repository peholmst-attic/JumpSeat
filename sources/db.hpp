#ifndef DB_HPP
#define	DB_HPP

#include <sstream>
#include <exception>
#include <string>
#include <sqlite3.h>

namespace JumpSeat {

    class DBException : public std::exception {
    public:
        DBException(const int code, const std::string& message) :
        code_(code), message_(message) {
            std::stringstream stream;
            stream << "sqlite error code: "
                    << code
                    << " ("
                    << sqlite3_errstr(code)
                    << "), message: \""
                    << message
                    << "\"";
            what_ = stream.str();
        }

        const int getCode() const noexcept {
            return code_;
        }

        const std::string getMessage() const noexcept {
            return message_;
        }

        const char* what() const noexcept {
            return what_.c_str();
        }
    private:
        const int code_;
        const std::string message_;
        std::string what_;
    };   

    class PreparedStatement;

    class DB {
        friend class PreparedStatement;
    public:
        DB(const std::string& dbFile);
        ~DB();
        void execute(const std::string& sql);
        static DB& executeAndReturn(DB& db, const std::string& sql);
    private:
        sqlite3* db_;
    };

    class PreparedStatement {
    public:
        PreparedStatement(DB& db, const std::string& sql);
        ~PreparedStatement();
        void reset();
        void setNull(const int index);
        void setText(const int index, const std::string& value);
        void setInt(const int index, const int value);
        void setDouble(const int index, const double value);
        void execute();
    private:
        sqlite3_stmt* stmt_;
        void throwOnError(const int code, const std::string& message);
    };
}

#endif	/* DB_HPP */

