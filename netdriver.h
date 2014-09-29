#if !defined ( NETJOY_NETDRIVER_H )
#define NETJOY_NETDRIVER_H

#define WPCAP
#define HAVE_REMOTE

#include <pcap.h>
#include <wx/wx.h>

/* 4 bytes IP address */
typedef struct ip_address{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

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
}ip_header;

/************************** Netdriver **********************************/
class Netdriver {
    public:
        Netdriver();
        bool Init_NIC();
};

#endif