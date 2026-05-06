def get_key_order(keyword):
    """Get column order based on alphabetical sorting of keyword."""
    keyword = keyword.upper().replace(" ", "")

    indexed = [(char, i) for i, char in enumerate(keyword)]
    sorted_indexed = sorted(indexed, key=lambda x: (x[0], x[1]))

    order = [0] * len(keyword)
    for new_pos, (_, old_pos) in enumerate(sorted_indexed):
        order[old_pos] = new_pos

    return order


def row_transposition_encrypt(plaintext, keyword):
    """Encrypt plaintext using Row Transposition cipher."""
    keyword = keyword.upper().replace(" ", "")
    key_len = len(keyword)

    padding_needed = (key_len - len(plaintext) % key_len) % key_len
    plaintext = plaintext + "X" * padding_needed

    rows = []
    for i in range(0, len(plaintext), key_len):
        rows.append(list(plaintext[i : i + key_len]))

    order = get_key_order(keyword)
    encrypted = ""

    for col_idx in range(key_len):
        original_col = order.index(col_idx)
        for row in rows:
            if col_idx < len(row):
                encrypted += row[original_col]

    return encrypted


def row_transposition_decrypt(ciphertext, keyword):
    """Decrypt ciphertext from Row Transposition cipher."""
    keyword = keyword.upper().replace(" ", "")
    key_len = len(keyword)
    num_rows = (len(ciphertext) + key_len - 1) // key_len

    order = get_key_order(keyword)

    grid = [[""] * key_len for _ in range(num_rows)]

    char_idx = 0
    sorted_cols = sorted(range(key_len), key=lambda x: (keyword[x], x))

    for new_col, original_col in enumerate(sorted_cols):
        for row in range(num_rows):
            if char_idx < len(ciphertext):
                grid[row][original_col] = ciphertext[char_idx]
                char_idx += 1

    plaintext = ""
    for row in grid:
        plaintext += "".join(row)

    return plaintext.rstrip("X")


if __name__ == "__main__":
    text = "ATTACK AT DAWN"
    key = "ZEBRAS"

    encrypted = row_transposition_encrypt(text, key)
    decrypted = row_transposition_decrypt(encrypted, key)

    print(f"Original: {text}")
    print(f"Key: {key}")
    print(f"Encrypted: {encrypted}")
    print(f"Decrypted: {decrypted}")
