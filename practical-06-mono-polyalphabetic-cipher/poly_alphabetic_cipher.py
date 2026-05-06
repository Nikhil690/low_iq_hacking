import string


def create_monoalphabetic_key(key_word):
    """Create a monoalphabetic substitution key from a keyword."""
    key_word = key_word.upper().replace(" ", "")
    seen = []
    for char in key_word:
        if char not in seen:
            seen.append(char)

    alphabet = string.ascii_uppercase
    remaining = [c for c in alphabet if c not in seen]
    return seen + remaining


def monoalphabetic_encrypt(plaintext, key_word):
    """Encrypt using monoalphabetic substitution with keyword-based key."""
    key_map = create_monoalphabetic_key(key_word)
    normal = string.ascii_uppercase

    result = ""
    for char in plaintext:
        if char.isupper():
            idx = normal.index(char)
            result += key_map[idx]
        elif char.islower():
            idx = normal.index(char.upper())
            result += key_map[idx].lower()
        else:
            result += char
    return result


def monoalphabetic_decrypt(ciphertext, key_word):
    """Decrypt using monoalphabetic substitution with keyword-based key."""
    key_map = create_monoalphabetic_key(key_word)
    normal = string.ascii_uppercase

    result = ""
    for char in ciphertext:
        if char.isupper():
            idx = key_map.index(char)
            result += normal[idx]
        elif char.islower():
            idx = key_map.index(char.upper())
            result += normal[idx].lower()
        else:
            result += char
    return result


def vigenere_encrypt(plaintext, keyword):
    """Encrypt using Vigenère cipher (polyalphabetic substitution)."""
    keyword = keyword.upper().replace(" ", "")
    result = ""
    key_index = 0

    for char in plaintext:
        if char.isalpha():
            shift = ord(keyword[key_index % len(keyword)]) - 65
            if char.isupper():
                result += chr((ord(char) - 65 + shift) % 26 + 65)
            else:
                result += chr((ord(char) - 97 + shift) % 26 + 97)
            key_index += 1
        else:
            result += char
    return result


def vigenere_decrypt(ciphertext, keyword):
    """Decrypt using Vigenère cipher (polyalphabetic substitution)."""
    keyword = keyword.upper().replace(" ", "")
    result = ""
    key_index = 0

    for char in ciphertext:
        if char.isalpha():
            shift = ord(keyword[key_index % len(keyword)]) - 65
            if char.isupper():
                result += chr((ord(char) - 65 - shift) % 26 + 65)
            else:
                result += chr((ord(char) - 97 - shift) % 26 + 97)
            key_index += 1
        else:
            result += char
    return result


if __name__ == "__main__":
    text = "Hello World"
    mono_key = "CRYPTO"
    poly_key = "KEY"

    print("=== Monoalphabetic Cipher ===")
    encrypted_mono = monoalphabetic_encrypt(text, mono_key)
    decrypted_mono = monoalphabetic_decrypt(encrypted_mono, mono_key)
    print(f"Original: {text}")
    print(f"Key word: {mono_key}")
    print(f"Encrypted: {encrypted_mono}")
    print(f"Decrypted: {decrypted_mono}")

    print("\n=== Polyalphabetic Cipher (Vigenère) ===")
    encrypted_poly = vigenere_encrypt(text, poly_key)
    decrypted_poly = vigenere_decrypt(encrypted_poly, poly_key)
    print(f"Original: {text}")
    print(f"Keyword: {poly_key}")
    print(f"Encrypted: {encrypted_poly}")
    print(f"Decrypted: {decrypted_poly}")
