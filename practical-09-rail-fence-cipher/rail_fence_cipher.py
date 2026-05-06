def rail_fence_encrypt(plaintext, rails):
    """Encrypt plaintext using Rail Fence transposition cipher."""
    if rails <= 1 or len(plaintext) <= rails:
        return plaintext

    fence = [[] for _ in range(rails)]
    rail = 0
    direction = 1

    for char in plaintext:
        fence[rail].append(char)

        if rail == 0:
            direction = 1
        elif rail == rails - 1:
            direction = -1

        rail += direction

    result = ""
    for row in fence:
        result += "".join(row)

    return result


def rail_fence_decrypt(ciphertext, rails):
    """Decrypt ciphertext from Rail Fence transposition cipher."""
    if rails <= 1 or len(ciphertext) <= rails:
        return ciphertext

    n = len(ciphertext)
    fence = [[0] * n for _ in range(rails)]

    rail = 0
    direction = 1
    for i in range(n):
        fence[rail][i] = 1

        if rail == 0:
            direction = 1
        elif rail == rails - 1:
            direction = -1

        rail += direction

    chars_index = 0
    for r in range(rails):
        for c in range(n):
            if fence[r][c] == 1:
                fence[r][c] = ciphertext[chars_index]
                chars_index += 1

    result = ""
    rail = 0
    direction = 1
    for i in range(n):
        result += fence[rail][i]

        if rail == 0:
            direction = 1
        elif rail == rails - 1:
            direction = -1

        rail += direction

    return result


if __name__ == "__main__":
    text = "HELLO WORLD"
    key = 3

    encrypted = rail_fence_encrypt(text, key)
    decrypted = rail_fence_decrypt(encrypted, key)

    print(f"Original: {text}")
    print(f"Rails: {key}")
    print(f"Encrypted: {encrypted}")
    print(f"Decrypted: {decrypted}")
