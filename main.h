#if !defined ( NETJOY_MAIN_H )
#define NETJOY_MAIN_H

#define WPCAP
#define HAVE_REMOTE

#include <wx/wx.h>
#include <wx/splitter.h>
#include <pcap.h>

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

enum {
    MENU_ABOUT,
    MENU_QUIT
};

/************************** Frame **********************************/
class Frame: public wxFrame {
    public:
        Frame();
        void Setup_Menu();

        void Menu_About(wxCommandEvent &event);
        void Menu_Quit(wxCommandEvent &event);

    DECLARE_EVENT_TABLE()
};

/**************************** App **********************************/
class App: public wxApp {
    public:
        virtual bool OnInit();

    private:
        bool Init_NIC();
};

#endif