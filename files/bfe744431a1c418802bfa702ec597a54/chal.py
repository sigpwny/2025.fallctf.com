import time

with open('flag.txt') as f:
    FLAG = f.read().strip()


def show_bank(user):
    flag = FLAG if user == 'admin' else None
    while True:
        time.sleep(1)
        print(f'\nYou are logged in as {user}. What would you like to do?')
        action = input('1. Withdraw flag. 2. Deposit flag. 3. Leave.\nAction: ')
        if action == '1':
            if flag:
                print(f'Here is your flag: {flag}')
            else:
                print('Sorry, you currently don\'t have any flags.')
        elif action == '2':
            flag = input('Please enter your flag: ')
            print('Deposited.')
        elif action == '3':
            exit()
        else:
            print('Unknown action.')


def hint_password(pwd):
    pwd_chars = {}
    for c in pwd:
        pwd_chars[c] = pwd_chars.get(c, 0) + 1
    true_chars = {}
    for c in FLAG:
        true_chars[c] = true_chars.get(c, 0) + 1
    right = 0
    for i in range(min(len(pwd), len(FLAG))):
        if pwd[i] == FLAG[i]:
            right += 1
            pwd_chars[c] = pwd_chars.get(c, 0) - 1
            true_chars[c] = true_chars.get(c, 0) - 1
    wrong_place = 0
    for c in pwd_chars:
        wrong_place += min(pwd_chars.get(c, 0), true_chars.get(c, 0))
    print(f'The password is incorrect, but {right} characters are correct and in the right place, and {wrong_place} characters are in the wrong place.')


def main():
    print('Welcome to the flag bank, where you can withdraw flags.')
    while True:
        user = input('Please enter your username: ')
        pwd = input('Please enter your password: ')
        if user == 'admin':
            if FLAG == pwd:
                show_bank(user)
            else:
                hint_password(pwd)
        else:
            show_bank(user)


if __name__ == "__main__":
    main()
