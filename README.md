# JLex: A Simple Lex Implementation for SEU Compiler Labwork

## Usage

### .l file format

Almost the same with flex.
However, JLex doesn't support definition.

```lex
%{
    code that you want to insert at the BEGINNING of lex.yy.cpp
%}

%%

regular_expression  →  { code that execute when MATCH regular expression }

%%

code that you want to insert at the END of lex.yy.cpp
```

### How to run?

```
jlex ./example/example.l
cc -o test ./lex.yy.cpp
test ./example/example.c
```

## Example

A simple example for C language has been put in `./example` folder.
