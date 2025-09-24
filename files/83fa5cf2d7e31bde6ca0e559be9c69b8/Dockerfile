# Set OS
FROM ubuntu:20.04

# Install dependencies
# according to docker, apt isnt stable in CLI, so use apt-get.
RUN apt-get update && apt-get install -y socat gcc-multilib python3 && apt-get install make
RUN rm -rf /var/lib/apt/lists/*

# Initialize User
RUN mkdir -p /usr/src/pwn
WORKDIR /usr/src/pwn
RUN cd /usr/src/pwn/

# Copy flag
COPY flag.txt .
RUN chmod 444 flag.txt

# Set up pwn user
RUN adduser pwn

# Copy and build challenge
COPY challenge.c .
COPY Makefile .
RUN make
RUN chmod 111 challenge
RUN rm challenge.c

# Run and expose challenge
USER pwn
CMD socat -T60 TCP-LISTEN:1337,fork,reuseaddr EXEC:"./challenge"