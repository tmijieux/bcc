LEX=lex
YACC=bison
CFLAGS=-Wall -std=gnu99 -I. -I./util -O0 -ggdb -D_GNU_SOURCE
LDFLAGS=-L. -lutil
CC=cc
TARGET=bcc
SRC=	grammar.c \
	scanner.c \
	error/error.c \
	main.c \
	option.c \
	module.c \
	function.c \
	program.c \
	symbol/symbol_table.c \
	type/type.c \
	type/type_codegen.c \
	type/specifier.c \
	type/pointer.c \
	type/enumerator.c \
	type/declarator.c \
	type/struct.c \
	symbol/symbol.c \
	symbol/symbol_codegen.c \
	expression/expression.c \
	expression/expression_codegen.c \
	statement/statement.c \
	statement/statement_codegen.c \
	constant/string_literal.c \
	constant/constant.c \
	misc/initializer.c \

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
	$(RM) $(TARGET)

edit: 
	emacs -mm *.c *.h *.y *.l &
