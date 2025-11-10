#include <iostream>
#include <stdio.h>

int i_o_c(std::string file_content)
{
	int file_size = file_content.size();
	int letter_freq[26] = { 0 };
	int temp;
	for ( int i = 0; i < file_size; i++ ) {
		temp = file_content[i] - 65;
		letter_freq[temp] += 1;
	}

	char letter;
	float index_of_coincidence = 0;
	int largest_frequency = 0;
	for ( int i = 0; i < 26; i++ ) {
		letter = i + 65;
		if ( letter_freq[i] > letter_freq[largest_frequency] ) {
			largest_frequency = i;
		}
		index_of_coincidence += letter_freq[i] * ( letter_freq[i] - 1 );
	}

return largest_frequency;

}
