#include <iostream>
#include <string>
#include <cctype>

std::string vigenere(const std::string& ciphertext, const std::string& key) {
    std::string plain_text = "";
    int key_index = 0;

    for (char c : ciphertext) {
            char upper_key_char = key[key_index % key.length()];

            int shift = upper_key_char - 'A';

            char decrypted_char = static_cast<char>(((c - 'A' - shift + 26) % 26) + 'A');

            plain_text += decrypted_char;

            key_index++;
    }
    return plain_text;
}
