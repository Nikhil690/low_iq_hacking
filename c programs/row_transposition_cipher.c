#include <stdio.h>
#include <string.h>
#include <ctype.h>

void get_key_order(const char *keyword, int order[]) {
    int key_len = strlen(keyword);
    
    for (int i = 0; i < key_len; i++) {
        order[i] = i;
    }
    
    for (int i = 0; i < key_len - 1; i++) {
        for (int j = i + 1; j < key_len; j++) {
            char ci = toupper(keyword[order[i]]);
            char cj = toupper(keyword[order[j]]);
            
            if (ci > cj || (ci == cj && order[i] > order[j])) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
}

void row_transposition_encrypt(const char *plaintext, const char *keyword, char *result) {
    int key_len = strlen(keyword);
    
    int padded_len = ((strlen(plaintext) + key_len - 1) / key_len) * key_len;
    char buf[100];
    
    for (int i = 0; i < strlen(plaintext); i++) {
        buf[i] = plaintext[i];
    }
    for (int i = strlen(plaintext); i < padded_len; i++) {
        buf[i] = 'X';
    }
    buf[padded_len] = '\0';
    
    int num_rows = padded_len / key_len;
    char grid[10][20];
    
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < key_len; j++) {
            grid[i][j] = buf[i * key_len + j];
        }
    }
    
    int order[20];
    get_key_order(keyword, order);
    
    int r_idx = 0;
    for (int col = 0; col < key_len; col++) {
        int orig_col = -1;
        for (int i = 0; i < key_len; i++) {
            if (order[i] == col) {
                orig_col = i;
                break;
            }
        }
        
        for (int row = 0; row < num_rows; row++) {
            result[r_idx] = grid[row][orig_col];
            r_idx++;
        }
    }
    result[r_idx] = '\0';
}

void row_transposition_decrypt(const char *ciphertext, const char *keyword, char *result) {
    int key_len = strlen(keyword);
    int cipher_len = strlen(ciphertext);
    int num_rows = (cipher_len + key_len - 1) / key_len;
    
    int order[20];
    get_key_order(keyword, order);
    
    char grid[10][20];
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < key_len; j++) {
            grid[i][j] = '\0';
        }
    }
    
    int char_idx = 0;
    for (int new_col = 0; new_col < key_len; new_col++) {
        int orig_col = order[new_col];
        for (int row = 0; row < num_rows; row++) {
            if (char_idx < cipher_len) {
                grid[row][orig_col] = ciphertext[char_idx];
                char_idx++;
            }
        }
    }
    
    int r_idx = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < key_len && grid[i][j] != '\0'; j++) {
            result[r_idx] = grid[i][j];
            r_idx++;
        }
    }
    
    while (r_idx > 0 && result[r_idx - 1] == 'X') {
        r_idx--;
    }
    result[r_idx] = '\0';
}

int main() {
    const char *text = "ATTACK AT DAWN";
    const char *key = "ZEBRAS";
    
    char encrypted[100];
    char decrypted[100];
    
    row_transposition_encrypt(text, key, encrypted);
    row_transposition_decrypt(encrypted, key, decrypted);
    
    printf("Original: %s\n", text);
    printf("Key: %s\n", key);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}
