#include "insert.hpp"
#include <iostream>

void insert(sqlite3* db) {
  const char* ptrErr;
  int result, maxValue;

  // Bloco de levantamento
  {
    sqlite3_stmt* stmt;
    const char* sql = "select max(id) from tab";
    result = sqlite3_prepare_v2(db, sql, -1, &stmt, &ptrErr);
    if (result != SQLITE_OK) {
      std::cerr << "sqlite prepare error. Code: " << result
                << "\nPosition: " << *ptrErr << '\n';
      exit(1);
    }
    result = sqlite3_step(stmt);
    if ((result == SQLITE_ROW) || (result == SQLITE_DONE)) {
      maxValue = sqlite3_column_int(stmt, 0);
    } else {
      std::cerr << "Unable to read the table\n";
      exit(1);
    }
    sqlite3_finalize(stmt);
  }

  // Bloco de insercao
  {
    sqlite3_stmt* stmt;
    const char* sql = "insert into tab (id) values(?)";
    result = sqlite3_prepare_v2(db, sql, -1, &stmt, &ptrErr);
    if (result != SQLITE_OK) {
      std::cerr << "sqlite prepare error. Code: " << result
                << "\nPosition: " << *ptrErr << '\n';
      exit(1);
    }
    sqlite3_bind_int(stmt, 1, (maxValue + 1));
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
      std::cerr << "Unable to insert a row\n";
      exit(1);
    }
    sqlite3_finalize(stmt);
  }
}
