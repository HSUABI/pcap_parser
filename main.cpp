#include <pcap.h>
#include <stdio.h>
#include "protocol_structure.h"
#include "printarr.h"

void usage() {
  printf("syntax: pcap_test <interface>\n");
  printf("sample: pcap_test wlan0\n");
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    usage();
    return -1;
  }

  struct sniff_ethernet *ethernet;
  struct sniff_ip *ip;
  struct sniff_tcp *tcp;

  char* dev = argv[1];
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
  if (handle == NULL) {
    fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
    return -1;
  }

  while (true) {
    struct pcap_pkthdr* header;
    const u_char* packet;
    int res = pcap_next_ex(handle, &header, &packet);
    ethernet = (struct sniff_ethernet*)packet;
    if (res == 0) continue;
    if (res == -1 || res == -2) break;
    printf("packet is : %x %x %x %x %x\n", ethernet->ether_dhost[0],ethernet->ether_dhost[1], ethernet->ether_dhost[2],ethernet->ether_dhost[3],ethernet->ether_dhost[4]);
  }

  pcap_close(handle);
  return 0;
}
