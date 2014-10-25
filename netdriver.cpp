#include "debug.h"
#include "netdriver.h"

/***************************** NetDriver ******************************/
NetDriver::NetDriver() {
    //logger = new Logger();
    GetNicList();
}

NetDriver::~NetDriver() {
    FreeNicList();
    //delete logger;
}

char **NetDriver::GetNicNames() {
    if (!nic_list) {
        return NULL;
    }

    nic_names = new char*[10];
    char **nic_names_pointer = nic_names;

	for (pcap_if_t *nic = nic_list; nic; nic = nic->next) {
		if (nic->description) {
            //*nic_names_pointer = nic->description;
            *nic_names_pointer = nic->name;
			Logger::GetInstance()->Debug(nic->description);
		}
		else {
            *nic_names_pointer = nic->name;
			Logger::GetInstance()->Debug("No NIC description available");
		}
        nic_names_pointer++;
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
    delete nic_names;
}

bool NetDriver::NicOpen(char *nic_name) {
    Logger::GetInstance()->Debug("Attempting to open");
    Logger::GetInstance()->Debug(nic_name);
    if ((nic_handle = pcap_open(nic_name, 65536, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, error_buffer)) == NULL) {
        Logger::GetInstance()->Error("Unable to open network adapter");
        return false;
    }

    pcap_setnonblock(nic_handle, 1, error_buffer);

    Logger::GetInstance()->Info("Successfully opened network adapter");
    return true;
}

/*	pcap_t *fp;
    const u_char *pkt_data;
    struct pcap_pkthdr *header;
    int res;

	if ((fp = pcap_open(nics->next->name, 100, PCAP_OPENFLAG_PROMISCUOUS, 20, NULL, error_buffer)) == NULL) {
		wxMessageBox(wxString::Format("Error opening source: %s", error_buffer));
	} else {
		// Read the packets
        int num_packets = 0;
		while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0 && num_packets < 10) {

			if (res == 0)
				// Timeout elapsed
				continue;
            num_packets++;
			// print pkt timestamp and pkt len
			wxMessageBox(wxString::Format("%ld:%ld (%ld)\n", header->ts.tv_sec, header->ts.tv_usec, header->len));

                ip_header *ih = (ip_header *) (pkt_data + 14);

			// Print the packet
			/*for (int i = 1; (i < header->caplen + 1); i++) {
				printf("%.2x ", pkt_data[i - 1]);
				if ((i % 16) == 0) printf("\n");
			}*/

                  /* print ip addresses and udp ports */
    //printf("%d.%d.%d.%d.%d -> %d.%d.%d.%d.%d\n",
    /*wxMessageBox(wxString::Format("%d.%d.%d.%d -> %d.%d.%d.%d\n",
        ih->saddr.byte1,
        ih->saddr.byte2,
        ih->saddr.byte3,
        ih->saddr.byte4,
        //sport,
        ih->daddr.byte1,
        ih->daddr.byte2,
        ih->daddr.byte3,
        ih->daddr.byte4
        //dport
        ));

			printf("\n\n");
		}

		if (res == -1) {
			wxMessageBox(wxString::Format("Error reading the packets: %s\n", pcap_geterr(fp)));
		}
	}*/


void NetDriver::ToggleCapture(char *nic_name) {
    Logger::GetInstance()->Info("Toggling capture");
    //logger->Info(nic_name);
    NicOpen(nic_name);
    //pcap_loop(nic_handle, 0, Packet_Handler, NULL);
    //Get_Packets();
}

void NetDriver::GetPackets() {
    Logger::GetInstance()->Debug("Getting packets");
    pcap_dispatch(nic_handle, -1, PacketHandler, NULL);
    Logger::GetInstance()->Debug("Got packets");
}

void NetDriver::PacketHandler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    Logger::GetInstance()->Debug("PACKET!");
}


