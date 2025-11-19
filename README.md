

Code : Human Made
README : AI generated under my guidance

--- 
# Hadex Shell

### 0. Demonstration

<div style="text-align: center;">
 <img src="./images/inaction.png" alt="No stress :)" width="800" />
</div>


### 1. General information

-   **Name of the project**: Hadex Shell
-   **Type of the project**: Having Fun and Learning 
-   **Main Language(s) of the project**: C
-   **Goal of this project**: My goal for this project was to build a basic Unix shell from scratch. This was primarily a learning exercise to better understand process management, command parsing, and the internal workings of a command-line interpreter.
-   **Scope of this project**: This project is currently a proof of concept. It implements a basic Read-Eval-Print Loop (REPL) that can read user input, distinguish between a few built-in commands (`cd`, `exit`, `help`) and external Unix commands, and execute them. It relies on a custom dynamic string library that I wrote as a foundation.
-   **Why**: Curious about how shell works !
-   **Compatibility**: The shell is built using standard C and relies on POSIX/UNIX system calls like `fork`, `execvp`, and `waitpid`. It is designed to be compiled and run on Linux-based systems. You will need `gcc` and `make` to build the project from the source.

### 2. Project

I designed this shell with a modular approach, separating the different stages of command processing into their own components. The entire process is built on top of my own simple, from-scratch dynamic string (`MyString`) and string list (`MyStringList`) libraries.

The main execution flow follows a classic shell architecture:

1.  **Read**: In the main loop (`my_repl.c`), the shell prints a prompt and uses `getline` to read a full line of input from the user.

2.  **Parse (Split & Tokenize)**: The raw input string is then passed to the tokenizer (`my_tokenizer.c`). I first use a `my_splitter` function to break the input line into a list of words based on spaces.

3.  **Evaluate (Tokenize & Classify)**: The resulting list of words is then tokenized. I check the first word in the list against a hardcoded set of built-in commands.
    -   If it matches a command like "cd" or "exit", it's classified as a `BUILTIN_COMMAND`.
    -   If not, it's assumed to be an external `UNIX_COMMAND`.
    -   All subsequent words are classified as `USER_ARGS`.
    This process creates a list of tokens, each containing the string value and its type.

4.  **Execute**: The `my_execute` function takes the list of tokens and decides how to run the command.
    -   For **built-in commands**, it calls a dedicated function (`my_builtin_execute`) that runs directly within the main shell process. This is necessary for commands like `cd` that need to change the state of the shell itself.
    -   For **external commands**, it uses the standard `fork()` and `execvp()` model. A child process is created, which then replaces its own process image with the command specified by the user. The parent shell process waits for the child to complete before printing the next prompt.

As this is an early version, the parsing and execution logic are quite simple, but they form a solid foundation for future improvements.

### 3. How to run the project :

To compile and run this project, you will need `make` and `gcc` installed on your system.

1.  Navigate to the `src` directory where the `makefile` is located:
    ```sh
    cd src
    ```

2.  To compile and run the shell in one step, use the `run` target in the makefile:
    ```sh
    make run
    ```
    This command will compile all the source files into an executable named `hadex` inside the `bin` directory and then immediately start the shell.

3.  If you only want to compile the program, you can simply run:
    ```sh
    make
    ```

4.  To compile with debugging symbols and launch the `gdb` debugger, use:
    ```sh
    make debug
    ```
