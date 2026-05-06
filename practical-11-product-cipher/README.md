# Practical 11: Product Cipher

## Overview
A Product cipher combines two or more simple ciphers sequentially to create a stronger encryption system. This practical implements a product cipher that chains a **Caesar substitution** followed by a **Row Transposition**, demonstrating how combining different cipher types enhances security through both confusion and diffusion.

---

## Algorithm Details

### Concept

The term "Product Cipher" was coined by Claude Shannon to describe ciphers that combine multiple operations:
- **Substitution** provides *confusion* (hides relationship between key and ciphertext)
- **Transposition** provides *diffusion* (spreads plaintext statistics across ciphertext)

### Implementation Structure

This implementation uses a two-stage product:

```
Plaintext → [Caesar Cipher] → Intermediate → [Row Transposition] → Ciphertext
```

**Encryption Flow:**
1. Apply Caesar cipher with specified shift
2. Apply Row Transposition with keyword key

**Decryption Flow (reverse order):**
1. Reverse the transposition (Row Transposition decrypt)
2. Reverse the substitution (Caesar decrypt)

---

## Mathematical Representation

Given:
- Plaintext P
- Caesar shift s
- Transposition key K

**Encryption:**
```
E(P) = T_K(C_s(P))
```

Where:
- C_s = Caesar encryption with shift s
- T_K = Row transposition with key K

**Decryption:**
```
D(C) = C⁻¹_s(T⁻¹_K(C))
```

The operations must be applied in reverse order for decryption.

---

## Component Ciphers

### Stage 1: Caesar Cipher (Substitution)

**Purpose**: Provides initial confusion by shifting each character.

**Operation:**
- Shifts each letter by a fixed amount (key = shift value)
- Preserves letter positions but changes their values
- Simple modular arithmetic: `E(x) = (x + s) mod 26`

### Stage 2: Row Transposition (Transposition)

**Purpose**: Provides diffusion by rearranging character positions.

**Operation:**
- Writes substituted text in rows
- Reads columns in keyword-determined order
- Preserves letter values but changes their positions

---

## Why Product Ciphers Are Stronger

### 1. Combined Confusion and Diffusion
| Property | Caesar Alone | Transposition Alone | Product Cipher |
|----------|-------------|---------------------|----------------|
| Confusion | ✓ | ✗ | ✓✓ |
| Diffusion | ✗ | ✓ | ✓✓ |

### 2. Enhanced Key Space
- **Caesar alone**: 25 possible keys (shifts 1-25)
- **Transposition alone**: n! permutations for n-letter key
- **Product cipher**: 25 × n! combined possibilities

**Example:** With shift=3 and "PYTHON" (6 letters):
- Keyspace = 25 × 720 = 18,000 combinations

### 3. Resistance to Frequency Analysis
- Caesar preserves frequency patterns → vulnerable
- Transposition alone preserves frequencies → somewhat vulnerable
- Product cipher: Substitution changes frequencies AND transposition scatters them → much harder to analyze

---

## Implementation Functions

### `caesar_encrypt(text, shift)`
Applies Caesar cipher encryption as first stage.

**Parameters:**
- `text`: Input text (string)
- `shift`: Shift value 1-25 (integer)

**Returns:** Caesar-encrypted text

### `caesar_decrypt(text, shift)`
Reverses Caesar cipher encryption.

**Parameters:**
- `text`: Caesar-encrypted text
- `shift`: Original shift value

**Returns:** Decrypted text

### `get_key_order(keyword)`
Helper function to determine column read order from keyword.

### `row_transposition_encrypt(text, keyword)`
Applies Row Transposition as second encryption stage.

### `row_transposition_decrypt(text, keyword)`
Reverses the transposition step during decryption.

### `product_encrypt(plaintext, caesar_shift, transposition_key)`
Main encryption function combining both ciphers.

**Parameters:**
- `plaintext`: Original message to encrypt
- `caesar_shift`: Integer shift value (1-25)
- `transposition_key`: Keyword string for column ordering

**Returns:** Fully encrypted ciphertext

### `product_decrypt(ciphertext, caesar_shift, transposition_key)`
Main decryption function reversing both operations.

**Parameters:**
- `ciphertext`: Encrypted message to decrypt
- `caesar_shift`: Original Caesar shift value
- `transposition_key`: Original keyword used

**Returns:** Fully decrypted plaintext

---

## Complete Example Walkthrough

```python
from product_cipher import product_encrypt, product_decrypt

# Setup
text = "SECRET"
shift = 3
key = "DOG"

# === ENCRYPTION ===

Step 1 - Caesar (shift=3):
S → V
E → H  
C → F
R → U
E → H
T → W
Result: "VHFUHW"

Step 2 - Row Transposition (key="DOG"):
Key analysis: D(0), O(14), G(6)
Alphabetical order: D(0), G(2), O(1)
Read columns in order [0, 2, 1]

Write "VHFUHW" in rows of length 3:
V H F   (Row 0)
U H W   (Row 1)

Column indices: 0  1  2

Read column 0: V U
Read column 2: F W  
Read column 1: H H

Final ciphertext: "VUFWHH"


# === DECRYPTION ===

Step 1 - Reverse Transposition (key="DOG"):
Reconstruct grid from "VUFWHH":
Column order [0, 2, 1] means:
Col 0 gets first chunk: V U
Col 2 gets second chunk: F W
Col 1 gets third chunk: H H

Grid reconstruction:
V H F
U H W

Read rows: "VHFUHW"

Step 2 - Reverse Caesar (shift=3):
V → S
H → E
F → C  
U → R
H → E
W → T

Final plaintext: "SECRET" ✓
```

---

## Complexity Analysis

### Time Complexity
- **Encryption**: O(n) where n = plaintext length
  - Caesar pass: O(n)
  - Transposition pass: O(n + m log m) for key sorting
  
- **Decryption**: O(n) similar structure

### Space Complexity
- **Overall**: O(n) for intermediate storage and result

---

## Strengths & Weaknesses

### Strengths
1. **Enhanced security**: Combines two different cryptographic principles
2. **Larger keyspace**: Product of individual key spaces
3. **Frequency hiding**: Both substitution changes AND position scattering
4. **Modular design**: Easy to swap components (e.g., use Vigenère instead of Caesar)

### Weaknesses
1. **Still linear**: Individual operations remain mathematically simple
2. **Padding artifacts**: Transposition padding may leak information
3. **Key management**: Requires managing multiple keys
4. **Not modern strength**: Historical product ciphers were superseded by DES/AES

---

## Historical Context

### Modern Examples of Product Ciphers

1. **DES (Data Encryption Standard)**: 
   - Combines substitution (S-boxes) and permutation (P-boxes)
   - 16 rounds of Feistel structure
   
2. **AES (Advanced Encryption Standard)**:
   - Uses SubBytes, ShiftRows, MixColumns, AddRoundKey
   - Multiple rounds create product effect

3. **SP-Networks**: 
   - Substitution-Permutation networks are classic product ciphers
   - Form basis of most modern block ciphers

### This Implementation's Place
This Caesar+Transposition combination represents an early form of product cipher thinking, similar to techniques used in the late 19th and early 20th centuries before formal cryptographic theory was developed.

---

## Usage Example

```python
from product_cipher import product_encrypt, product_decrypt

# Encrypt a message
message = "ATTACK AT DAWN"
caesar_key = 7
transposition_key = "SECRET"

encrypted = product_encrypt(message, caesar_key, transposition_key)
print(f"Encrypted: {encrypted}")

# Decrypt the message
decrypted = product_decrypt(encrypted, caesar_key, transposition_key)
print(f"Decrypted: {decrypted}")
```

---

## Practical Considerations

### Key Selection Guidelines

1. **Caesar Shift**: 
   - Avoid 0 (no encryption) and 13 (symmetric for some letters)
   - Any value 1-25 provides valid transformation

2. **Transposition Key**:
   - Longer keys = more permutations = better security
   - No repeated letters maximizes key space
   - Use memorable words for practical use

### Common Variations

1. **Triple Product**: Caesar → Transposition → Caesar
2. **Different Substitution**: Replace Caesar with Vigenère or Playfair
3. **Multiple Rounds**: Apply the product multiple times

---

## Comparison Summary

| Cipher Type | Confusion | Diffusion | Keyspace | Security Level |
|-------------|-----------|-----------|----------|----------------|
| Caesar Only | Medium | None | 25 | Low |
| Transposition Only | None | Medium | n! | Medium |
| **Product** | **High** | **High** | **25 × n!** | **High** |

---

## Exercises for Practice

1. Encrypt "HELLO WORLD" with shift=5 and key="KEY"
2. Decrypt "XKJWZM" with shift=3 and key="CAT"  
3. Compare frequency distribution of plaintext vs ciphertext
4. Try breaking the cipher without knowing both keys
