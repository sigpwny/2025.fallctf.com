

# *** Import the pwntools library ***
# look at the guides for information on how to install pwntools
# or look at: https://docs.pwntools.com/en/stable/install.html
# If you are on Windows, install pwntools in WSL
from pwn import *

# *** Connect to the challenge instance ***
# if nc command is `nc <host> <port>`, then
# conn = remote(<host>, <port>)
conn = remote('chal.fallctf.com', 6000)

# to try your exploit locally, use process() instead!
# conn = process('./challenge') # local challenge file in the same directory

# *** Receive the prompt ***
# (receive text up until the point where we enter our input)
# Always use bytes (b'<string>')
conn.recvuntil(b'> ')

# *** Send the payload ***
# Use bytes (b'<string>') for this too!
conn.sendline(b'<your input here>')

# *** Interact with the challenge ***
# After sending the payload, we can go into interactive mode
# this will allow us to see the response from the challenge
# and interact with it further if necessary!
conn.interactive()


# read the pwntools guides for more information!


