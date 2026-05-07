#include <stdio.h>
#include <string.h>
#include <ctype.h>

void create_monoalphabetic_key(const char *key_word, char key_map[]) {
    int seen[26] = {0};
    int key_idx = 0;
    
    for (int i = 0; key_word[i] != '\0'; i++) {
        char c = toupper(key_word[i]);
        if (c >= 'A' && c <= 'Z' && !seen[c - 'A']) {
            seen[c - 'A'] = 1;
            key_map[key_idx++] = c;
        }
    }
    
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!seen[c - 'A']) {
            key_map[key_idx++] = c;
        }
    }
}

void monoalphabetic_encrypt(const char *plaintext, const char *key_word, char *result) {
    char key_map[26];
    create_monoalphabetic_key(key_word, key_map);
    
    int i = 0;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isupper(plaintext[i])) {
            result[i] = key_map[plaintext[i] - 'A'];
        } else if (islower(plaintext[i])) {
            result[i] = tolower(key_map[toupper(plaintext[i]) - 'A']);
        } else {
            result[i] = plaintext[i];
        }
    }
    result[i] = '\0';
}

void monoalphabetic_decrypt(const char *ciphertext, const char *key_word, char *result) {
    char key_map[26];
    create_monoalphabetic_key(key_word, key_map);
    
    int i = 0;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isupper(ciphertext[i])) {
            for (int j = 0; j < 26; j++) {
                if (key_map[j] == ciphertext[i]) {
                    result[i] = 'A' + j;
                    break;
                }
            }
        } else if (islower(ciphertext[i])) {
            for (int j = 0; j < 26; j++) {
                if (key_map[j] == toupper(ciphertext[i])) {
                    result[i] = tolower('A' + j);
                    break;
                }
            }
        } else {
            result[i] = ciphertext[i];
        }
    }
    result[i] = '\0';
}

void vigenere_encrypt(const char *plaintext, const char *keyword, char *result) {
    int key_len = strlen(keyword);
    int key_index = 0;
    
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int shift = toupper(keyword[key_index % key_len]) - 'A';
            if (isupper(plaintext[i])) {
                result[i] = (char)((plaintext[i] - 'A' + shift) % 26 + 'A');
            } else {
                result[i] = (char)((plaintext[i] - 'a' + shift) % 26 + 'a');
            }
            key_index++;
        } else {
            result[i] = plaintext[i];
        }
    }
    result[ strlen(plaintext) ] = '\0';
}

void vigenere_decrypt(const char *ciphertext, const char *keyword, char *result) {
    int key_len = strlen(keyword);
    int key_index = 0;
    
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = toupper(keyword[key_index % key_len]) - 'A';
            if (isupper(ciphertext[i])) {
                result[i] = (char)((ciphertext[i] - 'A' - shift + 26) % 26 + 'A');
            } else {
                result[i] = (char)((ciphertext[i] - 'a' - shift + 26) % 26 + 'a');
            }
            key_index++;
        } else {
            result[i] = ciphertext[i];
        }
    }
    result[ strlen(ciphertext) ] = '\0';
}

int main() {
    const char *text = "Hello World";
    const char *mono_key = "CRYPTO";
    const char *poly_key = "KEY";
    
    char encrypted_mono[100], decrypted_mono[100];
    char encrypted_poly[100], decrypted_poly[100];
    
    printf("=== Monoalphabetic Cipher ===\n");
    monoalphabetic_encrypt(text, mono_key, encrypted_mono);
    monoalphabetic_decrypt(encrypted_mono, mono_key, decrypted_mono);
    printf("Original: %s\n", text);
    printf("Key word: %s\n", mono_key);
    printf("Encrypted: %s\n", encrypted_mono);
    printf("Decrypted: %s\n", decrypted_mono);
    
    printf("\n=== Polyalphabetic Cipher (Vigenère) ===\n");
    vigenere_encrypt(text, poly_key, encrypted_poly);
    vigenere_decrypt(encrypted_poly, poly_key, decrypted_poly);
    printf("Original: %s\n", text);
    printf("Keyword: %s\n", poly_key);
    printf("Encrypted: %s\n", encrypted_poly);
    printf("Decrypted: %s\n", decrypted_poly);
    
    return 0;
}
