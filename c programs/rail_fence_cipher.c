#include <stdio.h>
#include <string.h>

void rail_fence_encrypt(const char *plaintext, int rails, char *result) {
    if (rails <= 1 || strlen(plaintext) <= rails) {
        strcpy(result, plaintext);
        return;
    }
    
    int len = strlen(plaintext);
    char fence[100][100];
    int fence_len[100] = {0};
    
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            fence[i][j] = '\0';
        }
    }
    
    int rail = 0;
    int direction = 1;
    
    for (int i = 0; i < len; i++) {
        fence[rail][fence_len[rail]] = plaintext[i];
        fence_len[rail]++;
        
        if (rail == 0) {
            direction = 1;
        } else if (rail == rails - 1) {
            direction = -1;
        }
        rail += direction;
    }
    
    int r_idx = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < fence_len[i]; j++) {
            result[r_idx] = fence[i][j];
            r_idx++;
        }
    }
    result[r_idx] = '\0';
}

void rail_fence_decrypt(const char *ciphertext, int rails, char *result) {
    if (rails <= 1 || strlen(ciphertext) <= rails) {
        strcpy(result, ciphertext);
        return;
    }
    
    int len = strlen(ciphertext);
    int fence[100][100];
    
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            fence[i][j] = 0;
        }
    }
    
    int rail = 0;
    int direction = 1;
    for (int i = 0; i < len; i++) {
        fence[rail][i] = 1;
        
        if (rail == 0) {
            direction = 1;
        } else if (rail == rails - 1) {
            direction = -1;
        }
        rail += direction;
    }
    
    int chars_index = 0;
    for (int r = 0; r < rails; r++) {
        for (int c = 0; c < len; c++) {
            if (fence[r][c] == 1) {
                fence[r][c] = ciphertext[chars_index];
                chars_index++;
            }
        }
    }
    
    int r_idx = 0;
    rail = 0;
    direction = 1;
    for (int i = 0; i < len; i++) {
        result[r_idx] = (char)fence[rail][i];
        r_idx++;
        
        if (rail == 0) {
            direction = 1;
        } else if (rail == rails - 1) {
            direction = -1;
        }
        rail += direction;
    }
    result[r_idx] = '\0';
}

int main() {
    const char *text = "HELLO WORLD";
    int key = 3;
    
    char encrypted[100];
    char decrypted[100];
    
    rail_fence_encrypt(text, key, encrypted);
    rail_fence_decrypt(encrypted, key, decrypted);
    
    printf("Original: %s\n", text);
    printf("Rails: %d\n", key);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}
