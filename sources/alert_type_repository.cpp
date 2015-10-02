#include "alert_type_repository.hpp"

JumpSeat::AlertTypeRepository::AlertTypeRepository(DB& db) :
db_(DB::executeAndReturn(db, "CREATE TABLE IF NOT EXISTS alerttypes (code TEXT PRIMARY KEY, description TEXT);")),
findByCodeStmt_(db, "SELECT code, description FROM alerttypes WHERE code = ?1;") {
}

boost::optional<JumpSeat::AlertType> JumpSeat::AlertTypeRepository::findByCode(const std::string& code) {
    findByCodeStmt_.setText(1, code);
    Cursor cursor = findByCodeStmt_.executeQuery();
    if (cursor.isDone()) {
        return boost::none;
    } else {
        AlertType at = AlertType{cursor.getText(0), cursor.getText(1)};
        findByCodeStmt_.reset();
        return at;
    }
}
