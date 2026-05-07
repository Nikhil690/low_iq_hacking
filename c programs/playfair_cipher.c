#include <stdio.h>
#include <string.h>
#include <ctype.h>

void create_playfair_matrix(const char *key_word, char matrix[5][5]) {
    int seen[26] = {0};
    int idx = 0;
    
    for (int i = 0; key_word[i] != '\0'; i++) {
        char c = toupper(key_word[i]);
        if (c == 'J') c = 'I';
        if (c >= 'A' && c <= 'Z' && !seen[c - 'A']) {
            seen[c - 'A'] = 1;
            matrix[idx / 5][idx % 5] = c;
            idx++;
        }
    }
    
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c != 'J' && !seen[c - 'A']) {
            matrix[idx / 5][idx % 5] = c;
            idx++;
        }
    }
}

void find_position(const char matrix[5][5], char ch, int *row, int *col) {
    for (*row = 0; *row < 5; (*row)++) {
        for (*col = 0; *col < 5; (*col)++) {
            if (matrix[*row][*col] == ch) return;
        }
    }
}

void prepare_text(const char *text, char *prepared) {
    int p_idx = 0;
    int t_len = strlen(text);
    
    for (int i = 0; i < t_len; i++) {
        char c = toupper(text[i]);
        if (c == 'J') c = 'I';
        
        prepared[p_idx] = c;
        p_idx++;
        
        if (i + 1 < t_len) {
            char next = toupper(text[i + 1]);
            if (next == 'J') next = 'I';
            
            if (c == next) {
                prepared[p_idx] = 'X';
            } else {
                prepared[p_idx] = next;
                i++;
            }
        } else {
            prepared[p_idx] = 'X';
        }
        p_idx++;
    }
    prepared[p_idx] = '\0';
}

void playfair_encrypt(const char *plaintext, const char *key_word, char *result) {
    char matrix[5][5];
    create_playfair_matrix(key_word, matrix);
    
    char prepared[100];
    prepare_text(plaintext, prepared);
    
    int p_len = strlen(prepared);
    int r_idx = 0;
    
    for (int i = 0; i < p_len; i += 2) {
        int r1, c1, r2, c2;
        find_position(matrix, prepared[i], &r1, &c1);
        find_position(matrix, prepared[i + 1], &r2, &c2);
        
        if (r1 == r2) {
            result[r_idx] = matrix[r1][(c1 + 1) % 5];
            result[r_idx + 1] = matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            result[r_idx] = matrix[(r1 + 1) % 5][c1];
            result[r_idx + 1] = matrix[(r2 + 1) % 5][c2];
        } else {
            result[r_idx] = matrix[r1][c2];
            result[r_idx + 1] = matrix[r2][c1];
        }
        r_idx += 2;
    }
    result[r_idx] = '\0';
}

void playfair_decrypt(const char *ciphertext, const char *key_word, char *result) {
    char matrix[5][5];
    create_playfair_matrix(key_word, matrix);
    
    int c_len = strlen(ciphertext);
    int r_idx = 0;
    
    for (int i = 0; i < c_len; i += 2) {
        int r1, c1, r2, c2;
        find_position(matrix, ciphertext[i], &r1, &c1);
        find_position(matrix, ciphertext[i + 1], &r2, &c2);
        
        if (r1 == r2) {
            result[r_idx] = matrix[r1][(c1 - 1 + 5) % 5];
            result[r_idx + 1] = matrix[r2][(c2 - 1 + 5) % 5];
        } else if (c1 == c2) {
            result[r_idx] = matrix[(r1 - 1 + 5) % 5][c1];
            result[r_idx + 1] = matrix[(r2 - 1 + 5) % 5][c2];
        } else {
            result[r_idx] = matrix[r1][c2];
            result[r_idx + 1] = matrix[r2][c1];
        }
        r_idx += 2;
    }
    result[r_idx] = '\0';
}

int main() {
    const char *text = "Hide the gold in the tree stump";
    const char *key = "PLAYFAIR";
    
    char encrypted[100];
    char decrypted[100];
    
    playfair_encrypt(text, key, encrypted);
    playfair_decrypt(encrypted, key, decrypted);
    
    printf("Original: %s\n", text);
    printf("Key: %s\n", key);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}
