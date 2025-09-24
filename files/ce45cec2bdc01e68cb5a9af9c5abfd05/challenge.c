#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void setup();
void print_stack(char *name_addr);
                                                

const char *logo = "\n"
"  /$$$$$$   /$$$$$$  /$$$$$$$$       /$$$$$$    \n"
" /$$__  $$ /$$__  $$|__  $$__/      |_  $$_/    \n"
"| $$  \\ $$| $$  \\__/   | $$           | $$      \n"
"| $$$$$$$$| $$         | $$           | $$      \n"
"| $$__  $$| $$         | $$           | $$      \n"
"| $$  | $$| $$    $$   | $$           | $$      \n"
"| $$  | $$|  $$$$$$/   | $$          /$$$$$$ /$$\n"
"|__/  |__/ \\______/    |__/         |______/|__/\n";

void vuln() {
    char input[56]; 

    puts("Here's what the stack looks like before your input:");
    print_stack(input);

    printf("Your payload will be stored at %p\n", &input); // this address might be helpful!
    printf("> ");

    // We've completely removed print_flag... what can you do to get a flag yourself?
    gets(input);

    puts("Here's what the stack looks like after your input:");
    print_stack(input);
}

int main() {
    setup();
    puts(logo);
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