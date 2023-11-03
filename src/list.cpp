#include "list.hpp"
#include <iostream>

void list(sqlite3* db) {
  int result;
  sqlite3_stmt* stmt;
  const char* sql = "select * from tab";
  const char* ptrErr;

  result = sqlite3_prepare_v2(db, sql, -1, &stmt, &ptrErr);
  if (result != SQLITE_OK) {
    std::cerr << "Unable to prepare a query:\n" << sql << '\n';
    std::cerr << "Code: " << result << '\n';
    exit(2);
  }
  result = sqlite3_step(stmt);
  while (result == SQLITE_ROW) {
    std::cout << sqlite3_column_int(stmt, 0) << '\n';
    result = sqlite3_step(stmt);
  }
  sqlite3_finalize(stmt);
}
