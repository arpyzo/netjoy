#if !defined ( NETJOY_NETDRIVER_H )
#define NETJOY_NETDRIVER_H

#define WPCAP
#define HAVE_REMOTE

#include <pcap.h>
#include <iphlpapi.h>
#include <winerror.h>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "postgres.h"
#include "logger.h"

/* 4 bytes IP address */
typedef struct ip_address{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
} ip_address;

/* IPv4 header */
typedef struct ip_header{
    u_char  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
    u_char  tos;            // Type of service 
    u_short tlen;           // Total length 
    u_short identification; // Identification
    u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
    u_char  ttl;            // Time to live
    u_char  proto;          // Protocol
    u_short crc;            // Header checksum
    ip_address  saddr;      // Source address
    ip_address  daddr;      // Destination address
    u_int   op_pad;         // Option + Padding
} ip_header;

/********************************** Netdriver **********************************/
class NetDriver {
    public:
        NetDriver();
        ~NetDriver();

        static void ConnectToDB();
        vector<string> GetNicNames();
        bool OpenNic(int nic_number);
        void CloseNic();
        void GetPackets();

        static void PacketHandler(unsigned char *param, const struct pcap_pkthdr *header, const unsigned char *pkt_data);

    private:
        void GetNicList();
        void FreeNicList();

        pcap_if_t *nic_list;
        pcap_t *nic_handle;

        char error_buffer[PCAP_ERRBUF_SIZE];
};

#endif