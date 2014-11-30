#if !defined ( NETJOY_POSTGRES_H )
#define NETJOY_POSTGRES_H

#include <libpq-fe.h>
#include "logger.h"

/********************************** Postgres **********************************/
class Postgres {
    public:
        static Postgres *GetInstance();
        static void Release();

        bool CreateTable();
        void SavePacketData(long time_sec, long time_usec, unsigned int length, unsigned short ethertype, unsigned int source_ip, unsigned int destination_ip, unsigned short source_port, unsigned short destination_port);

    private:
        Postgres();
        ~Postgres();

        static Postgres *postgres_instance;

        PGconn *pg_connection;
};

#endif