#include <iostream>
#include <string>

std::string shift(const std::string& ciphertext, int key) {
	std::string decrypted_text;
	char decrypted_char;
	for ( char c : ciphertext ) {
		decrypted_char = ( c - 'A' - key + 26 ) % 26 + 'A';
		decrypted_text += decrypted_char;
	}
	return decrypted_text;
}
