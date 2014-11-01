#include "debug.h"
#include "postgres.h"

/********************************** Postgres **********************************/
Postgres::Postgres() {
    PGconn *pg_connection = PQconnectdb("hostaddr = '127.0.0.1' port = '' dbname = 'postgres' user = 'postgres' password = 'postgres' connect_timeout = '10'");

    if (PQstatus(pg_connection) != CONNECTION_OK) {
        Logger::GetInstance()->Error("Failed to open Postgres connection");
    } else {
        Logger::GetInstance()->Info("Successfully connected to Postgres");    
    }
    // TODO: Do open in separate method that return boolean
}
