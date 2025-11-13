#include <string.h>
#include <stdio.h>

void f1(char *str) {
    char buffer[6]; // 6 bytes including the null terminator '\0'
    strcpy(buffer, str);
    printf("%s\n", buffer);
}

void main(int argc, char *argv[]) {
    f1(argv[1]);
}

/*
GCC compiler provides stack protection, so if you compile this code when the
protection is enabled, stack overflow will not be occured. Instead, you will see
a stack smashing message, because protector terminates the program before stack
overflow and prints stack smashing error message. For example
CLI: gcc stack_overflow.c -o stack_overflow
CLI: ./stack_overflow Shakil_
Output:
Shakil_
*** stack smashing detected ***: terminated
Aborted (core dumped)

If you want to see a stack overflow, disable the protector using -fno-stack-protector
CLI: gcc stack_overflow.c -fno-stack-protector -o stack_overflow
CLI: ./stack_overflow Shakil_
Output:
Shakil_
Segmentation fault (core dumped)
*/