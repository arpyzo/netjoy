#include "debug.h"
#include "postgres.h"

/***************************** Postgres ******************************/
Postgres::Postgres() {
    PGconn *pg_connection = PQconnectdb("hostaddr = '127.0.0.1' port = '' dbname = 'postgres' user = 'postgres' password = 'postgres' connect_timeout = '10'");

    if (PQstatus(pg_connection) != CONNECTION_OK) {
        Logger::GetInstance()->Test("!!!Postgres connection fail!!!");
    } else {
        Logger::GetInstance()->Test("!!!Postgres connection success!!!");    
    }
}
