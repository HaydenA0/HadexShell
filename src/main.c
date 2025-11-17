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

u8 my_execute(MyTokenList *token_list)
{
    u8 size = token_list->size;
    char *args[size + 1];
    for (int i = 0; i < size; i++)
    {
        if (token_list->data[i].token_type == UNIX_COMMAND)
        {
            args[0] = token_list->data[i].string.string_proper;
        }
        else
        {
            args[i] = token_list->data[i].string.string_proper;
        }
    }
    args[size] = NULL;
    pid_t pid;
    pid = fork();
    if (pid == 0)
    {
        execvp(args[0], args);
    }
    else
    {
        pid_t wpid = waitpid(pid, NULL, WUNTRACED);
    }

    return 0;
}

int main(void)
{
    while (1)
    {
        printf("shell_HX: \n$ ");
        MyString user_input = read_line();
        MyStringList *list = my_splitter(user_input.string_proper, ' ');
        MyTokenList *token_list = my_tokenize_this(list, NULL);

        my_execute(token_list);
    }

    return EXIT_SUCCESS;
}
