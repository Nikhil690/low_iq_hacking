# Practical 6: Monoalphabetic & Polyalphabetic Cipher

## Overview
This practical implements two types of substitution ciphers:
1. **Monoalphabetic Cipher**: Uses a fixed substitution alphabet for the entire message
2. **Polyalphabetic Cipher (Vigenère)**: Uses multiple substitution alphabets based on a keyword

---

## Part 1: Monoalphabetic Cipher

### Algorithm Details

A monoalphabetic cipher uses a one-to-one mapping between plaintext and ciphertext letters. Unlike Caesar cipher which shifts all letters uniformly, this creates a completely randomized substitution alphabet based on a keyword.

### Key Generation
1. Start with a keyword (removing duplicates)
2. Append remaining letters of the alphabet in order
3. This creates a unique substitution alphabet

**Example:**
```
Keyword: CRYPTO
Alphabet: ABCDEFGHIJKLMNOPQRSTUVWXYZ
Key Map:  CRYPTOABDFGHIJLMNQSUWXVKZ
```

### Functions

#### `create_monoalphabetic_key(key_word)`
Creates a substitution key from a keyword.

#### `monoalphabetic_encrypt(plaintext, key_word)`
Encrypts text using the keyword-based monoalphabetic substitution.

#### `monoalphabetic_decrypt(ciphertext, key_word)`
Decrypts text back to original plaintext.

### Example
```python
text = "Hello World"
key = "CRYPTO"
# H -> R, e -> G, l -> L, o -> O, etc.
```

---

## Part 2: Polyalphabetic Cipher (Vigenère)

### Algorithm Details

The Vigenère cipher uses multiple Caesar ciphers based on a keyword. Each letter of the keyword determines the shift for corresponding plaintext letters.

### How It Works
1. Write the keyword repeatedly above the plaintext
2. For each letter, use the Vigenère table to find the ciphertext
3. The row is determined by the plaintext letter, column by the keyword letter

**Vigenère Table (excerpt):**
```
    ABCDEFGHIJK...
A   ABCDEFGHIJK...
B   BCDEFGHIKLM...
C   CDEFGHIJKLM...
...
K   KLMNOPQRSTUVW...
```

### Mathematical Formula
- **Encryption**: `E_i(x) = (x + k_i) mod 26`
- **Decryption**: `D_i(x) = (x - k_i) mod 26`

Where `k_i` is the shift value for position i based on the keyword.

### Functions

#### `vigenere_encrypt(plaintext, keyword)`
Encrypts using Vigenère cipher with the given keyword.

#### `vigenere_decrypt(ciphertext, keyword)`
Decrypts Vigenère encrypted text.

### Example
```
Plaintext:  H E L L O W O R L D
Keyword:    K E Y K E Y K E Y K
Shift:      10 4 24 10 4 24 10 4 24 10

H(7) + K(10) = R(17)
E(4) + E(4)  = I(8)
L(11) + Y(24)= J(9)
...
Ciphertext:  R I J J S O G W J N
```

---

## Comparison

| Feature | Monoalphabetic | Polyalphabetic (Vigenère) |
|---------|---------------|--------------------------|
| Substitution | Fixed mapping | Multiple mappings |
| Key Space | 26! (~4×10²⁶) | 26^k (k = keyword length) |
| Frequency Analysis | Effective | Less effective |
| Security | Moderate | Better |

---

## Complexity Analysis

### Monoalphabetic
- **Time**: O(n) for encryption/decryption
- **Space**: O(1) for key map, O(n) for result

### Polyalphabetic (Vigenère)
- **Time**: O(n) for encryption/decryption
- **Space**: O(k) for keyword storage, O(n) for result

---

## Strengths & Weaknesses

### Monoalphabetic
**Strengths:**
- Large key space makes brute-force difficult
- Simple to implement

**Weaknesses:**
- Letter frequency patterns preserved
- Vulnerable to frequency analysis

### Polyalphabetic (Vigenère)
**Strengths:**
- Masks letter frequencies better
- More secure than monoalphabetic
- Key repetition adds complexity

**Weaknesses:**
- Keyword length can be detected (Kasiski examination)
- Still vulnerable with sufficient ciphertext
- Key management required

---

## Usage Examples

```python
from poly_alphabetic_cipher import *

# Monoalphabetic
text = "ATTACK AT DAWN"
mono_key = "SECRET"
encrypted = monoalphabetic_encrypt(text, mono_key)
decrypted = monoalphabetic_decrypt(encrypted, mono_key)

# Polyalphabetic
poly_key = "KEY"
encrypted_vigenere = vigenere_encrypt(text, poly_key)
decrypted_vigenere = vigenere_decrypt(encrypted_vigenere, poly_key)
```
