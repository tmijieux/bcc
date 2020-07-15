# bcc
a basic c compiler

# dependencies
- https://www.hboehm.info/gc/
- GNU bison
- flex


# how to compile
make

# how to use

`./cc1 < input_file.c`

OR
use the `compile` script instead:

```
./compile file1.c file2.c file3.c
# then:
./a.out
```

(for now the `bcc` executable
-which is intended to be a drop-in replacement for `gcc`-
is not working yet)


it uses
- cpp (c preprocessor) (processes macro/defines/includes )
- cc1 (c compiler in this project) (transform C to llvm )
- opt (llvm optimizer) (llvm -> llvm )
- llc (llvm compiler) (llvm -> machine assembler (text format) )
- gcc executable (use as a driver for GNU "as"(GNU assembler) and GNU "ld" (the GNU linker))

gcc is invoked on assembler (".S") files only and transforms assembler to binary
and eventually link everything together and add the C standard library as well
with all required stuff to call main when program starts ... :) !!!

# state of the project:
UNFINISHED ! (there is a lot of things that does not work)

# credits
The Lex and Yaxx grammars this compiler is based on came from here:  
- https://www.lysator.liu.se/c/
- https://www.lysator.liu.se/c/ANSI-C-grammar-y.html
- https://www.lysator.liu.se/c/ANSI-C-grammar-l.html