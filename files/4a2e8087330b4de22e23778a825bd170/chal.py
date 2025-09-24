from Crypto.PublicKey import RSA
# Verify((e, N), m, sigma) = sigma^e mod N = m?
# Sign((d, N), m) = m^d mod N

def setup():
    key = RSA.generate(2048)
    n = key.n
    e = key.e
    d = key.d
    with open('pk.txt', 'w') as f:
        f.write(str(n) + '\n' + str(e))
    return (n, d), (n, e)

def sign(sk, m):
    N, d = sk
    return pow(m, d, N)

def testing(sk):
    with open('signatures.txt', 'w') as f:
        for i in range(10, 20):
            f.write(str(sign(sk, i)) + '\n')

def sign_secret_message(sk):
    secret_message = 56430
    return sign(sk, secret_message)

if __name__ == '__main__':
    sk, vk = setup()
    testing(sk)
    secret_message_signature = sign_secret_message(sk)
    print(secret_message_signature)