#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void setup();
void print_stack(char *input_addr, char *number_addr);

const char *pwn2 = "\n"
"___  ___            _        __  _____  _____ \n"
"|  \\/  |           (_)      /  ||  _  |/ __  \\\n"
"| .  . | __ _  __ _ _  ___  `| || |/' |`' / /'\n"
"| |\\/| |/ _` |/ _` | |/ __|  | ||  /| |  / /  \n"
"| |  | | (_| | (_| | | (__  _| |\\ |_/ /./ /___\n"
"\\_|  |_/\\__,_|\\__, |_|\\___| \\___/\\___/ \\_____/\n"
"               __/ |                        \n"
"              |___/                          \n";                         



void print_flag() {
    char c;
    FILE *f = fopen("flag.txt", "r");
    while ((c = fgetc(f)) != EOF) {
        putc(c, stdout);
    }
}

void vuln() {
    // In memory, you'll see this as:
    //      ef cd ab 90 78 56 34 12
    // It looks kinda backwards because this system is little-endian (less significant bytes go first in memory).
    // Read more about endianness here: https://en.wikipedia.org/wiki/Endianness
    uint64_t number = 0x1234567890abcdef; // change this to 0xfedcba0987654321 to win!
    char input[56]; 

    puts("Here's what the stack looks like before your input:");
    print_stack(input, (char *)&number);

    puts("Welcome to Magic 102. I made it a bit harder this time :)");
    printf("> ");

    // This is a dangerous function! It doesn't check the size of the input.
    // What happens if we send (a lot) more than 56 characters?
    gets(input);

    puts("Here's what the stack looks like after your input:");
    print_stack(input, (char *)&number);

    if (number == 0xfedcba0987654321) {
        puts("You win! Here's the flag:");
        print_flag();
    } else {
        puts("I see no magic here... Try again.");
    }     
}

int main() {
    setup();
    puts(pwn2);
    vuln();
    return 0;                                                            
}





/**
* You can ignore everything below this
*/

// Just to make things work over the network
void setup() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
}

// Creates a visual representation of the stack
void print_stack(char *input_addr, char *number_addr) {
    // get return address of previous frame
    char **rbp;
    __asm__("movq %%rbp, %0" : "=r"(rbp));
    char *prev_rbp = *rbp;
    char *return_addr = prev_rbp + 8;

    uint64_t *stack = (uint64_t *)input_addr;
    printf("\n");
    puts("+--------------------------------------------------------------+");
    for (int i = 0; i < 8; i++) {
        
        printf("|   %p: ", &stack[i]);
        for (int j = 0; j < 8; j++) {
            printf("%02hhx ", ((char *)&stack[i])[j]);
        }

        if ((char *)&stack[i] == input_addr) {
            printf("%-18s", "<-- input");
        } else if ((char *)&stack[i] == number_addr) {
            printf("%-18s", "<-- number");
        } else if ((char *)&stack[i] == return_addr) {
            printf("%-18s", "<-- return address");
        } else {
            printf("%18s", "");
        }

        printf(" |\n");
    }
    puts("+--------------------------------------------------------------+");
    printf("\n");
}