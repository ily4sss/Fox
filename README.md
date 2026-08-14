<div align="center">

FOX

A small programming language and compiler built from scratch in C

<img src="https://img.shields.io/badge/C-111827?style=flat-square&logo=c&logoColor=white">
<img src="https://img.shields.io/badge/.fox-7f1d1d?style=flat-square">
<img src="https://img.shields.io/badge/compiler-front--end-991b1b?style=flat-square">
<img src="https://img.shields.io/badge/status-in%20development-1f2937?style=flat-square">

<br><br>

source → lexer → tokens → parser → AST

</div>

ABOUT

Fox is a small programming language I am building to understand how compilers work internally.

The current version focuses on the compiler front-end: lexical analysis, parsing, expressions, conditions, blocks and AST construction.

The goal is to eventually turn .fox source code into C and compile it into an executable.

HELLO WORLD

The simplest Fox program.

<p align="center">
  <img src="./MiniCompiler/assets/carbon/hello-world.png" width="720">
</p>

display outputs a string.

VARIABLES

Fox currently supports integer variable declarations and arithmetic expressions.

<p align="center">
  <img src="./MiniCompiler/assets/carbon/variables.png" width="720">
</p>

Supported arithmetic operators:

+ - * /

Operator precedence is handled by the parser.

CONDITIONS

Conditions use check_if and check_else.

<p align="center">
  <img src="./MiniCompiler/assets/carbon/conditions.png" width="720">
</p>

Supported comparison operators:

> < >= <= == !=

Nested check_if blocks and multiple statements inside blocks are supported.

COMMENTS

Comments are ignored by the lexer.

<p align="center">
  <img src="./MiniCompiler/assets/carbon/comments.png" width="720">
</p>

Single-line comments start with $.

Multi-line comments use $- and -$.

CURRENT FEATURES

Lexer and tokenization

Integer variable declarations

Arithmetic expressions

Operator precedence

Comparison expressions

display

check_if

check_else

Nested check_if

Multiple statements inside blocks

Single-line comments

Multi-line comments

AST construction

PIPELINE

FOX Source
    ↓
Lexer
    ↓
Tokens
    ↓
Parser
    ↓
AST
    ↓
Semantic Analysis
    ↓
C Code Generation
    ↓
Executable

The lexer, parser and AST stages are the current focus.

<div align="center">

Built to understand what happens between source code and an executable.

</div>
