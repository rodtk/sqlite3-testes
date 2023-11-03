#include <sqlite3.h>
#include <iostream>
#include "src/insert.hpp"
#include "src/list.hpp"

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

  // Funcao de insercao
  insert(db);

  // Funcao de listagem
  list(db);
  // Fechamento do banco
  sqlite3_close(db);

  return 0;
}
