#include <stdio.h>
#include "fifoStaticCircularBuffer.h"
struct FIFOCircularBuffer circularBuffer;
int buffer[100];

int main()
{
	FIFOCircularBuffer_init(&circularBuffer, buffer, sizeof(buffer));
	return (0);
}