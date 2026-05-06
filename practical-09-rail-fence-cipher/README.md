# Practical 9: Rail Fence Cipher

## Overview
The Rail Fence cipher is a simple transposition cipher that rearranges plaintext by writing it in a zig-zag pattern across multiple "rails" (rows) and then reading off the letters row by row. The name comes from the visual appearance resembling a wooden rail fence.

---

## Algorithm Details

### How It Works

1. **Writing Phase**: Write the plaintext diagonally down and up across a specified number of rails
2. **Reading Phase**: Read the characters horizontally, row by row
3. **Key**: The number of rails used determines the encryption strength

### Encryption Process

**Example with 3 rails and "HELLO WORLD":**

```
Step 1 - Write in zig-zag pattern:

H . . . O . . . L .
. E . L . W . R . D
. . L . . . O . . .

Rail 0: H   O   L
Rail 1:  E L W R D
Rail 2:   L   O

Step 2 - Read row by row:
Row 0: HO L
Row 1: ELWRD  
Row 2: LO

Ciphertext: "HOLELW RDLO" → "HOLELWRDLO"
```

### Decryption Process

1. Determine the pattern of characters per rail
2. Fill each rail with the appropriate portion of ciphertext
3. Read in zig-zag order to recover plaintext

**Visual reconstruction:**
```
Ciphertext: "HOLELWRDLO" (10 chars, 3 rails)

Step 1 - Calculate positions:
Rail 0: H . . . O . . . L .  (positions 0, 4, 8)
Rail 1: . E . L . W . R . D  (positions 1, 3, 5, 7, 9)
Rail 2: . . L . . . O . . .  (positions 2, 6)

Step 2 - Fill with ciphertext:
H . . . O . . . L .
. E . L . W . R . D
. . L . . . O . . .

Step 3 - Read zig-zag:
H → E → L → L → O → (up) → W → R → D → (down) → ...
Result: "HELLOWORLD"
```

---

## Mathematical Pattern

For `r` rails and message length `n`:

**Period**: The pattern repeats every `2(r - 1)` characters

- Top rail (rail 0): Characters at positions `i * period`
- Bottom rail (rail r-1): Characters at positions `(period/2) + i * period`
- Middle rails: Two interleaved sequences

---

## Implementation Functions

### `rail_fence_encrypt(plaintext, rails)`
Encrypts plaintext using Rail Fence transposition cipher.

**Parameters:**
- `plaintext`: The text to encrypt (string)
- `rails`: Number of rails/rows for the zig-zag pattern (integer ≥ 2)

**Returns:** Encrypted ciphertext (string)

**Algorithm:**
1. Create empty lists for each rail
2. Traverse plaintext character by character
3. Place each character on the current rail
4. Change direction at top and bottom rails
5. Concatenate all rails to form ciphertext

### `rail_fence_decrypt(ciphertext, rails)`
Decrypts Rail Fence ciphertext back to plaintext.

**Parameters:**
- `ciphertext`: The encrypted text (string)
- `rails`: Number of rails used in encryption (integer ≥ 2)

**Returns:** Decrypted plaintext (string)

**Algorithm:**
1. Mark positions where characters would be placed on each rail
2. Fill marked positions with ciphertext characters row by row
3. Read characters following the zig-zag pattern

---

## Example Walkthrough

```python
from rail_fence_cipher import rail_fence_encrypt, rail_fence_decrypt

text = "WEAREDISCOVEREDFLEEATONCE"
key = 3

# Encryption visualization:
W . . . E . . . C . . . R . . . L . . . T . . . E
. E . R . D . S . O . V . E . F . L . E . A . O . N
. . A . . . I . . . V . . . D . . . E . . . E . . . C

# Rails read:
Rail 0: WECRLTE
Rail 1: ERDSOEF EAON
Rail 2: AIVDEEC

Ciphertext: "WECRLTIERDSOEFEAONAIVDEEC"

# Decryption reverses this process
```

---

## Complexity Analysis

### Time Complexity
- **Encryption**: O(n) where n is plaintext length
- **Decryption**: O(n) for pattern marking + O(n) for filling = O(n)

### Space Complexity
- **Encryption**: O(n × r) for the fence structure (r = rails)
- **Decryption**: O(n × r) for the temporary matrix

---

## Strengths & Weaknesses

### Strengths
- **Simple implementation**: Easy to understand and execute manually
- **No character substitution**: Preserves original letter frequencies
- **Variable key space**: Number of rails provides flexibility (2 to n/2)
- **Good for puzzles**: Popular in cryptography challenges

### Weaknesses
- **Weak security**: Only rearranges letters, doesn't substitute
- **Frequency analysis**: Letter frequencies remain unchanged
- **Pattern detection**: Regular zig-zag pattern is easy to recognize
- **Limited key space**: Practical rail counts are small (2-10)

---

## Key Space Analysis

For a message of length n:
- Minimum rails: 2
- Maximum useful rails: approximately n/2
- Total possible keys: ~(n/2 - 1) values

**Example:** For "HELLO" (5 characters):
- Valid rail counts: 2, 3, 4
- Only 3 possible encryption variations

---

## Variations

### 1. Wrapping Rail Fence
The pattern continues beyond the bottom rail and wraps to top.

### 2. Columnar Rail Fence
After creating the zig-zag, read columns instead of rows.

### 3. Keyed Rail Fence
Use a keyword to determine rail order instead of sequential reading.

---

## Historical Context

- Originated from the physical design of wooden fences
- Used for simple message obfuscation in telegraph communications
- Popular in Victorian-era secret writing
- Still used in puzzle competitions and CTF challenges

---

## Usage Example

```python
from rail_fence_cipher import rail_fence_encrypt, rail_fence_decrypt

text = "THE QUICK BROWN FOX"
key = 4

encrypted = rail_fence_encrypt(text, key)
decrypted = rail_fence_decrypt(encrypted, key)

print(f"Original: {text}")
print(f"Rails: {key}")
print(f"Encrypted: {encrypted}")
print(f"Decrypted: {decrypted}")
```

---

## Practical Tips

1. **Choose rails wisely**: More rails = more mixing but harder to decrypt manually
2. **Remove spaces first**: Typically done before encryption for cleaner output
3. **Minimum 2 rails**: With 1 rail, text remains unchanged
4. **Diminishing returns**: Beyond ~6-8 rails, additional complexity adds little security
