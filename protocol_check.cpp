#include "protocol_check.h"

int ip_check(unsigned short type)
{
	return type==8 ? 1: 0 ;
}

int tcp_check(unsigned char protocol)
{
	return protocol==6 ? 1: 0;
}
