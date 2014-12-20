#include "debug.h"
#include "postgres.h"

Postgres *Postgres::postgres_instance = NULL;

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
    PGresult *pg_result = PQexec(pg_connection, "CREATE TABLE if not exists netjoy_test(id SERIAL NOT NULL, timestamp INT NOT NULL, packet_length INT NOT NULL," 
                                                    "ethertype INT NOT NULL, source_ip INET, destination_ip INET, source_port INT, destination_port INT, PRIMARY KEY(id))");
    if (PQresultStatus(pg_result) != PGRES_COMMAND_OK) {
        Logger::GetInstance()->Error("CREATE TABLE failed: " + string(PQerrorMessage(pg_connection)));
        PQclear(pg_result);
        return false;
    }
    PQclear(pg_result);

    PQexec(pg_connection, "CREATE INDEX ON netjoy_test(timestamp)");

    Logger::GetInstance()->Info("CREATE TABLE succeeded");
    return true;
}

Postgres *Postgres::GetInstance() {
    if (!postgres_instance) {
        postgres_instance = new Postgres();
    }
    return postgres_instance;
}

void Postgres::Release() {
    if (postgres_instance) {
        delete postgres_instance;
    }
}

void Postgres::SavePacketData(long time_sec, long time_usec, unsigned int length, unsigned short ethertype, string source_ip, string destination_ip, unsigned short source_port, unsigned short destination_port) {
    //Logger::GetInstance()->Debug("Save packet called");
    string insert_query = "INSERT INTO netjoy_test (timestamp, packet_length, ethertype, source_ip, destination_ip, source_port, destination_port)"
                            "VALUES (" + to_string(time_sec) + "," + to_string(ethertype) + "," + to_string(length)
                                       + ",'" + source_ip + "','" + destination_ip + "'," + to_string(source_port) + "," + to_string(destination_port) + ")";
    PGresult *pg_result = PQexec(pg_connection, insert_query.c_str());

    if (PQresultStatus(pg_result) != PGRES_COMMAND_OK) {
        Logger::GetInstance()->Error("INSERT packet failed: " + string(PQerrorMessage(pg_connection)));
    }

    PQclear(pg_result);
    PQexec(pg_connection, "COMMIT");
}

Postgres::~Postgres() {
    PQfinish(pg_connection);
}