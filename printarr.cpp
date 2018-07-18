#include "printarr.h"

int printarr(u_char* arr, int length )
{
	int i;
	for (int i = 0; i < length; ++i)
	{
		printf("%2x ",arr[i]);
	}
	printf("\n");
	return 0;
}