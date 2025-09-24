from Crypto.Cipher import AES
import secrets

key = secrets.token_bytes(6)
print("Encryption Key:", key.hex())

key0, key1 = b'\0' * 13 + key[:3], b'\0' * 13 + key[3:]
cipher0 = AES.new(key0, AES.MODE_ECB)
cipher1 = AES.new(key1, AES.MODE_ECB)

plain = b'pwnypwnypwnypwny'
mid = cipher0.encrypt(plain)
cipher = cipher1.encrypt(mid)

print("Cipher:", cipher.hex())
