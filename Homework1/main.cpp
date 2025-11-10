#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <cctype>
#include <map>
#include <vector>

#include "shift.cpp"
#include "vigenere.cpp"
#include "index_of_coincidence.cpp"

int main(int argc, char** argv)
{
	//delete this
	std::string file_name = argv[1];

	//ensure input includes text file
	if ( argc != 2 ) {
		std::cout << "Invalid Input" << std::endl;
		return 1;
	}

	//ensure file opens properly
	std::ifstream file(argv[1]);
	if ( !file.is_open() ) {
		std::cout << "Error" << std::endl;
		return 1;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string file_content = buffer.str();
	int file_size = file_content.size();

	//calculate letter frequency
	int letter_freq[26] = { 0 };
	int temp;
	for ( int i = 0; i < file_size; i++ ) {
		temp = file_content[i] - 65;
		letter_freq[temp] += 1;
	}
	
	//print letter frequency
	//& calculate index of coincidence (IC)
	char letter;
	float index_of_coincidence = 0;
	std::cout << "\nLetter Frequency of Ciphertext:" << std::endl;
	int largest_frequency = 0;
	for ( int i = 0; i < 26; i++ ) {
		letter = i + 65;
		std::cout << letter << ": " << letter_freq[i] << std::endl;
		if ( letter_freq[i] > letter_freq[largest_frequency] ) {
			largest_frequency = i;
		}
		index_of_coincidence += letter_freq[i] * ( letter_freq[i] - 1 );
	}
	index_of_coincidence /= file_size * ( file_size - 1 );
	std::cout << "\nIndex of Coincidence (IC): " << index_of_coincidence << std::endl;
	
	std::string plain_text;
	//if shift cipher
	if( index_of_coincidence > 0.05 ) {
		while ( true ) {
			std::cout << "\nThis is a Shift Cipher\n" << std::endl;
			std::cout << "Enter Key: (Enter 0 If No Key)" << std::endl;
			int key = 0;
			std::cin >> key;
			if ( key == 0 ) {
				key = (largest_frequency - 4) % 26;
			}
			std::cout << "Key = " << key << std::endl;
			plain_text = shift(file_content, key);
			std::cout << "\nPlaintext: " << std::endl;
			for ( int i = 0; i < file_size; i++ ) {
				std::cout << plain_text[i];
			}
			std::cout << std::endl;

			std::cout << "\nType Y to Try Another Key\n" << std::endl;
			std::string input;
			std::cin >> input;
			if ( input != "Y" && input != "y" ) {
				break;
			}
		}
	} else if ( index_of_coincidence > 0.04 ) {
		while ( true ) {
			std::cout << "\nBased on the Index of Coincidence,\nThis is a Vigenere Cipher\n" << std::endl;
			
			std::cout << "Enter Key: (Enter 0 If No Key)" << std::endl;	
			std::string key = "";
			std::cin >> key;
			int key_length = 0;
			if ( key == "0" ) {
				if ( index_of_coincidence < 0.044 )  {
					if ( index_of_coincidence >= 0.043 ) {
						key_length = 9;
					} else if ( index_of_coincidence >= 0.042 ) {
						key_length = 7;
					} else if ( index_of_coincidence >= 0.041 ) {
						key_length = 1;
					} else if ( index_of_coincidence >= 0.0395 ) {
						key_length = 5;
					} else {
						key_length = 10;
					}
				} else if ( index_of_coincidence < 0.045 ) {
					key_length = 3;
				} else if ( index_of_coincidence < 0.047 ) {
					key_length = 2;
				} else if ( index_of_coincidence < 0.049 ) {
					key_length = 6;
				} else if ( index_of_coincidence < 0.055 ) {
					key_length = 4;
				} else {
					key_length = 8;
				}
				
				std::cout << "\nBased on IC,\nKey Length = " << key_length << std::endl;
				
				std::cout << "\nDivide the Ciphertext into Columns based on Key Length:" << std::endl;
				
				//Calculate Letter Frequency of each Column
				
				std::string first_column = "";
				std::string second_column = "";
				std::string third_column = "";
				std::string fourth_column = "";
				std::string fifth_column = "";
				std::string sixth_column = "";
				std::string seventh_column = "";

				for ( int i = 0; i < file_size; i++ ) {
					if ( i % 7 == 0 ) {
						first_column += file_content[i];
					} else if ( i % 7 == 1 ) {
						second_column += file_content[i];
					} else if ( i % 7 == 2 ) {
						third_column += file_content[i];
					} else if ( i % 7 == 3 ) {
						fourth_column += file_content[i];
					} else if ( i % 7 == 4 ) { 
						fifth_column += file_content[i];
					} else if ( i % 7 == 5 ) {
						sixth_column += file_content[i];
					} else if ( i % 7 == 6 ) {
						seventh_column += file_content[i];
					}
				}
				
				int largest = i_o_c(first_column);
				int k = (largest - 4) % 26;
				std::cout << "Column 1 Key: " << k << std::endl;
				char character_one = static_cast<char>(k + 65);
				largest = i_o_c(second_column);
				k = (largest - 4) % 26;
				std::cout << "Column 2 Key: " << k << std::endl;
				char character_two = static_cast<char>(k + 65);
				largest = i_o_c(third_column);
				k = (largest - 4) % 26;
				std::cout << "Column 3 Key: " << k << std::endl;
				char character_three = static_cast<char>(k + 65);
				largest = i_o_c(fourth_column);
				k = (largest - 4) % 26;
				std::cout << "Column 4 Key: " << k << std::endl;
				char character_four = static_cast<char>(k + 65);
				largest = i_o_c(fifth_column);
				k = (largest - 4) % 26;
				std::cout << "Column 5 Key: " << k << std::endl;
				char character_five = static_cast<char>(k + 65);
				largest = i_o_c(sixth_column);
				k = (largest - 4) % 26;
				std::cout << "Column 6 Key: " << k << std::endl;
				char character_six = static_cast<char>(k + 65);
				largest = i_o_c(seventh_column);
				k = (largest - 4) % 26;
				std::cout << "Column 7 Key: " << k << std::endl;
				char character_seven = static_cast<char>(k + 65);
				
				std::cout << "\nTherefore, the Key is:" << std::endl;
				std::cout << character_one << character_two << character_three << character_four << character_five << character_six << character_seven << std::endl;
				key = character_one;
				key += character_two;
				key += character_three;
				key += character_four;
				key += character_five;
				key += character_six;
				key += character_seven;
			}
			
			for ( char& c : key ) {
				c = static_cast<char>(std::toupper(c));
			}

			plain_text = vigenere(file_content, key);
	
			std::cout << "\nPlaintext: " << std::endl;
			for ( int i = 0; i < file_size; i++ ) {
				std::cout << plain_text[i];
			}
			std::cout << std::endl;

			std::cout << "\nType Y to Try Another Key\n" << std::endl;
			std::string input;
			std::cin >> input;
			if ( input != "Y" && input != "y" ) {
				break;
			}
		}
	} else {
		std::cout << "Unable to Crack Cipher\nIndex of Coincidence Indicates that Ciphertext is Random" << std::endl;
	}

	return 1;

}
