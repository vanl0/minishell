# Minishell, building a shell

A demanding project at 42 School that, once completed, marks a significant improvement in programming skills. The premise is rather simple, create a program that recreates a shell, including its most commonly used features such as pipes, redirections, signals and built-ins using exclusively C language.

<img src="./minigif.gif" width="100%" height="100%"/>

This project takes a closer look at the functioning of the commands and interface we use everyday to move ourselves through the computer.

The work was divided into two main components: the lexer and the parser. The lexer is responsible for analyzing and validating the input provided by the user or from a file descriptor. It detects syntax errors, such as incorrect use of quotes (" or ') or other special symbols, and tokenizes the input into structured elements—typically separating the command from its arguments and redirections. This organization allows the parser to efficiently interpret and execute the commands, without worrying about low-level input validation.

```
Input: echo "Hello $USER" > greeting.txt
     │
     ▼
┌───────────────┐     ┌───────────────┐     ┌───────────────┐     ┌───────────────┐
│     Lexer     │ --> │     Parser    │ --> │   Executor    │     │   Output      │
│---------------│     │---------------│     │---------------│     │---------------│
│ - Tokenize    │     │ - Validate    │     │ - Run command │     │ greeting.txt  │
│ - Detect ""   │     │ - Expand vars │     │ - Builtin     │     │ contains:     │
│ - Separate    │     │ - Redirections│     │ - Redirect >  │     │ "Hello <USER>"│
└───────────────┘     └───────────────┘     └───────────────┘     └───────────────┘

```
