#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesar_encrypt(const char *plaintext, int shift, char *result) {
    int i = 0;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isupper(plaintext[i])) {
            result[i] = (char)((plaintext[i] - 65 + shift) % 26 + 65);
        } else if (islower(plaintext[i])) {
            result[i] = (char)((plaintext[i] - 97 + shift) % 26 + 97);
        } else {
            result[i] = plaintext[i];
        }
    }
    result[i] = '\0';
}

void caesar_decrypt(const char *ciphertext, int shift, char *result) {
    caesar_encrypt(ciphertext, 26 - shift, result);
}

int main() {
    const char *text = "Hello World";
    int key = 3;
    
    char encrypted[100];
    char decrypted[100];
    
    caesar_encrypt(text, key, encrypted);
    caesar_decrypt(encrypted, key, decrypted);
    
    printf("Original: %s\n", text);
    printf("Encrypted (shift=%d): %s\n", key, encrypted);
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}
