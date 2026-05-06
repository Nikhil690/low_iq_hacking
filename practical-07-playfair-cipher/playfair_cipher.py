import string


def create_playfair_matrix(key_word):
    """Create 5x5 Playfair matrix from keyword."""
    key_word = key_word.upper().replace(" ", "").replace("J", "I")
    seen = []

    for char in key_word:
        if char not in seen and char in string.ascii_uppercase:
            seen.append(char)

    for char in string.ascii_uppercase:
        if char not in seen and char != "J":
            seen.append(char)

    matrix = [seen[i : i + 5] for i in range(0, 25, 5)]
    return matrix


def prepare_text(text):
    """Prepare plaintext by adding X between repeated letters and padding."""
    text = text.upper().replace(" ", "").replace("J", "I")
    prepared = ""

    i = 0
    while i < len(text):
        prepared += text[i]
        if i + 1 < len(text):
            if text[i] == text[i + 1]:
                prepared += "X"
            else:
                prepared += text[i + 1]
                i += 1
        else:
            prepared += "X"
        i += 1

    return prepared


def find_position(matrix, char):
    """Find row and column of a character in the matrix."""
    for row in range(5):
        if char in matrix[row]:
            return row, matrix[row].index(char)
    return 0, 0


def playfair_encrypt(plaintext, key_word):
    """Encrypt plaintext using Playfair cipher."""
    matrix = create_playfair_matrix(key_word)
    prepared = prepare_text(plaintext)

    result = ""
    for i in range(0, len(prepared), 2):
        r1, c1 = find_position(matrix, prepared[i])
        r2, c2 = find_position(matrix, prepared[i + 1])

        if r1 == r2:
            result += matrix[r1][(c1 + 1) % 5]
            result += matrix[r2][(c2 + 1) % 5]
        elif c1 == c2:
            result += matrix[(r1 + 1) % 5][c1]
            result += matrix[(r2 + 1) % 5][c2]
        else:
            result += matrix[r1][c2]
            result += matrix[r2][c1]

    return result


def playfair_decrypt(ciphertext, key_word):
    """Decrypt ciphertext using Playfair cipher."""
    matrix = create_playfair_matrix(key_word)
    ciphertext = ciphertext.upper().replace(" ", "").replace("J", "I")

    result = ""
    for i in range(0, len(ciphertext), 2):
        r1, c1 = find_position(matrix, ciphertext[i])
        r2, c2 = find_position(matrix, ciphertext[i + 1])

        if r1 == r2:
            result += matrix[r1][(c1 - 1) % 5]
            result += matrix[r2][(c2 - 1) % 5]
        elif c1 == c2:
            result += matrix[(r1 - 1) % 5][c1]
            result += matrix[(r2 - 1) % 5][c2]
        else:
            result += matrix[r1][c2]
            result += matrix[r2][c1]

    return result


if __name__ == "__main__":
    text = "Hide the gold in the tree stump"
    key = "PLAYFAIR"

    encrypted = playfair_encrypt(text, key)
    decrypted = playfair_decrypt(encrypted, key)

    print(f"Original: {text}")
    print(f"Key: {key}")
    print(f"Encrypted: {encrypted}")
    print(f"Decrypted: {decrypted}")
