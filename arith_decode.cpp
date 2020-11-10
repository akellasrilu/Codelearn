#include "arith_decode.h"

/* MAIN PROGPAM FOR DECODING. */
#include <stdio.h> 
#include "adaptiveModel.h" 

void arith_decode::decode()
{
	start_model();					/* Set up other modules. */
	start_inputing_bits();
	start_decoding();
	for (;;) {						/* Loop through characters. */
		int ch;
		int symbol;
		symbol = decode_symbol(cum_freq);	/* Decode next symbol. */
		if (symbol == EOF_symbol)		/* Exit loop if EOF symbol. */
			break;
		ch = index_to_char[symbol];		/* Translate to a character.*/
		putc(ch, stdout);				/* Write that character. */
		update_model(symbo1);			/* Update the model */
	}
	exit(0);
}


/* ARITHMETIC DECODING ALGORITHM. */ 
#include “arithmetic_coding.h” 
/* CURRENT STATE OF THE DECODING. */ 
static code_value value;	/* Currently-seen code value*/
static code_value low, high; /* Ends of current code region */

/* START DECODING A STREAM OF SYMBOLS. */ 
start_decoding() {
	int i;
	value = 0;
	for (i = 1; i <= Code_value_bits; i++) {
		value = 2 * value + input_bit();
	}
	low = 0;
	high = Top_value;
}

/* Input bits to flll the l / /* code value. l / 
/* Full code ranpe. l / 

/* DECODE THE NEXT SYMBOL. */ 
int decode_symbol (int cum_freq) {	/* Cumulative symbol frequencies */
	long range; /* Size of current code region */
	int cum;	/* Cumulative frequency calculated */
	int symbol; /* Symbol decoded */
	range = (long)(high-low)+l;
	cum = (((long)(value - low) + l) * cum_freq(0) - 1) / range;	/* Find cum freq for value. */
	for (symbol = 1; cum_freq(symbol)>cum; symbol++) ; /* Then find symbol. */
	high = low + (range * cum_freq[symbol - l]) / cum_freq(0) - 1;	/* Narrow the code region to that allotted to this symbol */
	low = low + (range *cum_freq(symbol))/cum_freq(0);
	for (;;) {						/* Loop to get rid of bits. */  
		if (high < Half) {
			/* nothing */			/* Expand low half. */ 
		}
		else if (low >= Half) {		/* Expand high half. */
			value -= Half;
			low -= Half;			/* Subtract offset to top. */ 
			high -= Half;
		}
		else if (low >= First_qtr && high < Third_qtr) {	/* Expand middle half. */ 
			value -= First_qtr;
			low -= First_qtr;		/* Subtract offset to middle */ 
			high -= First_qtr;
		}
		else break;					/* Otherwise exit loop. */ 

		low = 2 * low;
		high = 2 * high + 1;		/* Scale up code range. */ 
		value = 2 * value + input_bit();	/* Move in next input blt. */
	}
	return symbol;
}
