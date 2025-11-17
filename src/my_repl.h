#ifndef MY_REPL_H
#define MY_REPL_H
#include "abreviations.h"
#include "lib/my_string.h"
#include "my_tokenizer.h"

MyString read_line(void);
u8 my_execute(MyTokenList *token_list);

#endif
