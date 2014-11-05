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
        void SavePacketData();

    private:
        Postgres();
        ~Postgres();

        static Postgres *postgres_instance;

        PGconn *pg_connection;
};

#endif