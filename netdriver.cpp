#include "debug.h"
#include "netdriver.h"

/********************************** NetDriver **********************************/
NetDriver::NetDriver() {
    GetNicList();
}

NetDriver::~NetDriver() {
    FreeNicList();

    Postgres::GetInstance()->Release();
}

vector<string> NetDriver::GetNicNames() {
    vector<string> nic_names;

    if (!nic_list) {
        return nic_names;
    }

	for (pcap_if_t *nic = nic_list; nic; nic = nic->next) {
		if (nic->description) {
            nic_names.push_back(nic->description);
			Logger::GetInstance()->Debug(nic->description);
		} else {
            nic_names.push_back(nic->name);
			Logger::GetInstance()->Debug("No NIC description available.");
		}
	}

    return nic_names;
}

void NetDriver::GetNicList() {
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &nic_list, error_buffer) == -1) {
		Logger::GetInstance()->Error("Failed to retrieve network card list!");
        pcap_freealldevs(nic_list);
    }
}

void NetDriver::FreeNicList() {
    pcap_freealldevs(nic_list);
}

bool NetDriver::OpenNic(int nic_number) {
    Postgres::GetInstance()->CreateTable();

    pcap_if_t *nic = nic_list;
    for (int i = 0; i < nic_number; i++) {
        nic = nic->next;
    }

    Logger::GetInstance()->Debug("Attempting to open " + string(nic->name));
    if ((nic_handle = pcap_open(nic->name, 65536, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, error_buffer)) == NULL) {
        Logger::GetInstance()->Error("Unable to open network adapter!");
        return false;
    }
    pcap_setnonblock(nic_handle, 1, error_buffer);

    Logger::GetInstance()->Info("Successfully opened network adapter.");
    return true;
}

void NetDriver::CloseNic() {
    pcap_close(nic_handle);
    Logger::GetInstance()->Info("Closed network adapter.");
}

void NetDriver::GetPackets() {
    //Logger::GetInstance()->Debug("Getting packets via pcap_dispatch");
    pcap_dispatch(nic_handle, -1, PacketHandler, NULL);
    //Logger::GetInstance()->Debug("Returned from pcap_dispatch");
}

void NetDriver::PacketHandler(unsigned char *param, const struct pcap_pkthdr *header, const unsigned char *pkt_data) {
    unsigned short ethertype = *(pkt_data + 12) << 8 | *(pkt_data + 13);
    unsigned int source_ip = 0;
    unsigned int destination_ip = 0;

    stringstream hexstream;
    hexstream << setw(4) << setfill('0') << hex << int(ethertype);
    Logger::GetInstance()->Info("Ethertype or 802.3 length: 0x" + hexstream.str());

    Logger::GetInstance()->Info("Packet length: " + to_string(header->len));
    Logger::GetInstance()->Info("Packet timestamp: " + to_string(header->ts.tv_sec) + "." + to_string(header->ts.tv_usec));

    if (ethertype == 0x0800) {
        source_ip = *(pkt_data + 26) << 24 | *(pkt_data + 27) << 16 | *(pkt_data + 28) << 8 | *(pkt_data + 29);
        destination_ip = *(pkt_data + 30) << 24 | *(pkt_data + 31) << 16 | *(pkt_data + 32) << 8 | *(pkt_data + 33);

        Logger::GetInstance()->Info("Source IP: " + to_string(source_ip));
        Logger::GetInstance()->Info("Destination IP: " + to_string(destination_ip));
    }

    // packet length doesn't count 8 byte preamble, 4 byte CRC, 12 byte interpacket gap

    // TODO: capture timestamp
    // TODO: For IP packets, capture IP addresses (including vlan packets)
    // TODO: For TCP/UDP packets capture port numbers

    Logger::GetInstance()->Info("");
    Postgres::GetInstance()->SavePacketData(header->ts.tv_sec, header->ts.tv_usec, header->len, ethertype, source_ip, destination_ip);
}


