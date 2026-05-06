import string


def create_key_matrix(key, size):
    """Create n×n key matrix from keyword."""
    key = key.upper().replace(" ", "")

    while len(key) < size * size:
        key += key[len(key) % size :]

    matrix = []
    for i in range(size):
        row = []
        for j in range(size):
            idx = i * size + j
            if idx < len(key) and key[idx] in string.ascii_uppercase:
                row.append(ord(key[idx]) - 65)
            else:
                row.append(0)
        matrix.append(row)
    return matrix


def mod_inverse_26(a):
    """Find modular multiplicative inverse of a modulo 26."""
    for i in range(1, 26):
        if (a * i) % 26 == 1:
            return i
    return 1


def determinant_2x2(matrix):
    """Calculate determinant of 2x2 matrix mod 26."""
    det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26
    return det


def invert_key_matrix_2x2(matrix):
    """Calculate inverse of 2x2 key matrix mod 26."""
    a, b = matrix[0][0], matrix[0][1]
    c, d = matrix[1][0], matrix[1][1]

    det = (a * d - b * c) % 26
    det_inv = mod_inverse_26(det)

    inv = [
        [(d * det_inv) % 26, ((-b) * det_inv) % 26],
        [((-c) * det_inv) % 26, (a * det_inv) % 26],
    ]

    return [[x % 26 for x in row] for row in inv]


def matrix_multiply_2x2(matrix, vector):
    """Multiply 2x2 matrix by 2-element vector mod 26."""
    result = [0, 0]
    for i in range(2):
        total = 0
        for j in range(2):
            total += matrix[i][j] * vector[j]
        result[i] = total % 26
    return result


def hill_encrypt(plaintext, key):
    """Encrypt plaintext using Hill cipher with 2x2 key matrix."""
    plaintext = plaintext.upper().replace(" ", "").replace("J", "I")

    while len(plaintext) % 2 != 0:
        plaintext += "X"

    key_matrix = create_key_matrix(key, 2)

    result = ""
    for i in range(0, len(plaintext), 2):
        vec = [ord(plaintext[i]) - 65, ord(plaintext[i + 1]) - 65]
        encrypted_vec = matrix_multiply_2x2(key_matrix, vec)

        result += chr(encrypted_vec[0] + 65)
        result += chr(encrypted_vec[1] + 65)

    return result


def hill_decrypt(ciphertext, key):
    """Decrypt ciphertext using Hill cipher with 2x2 key matrix."""
    ciphertext = ciphertext.upper().replace(" ", "")

    key_matrix = create_key_matrix(key, 2)
    inv_key_matrix = invert_key_matrix_2x2(key_matrix)

    result = ""
    for i in range(0, len(ciphertext), 2):
        vec = [ord(ciphertext[i]) - 65, ord(ciphertext[i + 1]) - 65]
        decrypted_vec = matrix_multiply_2x2(inv_key_matrix, vec)

        result += chr(decrypted_vec[0] + 65)
        result += chr(decrypted_vec[1] + 65)

    return result


if __name__ == "__main__":
    text = "ACT"
    key = "BCAD"

    encrypted = hill_encrypt(text, key)
    decrypted = hill_decrypt(encrypted, key)

    print(f"Original: {text}")
    print(f"Key: {key}")
    print(f"Encrypted: {encrypted}")
    print(f"Decrypted: {decrypted}")
