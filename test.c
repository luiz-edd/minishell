#include <stdio.h>
#include <readline/readline.h>

int main() {
    char *input = readline("Enter some text: ");
    printf("You entered: %s\n", input);
    return 0;
}
