#include "./lib/my_string.h"
#include "abreviations.h"
#include "my_list_string.h"
#include "my_repl.h"
#include "my_tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    u8 shell_state = 1;
    MyStringList *builtin_commands = my_strlist_new();
    my_strlist_append_literal(builtin_commands, "help");
    my_strlist_append_literal(builtin_commands, "cd");
    my_strlist_append_literal(builtin_commands, "exit");
    while (shell_state)
    {
        printf("$ > ");
        MyString user_input = read_line();
        MyStringList *list = my_splitter(user_input.string_proper, ' ');
        MyTokenList *token_list = my_tokenize_this(list, builtin_commands);
        my_execute(token_list);
        my_destroy_string(&user_input);
        free(list);
        free(token_list);
    }
    free(builtin_commands);

    return EXIT_SUCCESS;
}
