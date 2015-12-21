LEX=lex
YACC=bison
CFLAGS=-Wall -std=gnu99 -I. -I./util -O0 -ggdb
LDFLAGS=-L. -lutil
CC=cc
TARGET=bcc
SRC=	grammar.c \
	scanner.c \
	error.c \
	main.c \
	option.c \
	module.c \
	function.c \
	program.c \
	symbol_table.c \
	type.c \
	type_codegen.c \
	symbol.c \
	symbol_codegen.c \
	expression.c \
	expression_codegen.c \
	statement.c \
	statement_codegen.c \
	string_literal.c

ifndef NOGC
CFLAGS+=-Dmalloc=gcmalloc -Dfree=gcfree \
	-Drealloc=gcrealloc -Dcalloc=gccalloc
LDFLAGS+=-lgc
endif

all: $(TARGET)

OBJ=$(patsubst %.c,%.o,$(SRC))

all: 

$(TARGET): $(OBJ) libutil.a
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

grammar.c:grammar.y
	$(YACC) -d -o $@ --defines=grammar.tab.h $^

scanner.c: scanner.l grammar.c
	$(LEX) -o $@ $<

libutil.a:  util
	make -C util/
	cp  util/libutil.a libutil.a

clean:
	$(RM) $(OBJ) grammar.c scanner.c grammar.tab.h *~
	make -C util/ clean

fullclean: clean
	$(RM) uuc -f

edit: 
	emacs -mm *.c *.h *.y *.l &
