#include "protocol_check.h"

int ip_check(unsigned short type)
{
	return type==8 ? 1: 0 ;
}