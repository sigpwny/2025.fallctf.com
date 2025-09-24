#include <stdio.h>
#include <stdlib.h>

void setup();
                                   

const char *logo = "\n"
" /$$$$$$   /$$$$$$  /$$$$$$$$       /$$$$$$ /$$$$$$ /$$$$$$    \n"
" /$$__  $$ /$$__  $$|__  $$__/      |_  $$_/|_  $$_/|_  $$_/    \n"
"| $$  \\ $$| $$  \\__/   | $$           | $$    | $$    | $$      \n"
"| $$$$$$$$| $$         | $$           | $$    | $$    | $$      \n"
"| $$__  $$| $$         | $$           | $$    | $$    | $$      \n"
"| $$  | $$| $$    $$   | $$           | $$    | $$    | $$      \n"
"| $$  | $$|  $$$$$$/   | $$          /$$$$$$ /$$$$$$ /$$$$$$ /$$\n"
"|__/  |__/ \\______/    |__/         |______/|______/|______/|__/\n";



void vuln() {
    char input[32];

    printf("Prove yourself.\n");
    printf("> ");

    fgets(input, 80, stdin);
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