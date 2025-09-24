
import os, sys, random
from Crypto.Cipher import AES

N = 32               
BLOCKLEN = 16
KEY = os.urandom(16)

def xor_bytes(a, b): return bytes(x ^ y for x, y in zip(a, b))

def aes_eceb_encrypt(m: bytes) -> bytes:
    aes = AES.new(KEY, AES.MODE_ECB)
    all_c0 = aes.encrypt(m)
    c0 = [ all_c0[i*BLOCKLEN:(i+1)*BLOCKLEN] for i in range(len(all_c0)//BLOCKLEN) ]
    n = len(c0)
    C = []
    for i in range(1, n+1):                
        cur = bytearray(c0[i-1])
        for j in range(1, i):
            if i % j == 0:
                cur = xor_bytes(cur, c0[j - 1])
        C.append(bytes(cur))
    return b"".join(C)

if __name__ == '__main__':
    m = os.urandom(N * BLOCKLEN)
    C = aes_eceb_encrypt(m)

    m_blocks = [m[i * BLOCKLEN: (i + 1) * BLOCKLEN] for i in range(N)]
    random.shuffle(m_blocks)
    challenge = b"".join(m_blocks)

    with open('challenge.txt', 'w') as f:
        f.write(f'm = {m.hex()}\n')
        f.write(f'aes_eceb_encrypt(m) = {C.hex()}\n')
        f.write(f'challenge = {challenge.hex()}\n',)
    
    print(aes_eceb_encrypt(challenge).hex())