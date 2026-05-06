# Practical 10: Row Transposition Cipher

## Overview
The Row Transposition cipher (also known as Columnar Transposition) is a transposition cipher that rearranges plaintext by writing it in rows and reading columns in an order determined by a keyword. The column read order follows the alphabetical sorting of the keyword letters.

---

## Algorithm Details

### How It Works

1. **Write Phase**: Write plaintext horizontally in rows of fixed width (keyword length)
2. **Key Processing**: Determine column read order from keyword's alphabetical arrangement
3. **Read Phase**: Read columns in the order specified by the sorted keyword

### Key Order Determination

The keyword determines which column is read first, second, third, etc.:

**Example with key "ZEBRAS":**
```
Keyword:    Z  E  B  R  A  S
Position:   0  1  2  3  4  5
Alphabet:   A  B  E  R  S  Z
Order:      4  2  1  3  5  0

Read order: Column 4 first, then 2, 1, 3, 5, and finally 0
```

### Encryption Process

**Example with "ATTACK AT DAWN" and key "ZEBRAS":**

```
Step 1 - Write in rows (6 columns):

A T T A C K   (Row 0)
A T X D A W   (Row 1, padded with X)

Column indices: 0  1  2  3  4  5

Step 2 - Determine read order from "ZEBRAS":
Z=21(5), E=4(1), B=1(0), R=17(3), A=0(0), S=18(4)
Alphabetical: A(4), B(2), E(1), R(3), S(5), Z(0)
Read order: 4, 2, 1, 3, 5, 0

Step 3 - Read columns in order [4, 2, 1, 3, 5, 0]:
Col 4: C A
Col 2: T X  
Col 1: T T
Col 3: A D
Col 5: K W
Col 0: A A

Ciphertext: "CATXTTADKWA A" → "CATXTTADKWAA"
```

### Decryption Process

1. Calculate grid dimensions (rows = ceil(length/key_length))
2. Fill columns in the order dictated by keyword sorting
3. Read rows horizontally to recover plaintext
4. Remove padding characters

---

## Mathematical Representation

Given:
- Plaintext P of length n
- Keyword K of length m
- Number of rows r = ⌈n/m⌉

**Grid Construction:**
```
G[i][j] = P[i × m + j]  for i ∈ [0, r), j ∈ [0, m)
```

**Read Order:**
Let σ be the permutation that sorts K alphabetically:
- σ(0) = index of smallest letter in K
- σ(1) = index of second smallest letter in K
- etc.

**Ciphertext:** C = concatenation of columns G[·][σ⁻¹(0)], G[·][σ⁻¹(1)], ...

---

## Implementation Functions

### `get_key_order(keyword)`
Determines the column read order based on alphabetical sorting of the keyword.

**Parameters:**
- `keyword`: The encryption key string

**Returns:** List where position i contains the original column index that should be read at position i

**Example:**
```python
get_key_order("ZEBRAS")  # Returns [4, 2, 1, 3, 5, 0]
# Column 4 (A) is read first, then 2 (B), etc.
```

### `row_transposition_encrypt(plaintext, keyword)`
Encrypts plaintext using Row Transposition cipher.

**Parameters:**
- `plaintext`: Text to encrypt
- `keyword`: Key determining column order

**Returns:** Encrypted ciphertext

**Algorithm Steps:**
1. Pad plaintext to fit complete grid (add 'X' characters)
2. Fill grid row by row
3. Read columns in keyword-specified order
4. Concatenate to form ciphertext

### `row_transposition_decrypt(ciphertext, keyword)`
Decrypts Row Transposition ciphertext back to plaintext.

**Parameters:**
- `ciphertext`: Encrypted text
- `keyword`: Key used for encryption

**Returns:** Decrypted plaintext (padding removed)

**Algorithm Steps:**
1. Calculate grid dimensions
2. Determine column read order from keyword
3. Fill columns in the correct order with ciphertext
4. Read rows to recover original message
5. Strip padding characters ('X')

---

## Complete Example

```python
from row_transposition_cipher import row_transposition_encrypt, row_transposition_decrypt

# Setup
text = "WE ARE DISCOVERED FLEE AT ONCE"
key = "CIPHER"

# Encryption visualization:
W E A R E D    (Row 0)
I S C O V E    (Row 1)  
R E D F L E    (Row 2)
E A T O N C    (Row 3, padded with X if needed)

Key analysis "CIPHER":
C=0(0), I=8(1), P=15(2), H=7(3), E=4(0), R=17(4)
Alphabetical: C(0), E(4), H(3), I(1), P(2), R(4)
Read order: 0, 4, 3, 1, 2, 5

Columns read in order [0, 4, 3, 1, 2, 5]:
Col 0: W I R E
Col 4: A V L N  
Col 3: R O F O
Col 1: E S E A
Col 2: A C D T
Col 5: D E E C

Ciphertext: "WIREAVLNROFOESE AACDTDEEC"
```

---

## Complexity Analysis

### Time Complexity
- **Encryption**: O(n + m log m) where n = plaintext length, m = keyword length
  - Grid filling: O(n)
  - Sorting keyword: O(m log m)
  - Column reading: O(n)
  
- **Decryption**: O(n + m log m)
  - Similar operations as encryption

### Space Complexity
- **Encryption**: O(n) for grid storage and result
- **Decryption**: O(n) for grid reconstruction

---

## Strengths & Weaknesses

### Strengths
- **Better than Rail Fence**: More complex rearrangement pattern
- **Key flexibility**: Any word can serve as key
- **No letter substitution**: Original characters preserved
- **Good diffusion**: Each ciphertext position depends on multiple plaintext positions

### Weaknesses
- **Known-plaintext vulnerable**: With enough known pairs, grid dimensions can be deduced
- **Anagram attacks**: Column rearrangement detectable through letter frequency analysis
- **Padding artifacts**: 'X' padding may create recognizable patterns
- **Limited key space**: Practical keys are dictionary words

---

## Key Space Analysis

For keyword of length m:
- Possible permutations: m! (factorial)
- However, duplicate letters reduce effective key space
- Dictionary words provide ~10⁴ to 10⁶ possible keys depending on length

**Examples:**
- 5-letter keyword: up to 120 permutations
- 7-letter keyword: up to 5,040 permutations  
- 10-letter keyword: up to 3,628,800 permutations

---

## Variations

### 1. Double Transposition
Apply Row Transposition twice with different keys for enhanced security.

### 2. Irregular Columnar
Use varying row lengths based on keyword letter values.

### 3. Route Variation
Read columns in different patterns (diagonal, spiral) instead of top-to-bottom.

---

## Historical Context

- Used extensively during World War I and II
- German Army employed variations for field communications
- British forces used it for tactical messages
- Often combined with other ciphers for enhanced security

---

## Usage Example

```python
from row_transposition_cipher import row_transposition_encrypt, row_transposition_decrypt

text = "THE QUICK BROWN FOX JUMPS"
key = "SECRET"

encrypted = row_transposition_encrypt(text, key)
decrypted = row_transposition_decrypt(encrypted, key)

print(f"Original: {text}")
print(f"Key: {key}")  
print(f"Encrypted: {encrypted}")
print(f"Decrypted: {decrypted}")
```

---

## Practical Tips

1. **Keyword choice**: Use longer keywords for better security
2. **No duplicate letters**: Keywords without repeated letters maximize key space
3. **Padding awareness**: Padding character 'X' can be changed to any unused letter
4. **Combined encryption**: Often used after substitution ciphers for layered security
