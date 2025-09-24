#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void setup();
void print_stack(char *input_addr);


const char *pwn3 = "\n"
"___  ___            _        __  _____  _____ \n"
"|  \\/  |           (_)      /  ||  _  ||____ |\n"
"| .  . | __ _  __ _ _  ___  `| || |/' |    / /\n"
"| |\\/| |/ _` |/ _` | |/ __|  | ||  /| |    \\ \\\n"
"| |  | | (_| | (_| | | (__  _| |\\ |_/ /.___/ /\n"
"\\_|  |_/\\__,_|\\__, |_|\\___| \\___/\\___/ \\____/\n"
"               __/ |                        \n"
"              |___/                          \n";                    




void print_flag() {
    // bypasses some features in glibc to make your exploit easier
    __asm__("sub $0x8, %rsp");

    char c;
    FILE *f = fopen("flag.txt", "r");
    while ((c = fgetc(f)) != EOF) {
        putc(c, stdout);
    }
}

void vuln() {
    char input[64]; 

    puts("Here's what the stack looks like before your input:");
    print_stack(input);

    puts("Welcome to Magic 103. This next trick is called 'ret2win'");
    printf("> ");

    // we don't call print_flag for you anymore. is there a way you can call it yourself?
    // read the pwn guides!
    gets(input);

    puts("Here's what the stack looks like after your input:");
    print_stack(input);
}

int main() {
    setup();
    puts(pwn3);
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
void print_stack(char *input_addr) {
    // get return address of previous frame
    char **rbp;
    __asm__("movq %%rbp, %0" : "=r"(rbp));
    char *prev_rbp = *rbp;
    char *return_addr = prev_rbp + 8;

    uint64_t *stack = (uint64_t *)input_addr;
    printf("\n");
    puts("+--------------------------------------------------------------+");
    for (int i = 0; i < 10; i++) {
        
        printf("|   %p: ", &stack[i]);
        for (int j = 0; j < 8; j++) {
            printf("%02hhx ", ((char *)&stack[i])[j]);
        }
      
        if ((char *)&stack[i] == input_addr) {
            printf("%-18s", "<-- input");
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