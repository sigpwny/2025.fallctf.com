import hashlib

nice_msg = input("Enter your friendly message: ")
mean_msg = input("Enter your mean message: ")

nice_hash = hashlib.sha256(nice_msg.encode()).hexdigest()
mean_hash = hashlib.sha256(mean_msg.encode()).hexdigest()

nice_start = "Happy birthday, Akhil!"
mean_start = "I hate you, Akhil!"

if not nice_msg.startswith(nice_start):
    print("Your nice message:", nice_msg, "did not start with:", nice_start)
    exit(1)
if not mean_msg.startswith(mean_start):
    print("Your mean message:", mean_msg, "did not start with:", mean_start)
    exit(1)

if nice_hash[-12:] != mean_hash[-12:]:
    print("Akhil's friend spotted a difference in your hashes:", nice_hash, "and", mean_hash)
    exit(1)

with open("flag.txt", "r") as f:
    print(f.read())
