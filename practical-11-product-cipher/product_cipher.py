import string


def caesar_encrypt(text, shift):
    """Apply Caesar cipher encryption."""
    result = ""
    for char in text:
        if char.isupper():
            result += chr((ord(char) - 65 + shift) % 26 + 65)
        elif char.islower():
            result += chr((ord(char) - 97 + shift) % 26 + 97)
        else:
            result += char
    return result


def caesar_decrypt(text, shift):
    """Apply Caesar cipher decryption."""
    return caesar_encrypt(text, 26 - shift)


def get_key_order(keyword):
    """Get column order based on alphabetical sorting of keyword."""
    keyword = keyword.upper().replace(" ", "")
    indexed = [(char, i) for i, char in enumerate(keyword)]
    sorted_indexed = sorted(indexed, key=lambda x: (x[0], x[1]))

    order = [0] * len(keyword)
    for new_pos, (_, old_pos) in enumerate(sorted_indexed):
        order[old_pos] = new_pos
    return order


def row_transposition_encrypt(text, keyword):
    """Apply Row Transposition encryption."""
    keyword = keyword.upper().replace(" ", "")
    key_len = len(keyword)

    padding_needed = (key_len - len(text) % key_len) % key_len
    text = text + "X" * padding_needed

    rows = []
    for i in range(0, len(text), key_len):
        rows.append(list(text[i : i + key_len]))

    order = get_key_order(keyword)
    encrypted = ""

    for col_idx in range(key_len):
        original_col = order.index(col_idx)
        for row in rows:
            if col_idx < len(row):
                encrypted += row[original_col]

    return encrypted


def row_transposition_decrypt(text, keyword):
    """Apply Row Transposition decryption."""
    keyword = keyword.upper().replace(" ", "")
    key_len = len(keyword)
    num_rows = (len(text) + key_len - 1) // key_len

    order = get_key_order(keyword)
    grid = [[""] * key_len for _ in range(num_rows)]

    char_idx = 0
    sorted_cols = sorted(range(key_len), key=lambda x: (keyword[x], x))

    for new_col, original_col in enumerate(sorted_cols):
        for row in range(num_rows):
            if char_idx < len(text):
                grid[row][original_col] = text[char_idx]
                char_idx += 1

    plaintext = ""
    for row in grid:
        plaintext += "".join(row)

    return plaintext.rstrip("X")


def product_encrypt(plaintext, caesar_shift, transposition_key):
    """Encrypt using Product cipher (Caesar + Row Transposition)."""
    step1 = caesar_encrypt(plaintext, caesar_shift)
    step2 = row_transposition_encrypt(step1, transposition_key)
    return step2


def product_decrypt(ciphertext, caesar_shift, transposition_key):
    """Decrypt Product cipher (reverse: Row Transposition + Caesar)."""
    step1 = row_transposition_decrypt(ciphertext, transposition_key)
    step2 = caesar_decrypt(step1, caesar_shift)
    return step2


if __name__ == "__main__":
    text = "SECRET MESSAGE"
    shift = 3
    key = "PYTHON"

    encrypted = product_encrypt(text, shift, key)
    decrypted = product_decrypt(encrypted, shift, key)

    print(f"Original: {text}")
    print(f"Caesar Shift: {shift}")
    print(f"Transposition Key: {key}")
    print(f"Encrypted: {encrypted}")
    print(f"Decrypted: {decrypted}")
