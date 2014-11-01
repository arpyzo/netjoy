#include "debug.h"
#include "netdriver.h"

/********************************** NetDriver **********************************/
NetDriver::NetDriver() {
    GetNicList();
}

NetDriver::~NetDriver() {
    FreeNicList();
}

//char **NetDriver::GetNicNames() {
vector<string> NetDriver::GetNicNames() {
    vector<string> nic_names;

    if (!nic_list) {
        return nic_names;
    }

    //nic_names = new char*[10];
    //char **nic_names_pointer = nic_names;

	for (pcap_if_t *nic = nic_list; nic; nic = nic->next) {
		if (nic->description) {
            nic_names.push_back(nic->description);
            //*nic_names_pointer = nic->description;
            //*nic_names_pointer = nic->name;
			Logger::GetInstance()->Debug(nic->description);
		} /*else {
            *nic_names_pointer = nic->name;
			Logger::GetInstance()->Debug("No NIC description available");
		}
        nic_names_pointer++;*/
	}

    return nic_names;
}

void NetDriver::GetNicList() {
    //char error_buffer[PCAP_ERRBUF_SIZE];

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &nic_list, error_buffer) == -1) {
		Logger::GetInstance()->Error("Failed to retrieve network card list!");
        pcap_freealldevs(nic_list);
    }
}

void NetDriver::FreeNicList() {
    pcap_freealldevs(nic_list);
    //delete nic_names;
}

bool NetDriver::OpenNic(int nic_number) {
    pcap_if_t *nic = nic_list;
    for (int i = 0; i < nic_number; i++) {
        nic = nic->next;
    }

    Logger::GetInstance()->Debug("Attempting to open " + string(nic->name));
    if ((nic_handle = pcap_open(nic->name, 65536, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, error_buffer)) == NULL) {
        Logger::GetInstance()->Error("Unable to open network adapter");
        return false;
    }
    pcap_setnonblock(nic_handle, 1, error_buffer);

    Logger::GetInstance()->Info("Successfully opened network adapter");
    return true;
}

void NetDriver::GetPackets() {
    //Logger::GetInstance()->Debug("Getting packets via pcap_dispatch");
    pcap_dispatch(nic_handle, -1, PacketHandler, NULL);
    //Logger::GetInstance()->Debug("Returned from pcap_dispatch");
}

void NetDriver::PacketHandler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    u_char *ethertype_high = (u_char *) (pkt_data + 12);
    u_char *ethertype_low = (u_char *) (pkt_data + 13);

    stringstream hexstream;
    hexstream << setw(2) << setfill('0') << hex << int(*ethertype_high);
    hexstream << setw(2) << setfill('0') << hex << int(*ethertype_low);
    Logger::GetInstance()->Info("Ethertype or 802.3 length: 0x" + hexstream.str());
    Logger::GetInstance()->Info("Packet length: " + to_string(header->len));

    // packet length doesn't count 8 byte preamble, 4 byte CRC, 12 byte interpacket gap

    // TODO: capture timestamp
    // TODO: For IP packets, capture IP addresses
    // TODO: For TCP/UDP packets capture port numbers
}


