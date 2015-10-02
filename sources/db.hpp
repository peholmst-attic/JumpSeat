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

    class CursorException : public std::exception {
    public:

        CursorException(const std::string& message) :
        message_(message) {
        }
        
        const char* what() const noexcept {
            return message_.c_str();
        }
    private:
        const std::string message_;
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

    class Cursor;

    class PreparedStatement {
        friend class Cursor;
    public:
        PreparedStatement(DB& db, const std::string& sql);
        ~PreparedStatement();
        void reset();
        void setNull(const int index);
        void setText(const int index, const std::string& value);
        void setInt(const int index, const int value);
        void setDouble(const int index, const double value);
        void execute();
        Cursor executeQuery();
    private:
        sqlite3_stmt* stmt_;
        void throwOnError(const int code, const std::string& message) const;
    };

    class Cursor {
    public:
        Cursor(PreparedStatement& preparedStatement);
        bool isNull(const int index) const;
        std::string getText(const int index) const;
        int getInt(const int index) const;
        double getDouble(const int index) const;
        bool isDone() const;
        void next();
    private:
        PreparedStatement& preparedStatement_;
        bool isDone_;
        void throwIfDone() const;
    };
}

#endif	/* DB_HPP */

