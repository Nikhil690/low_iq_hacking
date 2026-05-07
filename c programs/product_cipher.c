#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesar_encrypt(const char *text, int shift, char *result) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            result[i] = (char)((text[i] - 65 + shift) % 26 + 65);
        } else if (islower(text[i])) {
            result[i] = (char)((text[i] - 97 + shift) % 26 + 97);
        } else {
            result[i] = text[i];
        }
    }
    result[ strlen(text) ] = '\0';
}

void caesar_decrypt(const char *text, int shift, char *result) {
    caesar_encrypt(text, 26 - shift, result);
}

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

void row_transposition_encrypt(const char *text, const char *keyword, char *result) {
    int key_len = strlen(keyword);
    
    int padded_len = ((strlen(text) + key_len - 1) / key_len) * key_len;
    char buf[100];
    
    for (int i = 0; i < strlen(text); i++) {
        buf[i] = text[i];
    }
    for (int i = strlen(text); i < padded_len; i++) {
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

void row_transposition_decrypt(const char *text, const char *keyword, char *result) {
    int key_len = strlen(keyword);
    int text_len = strlen(text);
    int num_rows = (text_len + key_len - 1) / key_len;
    
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
            if (char_idx < text_len) {
                grid[row][orig_col] = text[char_idx];
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

void product_encrypt(const char *plaintext, int caesar_shift, const char *transposition_key, char *result) {
    char step1[100];
    caesar_encrypt(plaintext, caesar_shift, step1);
    row_transposition_encrypt(step1, transposition_key, result);
}

void product_decrypt(const char *ciphertext, int caesar_shift, const char *transposition_key, char *result) {
    char step1[100];
    row_transposition_decrypt(ciphertext, transposition_key, step1);
    caesar_decrypt(step1, caesar_shift, result);
}

int main() {
    const char *text = "SECRET MESSAGE";
    int shift = 3;
    const char *key = "PYTHON";
    
    char encrypted[100];
    char decrypted[100];
    
    product_encrypt(text, shift, key, encrypted);
    product_decrypt(encrypted, shift, key, decrypted);
    
    printf("Original: %s\n", text);
    printf("Caesar Shift: %d\n", shift);
    printf("Transposition Key: %s\n", key);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}
