#include <stdio.h>
#include "fifoStaticCircularBuffer.h"
FIFOBuffer circularBuffer;
int buffer[100];

int main()
{
	FIFOBuffer_init(&circularBuffer, buffer, sizeof(int),git  sizeof(buffer));
	return (0);
}