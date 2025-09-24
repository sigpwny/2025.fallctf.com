#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setup() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
}

void print_flag() {
    char c;
    FILE *f = fopen("flag.txt", "r");
    while ((c = fgetc(f)) != EOF) {
        putc(c, stdout);
    }
}

int main() {
    setup();

    // \xXX represents a byte with hex value XX
    // this is difficult to enter directly into the terminal - use pwntools instead!
    const char *password = "\xde\xad\xbe\xef";

    puts("Welcome! Enter the password to get the flag:");

    printf("> ");

    char input[5];
    memset(input, 0, 5);
    fgets(input, 5, stdin);

    if (memcmp(input, password, 5) == 0) { 
        puts("You win! Here's the flag:");
        print_flag();
    } else {
        puts("Wrong password!");
        printf("You entered: ");
        for (int i = 0; i < 4; i++) {
            printf("\\x%02hhx", input[i]);
        }
    }

    return 0;
}

                                                 
                                                                                        