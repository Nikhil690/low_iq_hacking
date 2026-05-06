# Practical 8: Hill Cipher

## Overview
The Hill cipher is a polygraphic substitution cipher based on linear algebra. Invented by Lester S. Hill in 1929, it encrypts blocks of letters simultaneously using matrix multiplication modulo 26.

---

## Algorithm Details

### Mathematical Foundation

The Hill cipher uses matrix multiplication over the field Z₂₆ (integers mod 26).

**Encryption Formula:**
```
C = (K × P) mod 26
```

Where:
- `C` is the ciphertext vector
- `K` is the key matrix (n×n)
- `P` is the plaintext vector (n×1)

**Decryption Formula:**
```
P = (K⁻¹ × C) mod 26
```

Where `K⁻¹` is the modular multiplicative inverse of the key matrix.

### Key Matrix Requirements

For a valid Hill cipher key:
1. Must be an n×n square matrix
2. Determinant must be coprime with 26 (gcd(det(K), 26) = 1)
3. Common sizes: 2×2, 3×3

### Key Matrix Construction

Given a keyword, fill the matrix row by row:
```
Key: "GYBNQKURP" → 3×3 matrix
G Y B   →  6 24 1
N Q K       13 16 10
U R P       20 17 15
```

### Encryption Process

1. Convert plaintext to numerical values (A=0, B=1, ..., Z=25)
2. Split into vectors of size n
3. Multiply each vector by the key matrix mod 26
4. Convert result back to letters

**Example (2×2):**
```
Plaintext: "ACT" → [0, 2] and [19, ?] padded to [19, 23]
Key Matrix: [[6, 24], [13, 16]]

Encryption of [0, 2]:
[6  24]   [0]     [(6×0 + 24×2) mod 26]     [20]
[13 16] × [2]  =  [(13×0 + 16×2) mod 26]  = [6 ]

Result: "UG"
```

### Decryption Process

1. Calculate the inverse of the key matrix mod 26
2. Convert ciphertext to numerical vectors
3. Multiply each vector by K⁻¹ mod 26
4. Convert result back to letters

**Matrix Inverse Calculation:**
```
For 2×2 matrix [[a, b], [c, d]]:

1. Calculate det = (ad - bc) mod 26
2. Find det⁻¹ using modular inverse
3. Adjugate = [[d, -b], [-c, a]]
4. K⁻¹ = det⁻¹ × Adjugate mod 26
```

---

## Implementation Functions

### `create_key_matrix(key, size)`
Creates an n×n key matrix from a keyword.

**Parameters:**
- `key`: Keyword string for the matrix
- `size`: Dimension of the square matrix (e.g., 2 for 2×2)

**Returns:** List of lists representing the matrix

### `mod_inverse_26(a)`
Finds the modular multiplicative inverse of a number mod 26.

**Parameters:**
- `a`: Number to find inverse for

**Returns:** Modular inverse (or 1 if none exists)

### `determinant_2x2(matrix)`
Calculates determinant of a 2×2 matrix modulo 26.

### `invert_key_matrix_2x2(matrix)`
Computes the modular inverse of a 2×2 key matrix.

### `matrix_multiply_2x2(matrix, vector)`
Multiplies a 2×2 matrix by a 2-element vector mod 26.

### `hill_encrypt(plaintext, key)`
Encrypts plaintext using Hill cipher with 2×2 key matrix.

**Parameters:**
- `plaintext`: Text to encrypt
- `key`: Keyword for generating the key matrix

**Returns:** Encrypted ciphertext

### `hill_decrypt(ciphertext, key)`
Decrypts ciphertext back to plaintext.

---

## Complete Example

```
Key: "GYBNQKURP" (3×3 matrix)
Plaintext: "ACT"

Step 1 - Create Key Matrix:
G=6   Y=24  B=1
N=13  Q=16  K=10
U=20  R=17  P=15

Matrix:
[ 6  24   1 ]
[13  16  10 ]
[20  17  15 ]

Step 2 - Convert Plaintext:
A=0, C=2, T=19 → Vector [0, 2, 19]

Step 3 - Multiply (mod 26):
Result = [24, 18, 20] → "YSU"

Decryption reverses the process using K⁻¹
```

---

## Complexity Analysis

### Time Complexity
- **Encryption**: O(n² × m) where n is matrix size and m is plaintext length
- **Decryption**: O(n³ + n² × m) for inverse calculation plus encryption

### Space Complexity
- **Key Matrix**: O(n²)
- **Result**: O(m) for output string

---

## Strengths & Weaknesses

### Strengths
- **Mathematical elegance**: Clean linear algebra foundation
- **Diffusion**: Each ciphertext letter depends on multiple plaintext letters
- **Efficient**: Fast matrix multiplication for encryption/decryption
- **Key space**: Large key space for larger matrices (26^(n²) possibilities)

### Weaknesses
- **Linear structure**: Vulnerable to known-plaintext attacks
- **Determinant requirement**: Not all matrices are valid keys
- **No substitution**: Purely transpositional, preserves letter frequencies in blocks
- **Padding needed**: Requires padding for messages not divisible by matrix size

---

## Security Considerations

### Known-Plaintext Attack
An attacker with n² known plaintext-ciphertext pairs can recover the key matrix by solving a system of linear equations.

### Chosen-Plaintext Attack
Carefully chosen plaintext blocks can reveal the entire key structure quickly.

### Improvements
To enhance security:
1. Use larger matrices (3×3 or bigger)
2. Combine with substitution ciphers
3. Add non-linear operations

---

## Usage Example

```python
from hill_cipher import hill_encrypt, hill_decrypt

text = "HELLO"
key = "GYBNQKURP"

encrypted = hill_encrypt(text, key)
decrypted = hill_decrypt(encrypted, key)

print(f"Original: {text}")
print(f"Key: {key}")
print(f"Encrypted: {encrypted}")
print(f"Decrypted: {decrypted}")
```

---

## Notes

1. **Matrix Size**: This implementation uses 2×2 matrices for simplicity; 3×3 is also common
2. **Padding**: 'X' is used to pad messages to even length (for 2×2) or appropriate size
3. **J/I Convention**: J is treated as I to maintain 26-letter alphabet
4. **Key Validation**: In production, verify gcd(det(K), 26) = 1 before using
