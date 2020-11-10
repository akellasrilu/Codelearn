#include "adaptiveModel.h"

int freq[NoOfSymbols + 1] = {	/* symbol frequencies */
	/* P, N, T, Z*/ 1,1,1,1 };

void adaptiveModel::start_model(void)
{
	int i;
	for (i = 0; i < NoOfChars; i++) {	/* Set up tables that translate between symbol indexes and characters. */
		char_to_index[i] = i + 1;
		index_to_char[i + 1] = i;
	}
	for (i = 0; i < NoOfSymbols; i++) {	/* Set up initial frequency counts to be one for all symbols. */
		freq[i] = 1;
		cum_freq[i] = NoOfSymbols - i;
	}
	freq[0] = 0;						/* Freq[0] must not be the same as freq[1]. */
}

		
		/* UPDATE THE MODEL TO ACCOUNT FOR A NEW SYMBOL. */
void adaptiveModel::update_model(int symbol) /* Index of new symbol */ {
	int i; /* New index for symbol */
	if (cum_freq[0] == Max_frequency) { /* See if frequency counts are at their maximum. */
		int cum;
		cum = 0;
		for (i = No_of_symbols; i >= 0; i--) {	/* If so, half all the counts (keeping them non-zero).*/
			freq[i] - (freq[i] + 1) / 2;
			cum - freq[i] = cum;
			cum += freq[i];
		}
	}
	for (i = symbol; freq[i] == freq[i - 1]; i--); /* Find symbol's new Index. */
	if (i < symbol) {
		int ch_i, ch_symbol;
		ch_i = index_to_char[i]; /* Update the translation tables lf the symbol has moved.*/
		ch_symbol = index_to_char[symbol];
		index_to_char[i] = ch_symbol;
		index_to_char[symbol] = ch_i;
		char_to_index[ch_i] = symbol;
		char_to_index[ch_symbol] = i;
	}
	freq[i] += 1;
	while (i > 0) {		/* Increment the frequency count for the symbol and update the cumulative frequencies. */
		i -= 1;
		cum_freq[i] += 1;
	}
}
