#include "debug.h"
#include "postgres.h"

/********************************** Postgres **********************************/
Postgres::Postgres() {
    pg_connection = PQconnectdb("hostaddr = '127.0.0.1' port = '' dbname = 'test' user = 'postgres' password = 'postgres' connect_timeout = '10'");

    if (PQstatus(pg_connection) != CONNECTION_OK) {
        Logger::GetInstance()->Error("Failed to open Postgres connection");
    } else {
        Logger::GetInstance()->Info("Successfully connected to Postgres");    
    }
    // TODO: Do open in separate method that returns boolean result
}

bool Postgres::CreateTable() {
    PGresult *pg_result = PQexec(pg_connection, "CREATE TABLE if not exists netjoy_test(timestamp INT NOT NULL, packet_type INT NOT NULL, packet_length INT NOT NULL, Constraint PK Primary Key(timestamp))");
    if (PQresultStatus(pg_result) != PGRES_COMMAND_OK) {
        Logger::GetInstance()->Error("CREATE TABLE failed: " + string(PQerrorMessage(pg_connection)));
        PQclear(pg_result);
        return false;
    }

    Logger::GetInstance()->Info("CREATE TABLE succeeded");
    PQclear(pg_result);
    return true;
}

Postgres::~Postgres() {
    // TODO: Close connection
}