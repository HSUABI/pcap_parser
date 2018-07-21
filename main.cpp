#include <pcap.h>
#include <stdio.h>
#include "protocol_structure.h"
#include "printarr.h"
#include "protocol_check.h"
#define ETHER_LEN 14

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
  u_int size_ip;

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
    ip = (struct sniff_ip*)(packet+ETHER_LEN);
    size_ip = IP_HL(ip)*4; 
    
    if (res == 0) continue;
    if (res == -1 || res == -2) break;
    printf("Destination MacAddress\t:");
    printarr(ethernet->ether_dhost,ETHER_ADDR_LEN);
    printf("Source MacAddress\t:");
    printarr(ethernet->ether_shost,ETHER_ADDR_LEN);
    
    if(ip_check(ethernet->ether_type))
    {

      printf("source ip\t:%x\n",ip->ip_src);
      printf("source ip\t:%x\n",ip->ip_dst);

      //if(tcp_check(ip->ip_p)) printf("it is tcp\n");
    }
    

  }

  pcap_close(handle);
  return 0;
}
