def caesar_encrypt(plaintext, shift):
    """Encrypt plaintext using Caesar cipher with given shift."""
    result = ""
    for char in plaintext:
        if char.isupper():
            result += chr((ord(char) - 65 + shift) % 26 + 65)
        elif char.islower():
            result += chr((ord(char) - 97 + shift) % 26 + 97)
        else:
            result += char
    return result


def caesar_decrypt(ciphertext, shift):
    """Decrypt ciphertext using Caesar cipher with given shift."""
    return caesar_encrypt(ciphertext, 26 - shift)


if __name__ == "__main__":
    text = "Hello World"
    key = 3

    encrypted = caesar_encrypt(text, key)
    decrypted = caesar_decrypt(encrypted, key)

    print(f"Original: {text}")
    print(f"Encrypted (shift={key}): {encrypted}")
    print(f"Decrypted: {decrypted}")
