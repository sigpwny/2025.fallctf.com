# flag is in a file: ./flag.txt
import string

def check_code(user_code):
    banned = ["open", "read", "'", '"']
    for keyword in banned:
        if keyword in user_code:
            return False 
        
    return True

print("I'll run your python code, just don't try to hack me :)")
user_code = input("> ")

if not check_code(user_code):
    print("Hey! I said don't hack me.")
    exit(1)

eval(user_code)
