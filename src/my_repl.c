#include "./my_repl.h"
#include "lib/my_string.h"
#include "my_list_string.h"
#include "my_tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

MyString read_line(void)
{
    MyString user_input = my_new_string("");
    char *buffer = NULL;
    size_t buffer_size = 1;
    getline(&buffer, &buffer_size, stdin);
    my_append_literal(&user_input, buffer);
    user_input.string_proper[user_input.size - 1] = '\0';
    user_input.size--;
    return user_input;
}

u8 my_builtin_execute(MyString *command, MyStringList *args)
{
    if (my_compare_literals(command->string_proper, "cd"))
    {
        if (args->size == 0)
        {
            chdir("/home/anasr/"); // HARD CODED
        }
        else
        {
            if (chdir(args[0].body->string_proper) == -1)
            {
                printf("%s was not found.\n", args[0].body->string_proper);
            };
        }
    }
    if (my_compare_literals(command->string_proper, "help"))
    {
        printf("/================================================================================================\\\n");
        printf("|                                                                                                |\n");
        printf(
            "|  ░██     ░██                   ░██                         ░██████   ░██                   ░██ ░██ |\n");
        printf(
            "|  ░██     ░██                   ░██                        ░██   ░██  ░██                   ░██ ░██ |\n");
        printf(
            "|  ░██     ░██  ░██████    ░████████  ░███████  ░██    ░██ ░██         ░████████   ░███████  ░██ ░██ |\n");
        printf(
            "|  ░██████████       ░██  ░██    ░██ ░██    ░██  ░██  ░██   ░████████  ░██    ░██ ░██    ░██ ░██ ░██ |\n");
        printf(
            "|  ░██     ░██  ░███████  ░██    ░██ ░█████████   ░█████           ░██ ░██    ░██ ░█████████ ░██ ░██ |\n");
        printf(
            "|  ░██     ░██ ░██   ░██  ░██   ░███ ░██         ░██  ░██   ░██   ░██  ░██    ░██ ░██        ░██ ░██ |\n");
        printf(
            "|  ░██     ░██  ░█████░██  ░█████░██  ░███████  ░██    ░██   ░██████   ░██    ░██  ░███████  ░██ ░██ |\n");
        printf("|                                                                                                |\n");
        printf("|------------------------------------------------------------------------------------------------|\n");
        printf("|  Hello !                                                                                       |\n");
        printf("|  This is my Unix Shell called Hadex Shell.                                                     |\n");
        printf("|  Don't know why would you use this shell                                                       |\n");
        printf("|  Maybe I became famous :o                                                                      |\n");
        printf("|  Love---Anas                                                                                   |\n");
        printf("\\================================================================================================/\n");
    }
    if (my_compare_literals(command->string_proper, "exit"))
    {
        exit(0);
    }
    return EXIT_SUCCESS;
}

u8 my_execute(MyTokenList *token_list)
{
    u8 size = token_list->size;
    char *args[size + 1];
    MyString built_in_command;
    u8 built_in_mode = 0;
    for (int i = 0; i < size; i++)
    {
        if (token_list->data[i].token_type == BUILTIN_COMMAND)
        {
            built_in_command = token_list->data[i].string;
            built_in_mode = 1;
        }
        else if (token_list->data[i].token_type == UNIX_COMMAND)
        {
            args[0] = token_list->data[i].string.string_proper;
        }
        else
        {
            args[i] = token_list->data[i].string.string_proper;
        }
    }
    args[size] = NULL;
    if (built_in_mode == 1)
    {
        MyStringList *built_in_args = my_strlist_new();

        for (int i = 1; i < size; i++)
        {
            my_strlist_append_literal(built_in_args, args[i]);
        }
        my_builtin_execute(&built_in_command, built_in_args);
        free(built_in_args);
    }
    else
    {
        pid_t pid;
        pid = fork();
        if (pid == 0)
        {
            if (execvp(args[0], args) == -1)
            {
                printf("%s was not found.\n", args[0]);
            };
        }
        else
        {
            pid_t wpid = waitpid(pid, NULL, WUNTRACED);
        }
    }
    return 0;
}
