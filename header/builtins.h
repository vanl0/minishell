#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"

#define NOT_BUILTIN -1
#define ECHO 0
#define CD 1
#define PWD 2
#define EXPORT 3
#define UNSET 4
#define ENV 5
#define EXIT 6

// BUILTINS
int builtin_key(char *command);

#endif