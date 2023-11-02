#include <sqlite3.h>
#include <iostream>

using namespace std;
int main() {
  int rc;
  sqlite3* db;

  // Abertura do banco
  if ((rc = sqlite3_open("teste.db", &db))) {
    cerr << "Database opening error: Error code: " << rc << '\n';
    exit(-1);
  }

  // Criacao da tabela caso nao exista
  {
    const char* sql = "create table if not exists tab (id integer)";
    char* msg;
    if ((rc = sqlite3_exec(db, sql, NULL, NULL, &msg))) {
      cerr << "SQLITE prepare error: Code: " << rc << '\n';
      sqlite3_free(msg);
      exit(-1);
    }
  }

  // Teste do prepare_stmt
  {
    sqlite3_stmt* stmt;
    const char* ptz;

    // Teste de consulta ao banco
    {
      if ((rc = sqlite3_prepare_v2(db, "select max(id) from tab", -1, &stmt,
                                   NULL))) {
        cerr << "Prepared statement error: Code: " << rc << '\n';
        cerr << "Stopped at: " << ptz << '\n';
        sqlite3_close(db);
        exit(1);
      }
      rc = sqlite3_step(stmt);
      if ((rc != SQLITE_ROW) && (rc != SQLITE_DONE)) {
        cerr << "Step on statement error: Code: " << rc << '\n';
        sqlite3_close(db);
        exit(2);
      }
    }
    int maxValue = sqlite3_column_int(stmt, 0);

    // Teste de insercao ao banco
    {
      sqlite3_reset(stmt);
      const char* sql = "insert into tab (id) values (?)";
      rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &ptz);
      if (rc) {
        cerr << "Prepared statement error: Code: " << rc << '\n';
        cerr << "Stopped at: " << ptz << '\n';
        sqlite3_close(db);
        exit(3);
      }
      sqlite3_bind_int(stmt, 1, maxValue + 1);
      rc = sqlite3_step(stmt);
      if ((rc != SQLITE_ROW) && (rc != SQLITE_DONE)) {
        cerr << "Step on statement error: Code: " << rc << '\n';
        sqlite3_close(db);
        exit(4);
      }
    }

    // Teste visualizando a tabela
    {
      const char* sql = "select * from tab";
      sqlite3_reset(stmt);
      rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &ptz);
      if (rc) {
        cerr << "Prepared statement error: Code: " << rc << '\n';
        cerr << "Stopped at: " << ptz << '\n';
        sqlite3_close(db);
        exit(5);
      }
      rc = sqlite3_step(stmt);
      while ((rc == SQLITE_ROW) && (rc != SQLITE_DONE)) {
        cout << sqlite3_column_int(stmt, 0) << '\n';
        rc = sqlite3_step(stmt);
      }
    }
    sqlite3_finalize(stmt);
  }
  // Fechamento do banco
  sqlite3_close(db);

  return 0;
}
