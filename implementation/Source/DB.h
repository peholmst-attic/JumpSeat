#ifndef DB_H
#define	DB_H

#include <sstream>
#include <exception>
#include <string>
#include <sqlite3.h>

namespace JumpSeat {

    /**
     * Exception thrown when a SQLite error occurs.
     * @param code the SQLite error code.
     * @param message a message explaining what was happening when the error occurred.
     */
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

    /**
     * Exception thrown by a Cursor when an error occurs.
     * @param message a message explaining what went wrong.
     */
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

    /**
     * A simple C++ wrapper for SQLite.
     * @param dbFile the filename of the database file.
     */
    class DB {
        friend class PreparedStatement;
    public:
        DB(const std::string& dbFile);
        ~DB();
        /**
         * Executes the given SQL string.
         * @param sql the SQL to execute.
         */
        void execute(const std::string& sql);
        /**
         * Executes the given SQL on the given DB instance and returns the DB instance.
         * @param db the DB instance.
         * @param sql the SQL to execute.
         * @return the DB instance.
         */
        static DB& executeAndReturn(DB& db, const std::string& sql);
    private:
        sqlite3* db_;
    };

    class Cursor;

    /**
     * A simple C++ wrapper for a SQLite statement.
     * @param db the DB instance.
     * @param sql the SQL to prepare.
     */
    class PreparedStatement {
        friend class Cursor;
    public:
        PreparedStatement(DB& db, const std::string& sql);
        ~PreparedStatement();
        /**
         * Resets the statement, making it possible to execute it again.
         */
        void reset();
        /**
         * Sets the given parameter to null.
         * @param index the index of the parameter. The first parameter has index 1.
         */
        void setNull(const int index);
        /**
         * Sets the given parameter to the given string value.
         * @param index the index of the parameter. The first parameter has index 1.
         * @param value the value to set.
         */
        void setText(const int index, const std::string& value);
        /**
         * Sets the given parameter to the given integer value.
         * @param index the index of the parameter. The first parameter has index 1.
         * @param value the value to set.
         */
        void setInt(const int index, const int value);
        /**
         * Sets the given parameter to the given double value.
         * @param index the index of the parameter. The first parameter has index 1.
         * @param value the value to set.
         */
        void setDouble(const int index, const double value);
        /**
         * Executes the query without expecting any results. This method should be used
         * for inserts, updates and deletes. The statement is automatically reset after
         * a successful execution.
         */
        void execute();
        /**
         * Executes the query and returns a cursor containing the result. This method
         * should be used for selects.
         * @return a cursor.
         */
        Cursor executeQuery();
    private:
        sqlite3_stmt* stmt_;
        void throwOnError(const int code, const std::string& message) const;
    };

    /**
     * A simple C++ wrapper for navigating the result of a SQLite query.
     * @param preparedStatement the statement that contains the result.
     */
    class Cursor {
    public:
        Cursor(PreparedStatement& preparedStatement);
        /**
         * Checks if the specified column has a null value in the current row.
         * If the cursor is done, a CursorException is thrown.
         * @param index the index of the column. The first column has index 0.
         * @return true if the value is null, false otherwise.
         */
        bool isNull(const int index) const;
        /**
         * Gets the text value of the specified column in the current row.
         * If the cursor is done, a CursorException is thrown.
         * @param index the index of the column. The first column has index 0.
         * @return a string containing the value.
         */
        std::string getText(const int index) const;
        /**
         * Gets the integer value of the specified column in the current row.
         * If the cursor is done, a CursorException is thrown.
         * @param index the index of the column. The first column has index 0.
         * @return an integer containing the value.
         */
        int getInt(const int index) const;
        /**
         * Gets the double value of the specified column in the current row.
         * If the cursor is done, a CursorException is thrown.
         * @param index the index of the column. The first column has index 0.
         * @return a double containing the value.
         */
        double getDouble(const int index) const;
        /**
         * Checks if this cursor is done (i.e. there are no more rows to fetch).
         * @return true if this cursor is done, false if there are more rows.
         */
        bool isDone() const;
        /**
         * Navigates to the next row in the result set. If there are no more rows
         * the prepared statement is reset. After this happens, this method will not do anything.
         */
        void next();
    private:
        PreparedStatement& preparedStatement_;
        bool isDone_;
        void throwIfDone() const;
    };
}

#endif	/* DB_H */

