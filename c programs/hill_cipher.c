#include <stdio.h>
#include <string.h>
#include <ctype.h>

void create_key_matrix(const char *key, int size, int matrix[][2]) {
    char key_buf[100];
    int k_idx = 0;
    
    for (int i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (c >= 'A' && c <= 'Z') {
            key_buf[k_idx++] = c;
        }
    }
    while (k_idx < size * size) {
        key_buf[k_idx] = key_buf[k_idx % size];
        k_idx++;
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = key_buf[i * size + j] - 'A';
        }
    }
}

int mod_inverse_26(int a) {
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) return i;
    }
    return 1;
}

void invert_key_matrix_2x2(const int matrix[][2], int inv[][2]) {
    int a = matrix[0][0], b = matrix[0][1];
    int c = matrix[1][0], d = matrix[1][1];
    
    int det = (a * d - b * c) % 26;
    if (det < 0) det += 26;
    int det_inv = mod_inverse_26(det);
    
    inv[0][0] = (d * det_inv) % 26;
    inv[0][1] = ((-b % 26 + 26) * det_inv) % 26;
    inv[1][0] = ((-c % 26 + 26) * det_inv) % 26;
    inv[1][1] = (a * det_inv) % 26;
}

void matrix_multiply_2x2(const int matrix[][2], const int vector[2], int result[2]) {
    for (int i = 0; i < 2; i++) {
        int total = 0;
        for (int j = 0; j < 2; j++) {
            total += matrix[i][j] * vector[j];
        }
        result[i] = total % 26;
    }
}

void hill_encrypt(const char *plaintext, const char *key, char *result) {
    char buf[100];
    int p_idx = 0;
    
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = toupper(plaintext[i]);
        if (c == 'J') c = 'I';
        if (c >= 'A' && c <= 'Z') {
            buf[p_idx++] = c;
        }
    }
    
    while (p_idx % 2 != 0) {
        buf[p_idx++] = 'X';
    }
    buf[p_idx] = '\0';
    
    int key_matrix[2][2];
    create_key_matrix(key, 2, key_matrix);
    
    int r_idx = 0;
    for (int i = 0; buf[i + 1] != '\0'; i += 2) {
        int vec[2] = {buf[i] - 'A', buf[i + 1] - 'A'};
        int enc[2];
        matrix_multiply_2x2(key_matrix, vec, enc);
        
        result[r_idx] = (char)(enc[0] + 'A');
        result[r_idx + 1] = (char)(enc[1] + 'A');
        r_idx += 2;
    }
    result[r_idx] = '\0';
}

void hill_decrypt(const char *ciphertext, const char *key, char *result) {
    char buf[100];
    int p_idx = 0;
    
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (toupper(ciphertext[i]) >= 'A' && toupper(ciphertext[i]) <= 'Z') {
            buf[p_idx++] = toupper(ciphertext[i]);
        }
    }
    buf[p_idx] = '\0';
    
    int key_matrix[2][2];
    create_key_matrix(key, 2, key_matrix);
    
    int inv_matrix[2][2];
    invert_key_matrix_2x2(key_matrix, inv_matrix);
    
    int r_idx = 0;
    for (int i = 0; buf[i + 1] != '\0'; i += 2) {
        int vec[2] = {buf[i] - 'A', buf[i + 1] - 'A'};
        int dec[2];
        matrix_multiply_2x2(inv_matrix, vec, dec);
        
        result[r_idx] = (char)(dec[0] + 'A');
        result[r_idx + 1] = (char)(dec[1] + 'A');
        r_idx += 2;
    }
    result[r_idx] = '\0';
}

int main() {
    const char *text = "ACT";
    const char *key = "BCAD";
    
    char encrypted[100];
    char decrypted[100];
    
    hill_encrypt(text, key, encrypted);
    hill_decrypt(encrypted, key, decrypted);
    
    printf("Original: %s\n", text);
    printf("Key: %s\n", key);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}
