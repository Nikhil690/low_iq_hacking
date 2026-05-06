# Practical 7: Playfair Cipher

## Overview
The Playfair cipher is a digraph substitution cipher that encrypts pairs of letters simultaneously. Invented by Charles Wheatstone in 1854 and popularized by Lord Playfair, it was the first polygraphic substitution cipher to gain widespread use.

---

## Algorithm Details

### Key Matrix Construction
A 5×5 matrix is created using a keyword:
1. Fill the matrix with unique letters from the keyword (left to right, top to bottom)
2. Fill remaining cells with remaining alphabet letters in order
3. Combine I and J into one cell (typically use I for both)

**Example with key "PLAYFAIR":**
```
P L A Y F
I R B C D
E G H K M
N O Q S T
U V W X Z
```

### Text Preparation Rules
1. Convert to uppercase and remove spaces
2. Replace J with I
3. Split into digraphs (pairs of 2 letters)
4. If a pair has identical letters, insert 'X' between them
5. If the final letter is alone, append 'X'

**Example:**
```
"HELLO WORLD" → "HE LX LO WO RL DX"
```

### Encryption Rules
For each digraph (A, B):

1. **Same Row**: Replace each with the letter to its right (wrap around)
   ```
   AB → CD (if A,B,C,D are consecutive in a row)
   ```

2. **Same Column**: Replace each with the letter below it (wrap around)
   ```
   A  → D
   B     E
   (A becomes D, B becomes E)
   ```

3. **Rectangle**: Swap columns - each letter is replaced by the letter in its row but in the other letter's column
   ```
   A . C    →    A . C
   . B .           . D .
   (A→C, B→D)
   ```

### Decryption Rules
Reverse of encryption:
1. **Same Row**: Shift left instead of right
2. **Same Column**: Shift up instead of down
3. **Rectangle**: Same as encryption (swap columns)

---

## Implementation Functions

### `create_playfair_matrix(key_word)`
Creates the 5×5 Playfair matrix from a keyword.

**Parameters:**
- `key_word`: The keyword for matrix generation

**Returns:** 2D list representing the 5×5 matrix

### `prepare_text(text)`
Prepares plaintext by:
- Converting to uppercase
- Replacing J with I
- Inserting X between repeated letters
- Padding with X if odd length

**Parameters:**
- `text`: The plaintext to prepare

**Returns:** Prepared text as digraph-ready string

### `find_position(matrix, char)`
Locates a character's position in the matrix.

**Parameters:**
- `matrix`: The 5×5 Playfair matrix
- `char`: Character to find

**Returns:** Tuple (row, column)

### `playfair_encrypt(plaintext, key_word)`
Encrypts plaintext using Playfair cipher rules.

### `playfair_decrypt(ciphertext, key_word)`
Decrypts ciphertext back to plaintext.

---

## Example Walkthrough

```
Key: PLAYFAIR
Matrix:
P L A Y F
I R B C D
E G H K M
N O Q S T
U V W X Z

Plaintext: "HELLO"

Step 1 - Prepare text: HE LX LO (inserted X between LL)

Step 2 - Encrypt each pair:
HE → Rectangle rule → RM
LX → Rectangle rule → YW  
LO → Same row → YA

Ciphertext: "RMYWYA"
```

---

## Complexity Analysis

- **Time Complexity**: O(n) where n is plaintext length
- **Space Complexity**: O(1) for 25-cell matrix, O(n) for result

---

## Strengths & Weaknesses

### Strengths
- More secure than simple substitution ciphers
- Only 676 possible digraphs vs 26 single letters
- Resists simple frequency analysis
- No special equipment needed

### Weaknesses
- Still susceptible to digraph frequency analysis
- Adds 'X' characters which may alter word boundaries
- I/J ambiguity reduces alphabet effectiveness
- Not suitable for modern cryptographic needs

---

## Historical Significance

- Used by British forces in Boer War and WWI
- Adopted by Australians in WWI
- Used by American troops at Battle of Guadalcanal (WWII)
- Remained secure enough for military field use
- Eventually superseded by more complex systems (e.g., ADFGVX)

---

## Usage Example

```python
from playfair_cipher import playfair_encrypt, playfair_decrypt

text = "Hide the gold"
key = "PLAYFAIR"

encrypted = playfair_encrypt(text, key)
decrypted = playfair_decrypt(encrypted, key)

print(f"Original: {text}")
print(f"Encrypted: {encrypted}")
print(f"Decrypted: {decrypted}")
```

---

## Notes

1. **J/I Convention**: The 5×5 matrix can only hold 25 letters, so I and J share a cell
2. **Padding Character**: 'X' is traditionally used, though 'Q' or 'Z' are alternatives
3. **Digraph Limitation**: Always encrypts in pairs - odd-length messages require padding
