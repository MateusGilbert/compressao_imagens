/* BIT OUTPUT ROUTINES */

#include <stdio.h>
#include "arithmetic_coding.h"
#include "missing_header.h"

/* THE BIT BUFFER */

static int buffer;		    /* Bits buffered for output 		*/
static int bits_to_go;		/* Number of bits still in buffer	*/
static int Bits_Count;

/* INITIALISE BIT OUTPUT */
void
start_outputing_bits(void)
{ 
 buffer = 0;		   /* Bits buffered for ouput		*/
 bits_to_go = 8;	   /* Number of bits free in buffer	*/
 Bits_Count = 0;
}


/* OUTPUT A BIT  */
void
output_bit(int bit)
/*int bit;*/
{ 
 buffer >>= 1;				/* Put bit in top of buffer	*/
 if (bit) buffer |= 0x80;
 bits_to_go -= 1;
 Bits_Count += 1;
 if (bits_to_go == 0) 		/* Output buffer if it is	*/
	{						/* now full					*/
     putc(buffer,stdout);	
     bits_to_go = 8;
    }
}


/* FLUSH OUT THE LAST BITS */
void
done_outputing_bits(void)
{ 
 putc(buffer>>bits_to_go,stdout);
 fprintf(stderr,"Total Bits count : %d \n",Bits_Count);
}

