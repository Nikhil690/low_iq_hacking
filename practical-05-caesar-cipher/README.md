# Practical 5: Caesar Cipher

## Overview
The Caesar Cipher is one of the simplest and most widely known encryption techniques. It is a type of substitution cipher where each letter in the plaintext is shifted a certain number of places down or up the alphabet.

## Algorithm Details

### How It Works
1. Choose a shift value (key), typically between 1-25
2. For each character in the plaintext:
   - If uppercase: shift within A-Z range
   - If lowercase: shift within a-z range
   - Non-alphabetic characters remain unchanged
3. The shift wraps around using modulo 26

### Mathematical Formula
- **Encryption**: `E(x) = (x + n) mod 26`
- **Decryption**: `D(x) = (x - n) mod 26`

Where:
- `x` is the position of the letter in the alphabet (0-25)
- `n` is the shift value (key)

## Implementation

### Functions Provided

#### `caesar_encrypt(plaintext, shift)`
Encrypts the given plaintext using Caesar cipher with the specified shift value.

**Parameters:**
- `plaintext`: The text to encrypt (string)
- `shift`: The number of positions to shift (integer)

**Returns:** Encrypted ciphertext (string)

#### `caesar_decrypt(ciphertext, shift)`
Decrypts the given ciphertext using Caesar cipher with the specified shift value.

**Parameters:**
- `ciphertext`: The text to decrypt (string)
- `shift`: The number of positions shifted (integer)

**Returns:** Decrypted plaintext (string)

## Example Usage

```python
from caesar_cipher import caesar_encrypt, caesar_decrypt

text = "Hello World"
key = 3

encrypted = caesar_encrypt(text, key)
# Output: "Khoor Zruog"

decrypted = caesar_decrypt(encrypted, key)
# Output: "Hello World"
```

## Visualization

```
Original Alphabet:  ABCDEFGHIJKLMNOPQRSTUVWXYZ
Shifted by 3:       DEFGHIJKLMNOPQRSTUVWXYZABC

Plain:   H  e  l  l  o  W  o  r  l  d
Cipher:  K  h  o  o  r  Z  r  u  o  g
```

## Complexity Analysis

- **Time Complexity**: O(n) where n is the length of plaintext
- **Space Complexity**: O(n) for storing the result

## Strengths & Weaknesses

### Strengths
- Simple to understand and implement
- Easy to use without special tools
- Good for educational purposes

### Weaknesses
- Only 25 possible keys (easy to brute-force)
- Preserves letter frequency patterns
- Vulnerable to frequency analysis attacks

## Historical Context
Named after Julius Caesar, who reportedly used this cipher with a shift of 3 to communicate with his generals. Despite its simplicity, it remained effective for its intended purpose due to the limited literacy of the time.
