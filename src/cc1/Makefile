LEX=flex
YACC=bison
CFLAGS=-Wall -Wextra -std=gnu99 -I. -I.. -O0 -ggdb -D_GNU_SOURCE
LDFLAGS=-L. -L../util -lutil
CC=gcc
TARGET=cc1
SRC_CC1=parser.c \
	scanner.c \
	errorc.c \
	main.c \
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

OBJ_CC1=$(patsubst %.c,%.o,$(SRC_CC1))
OBJ_BCC=$(patsubst %.c,%.o,$(SRC_BCC))

#DEP=$(patsubst %.c,%.d,$(SRC))

-include $(DEP)

cc1: $(OBJ_CC1) ../util/libutil.a
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
#	$(CC) $(CFLAGS) -MM $^ -o $*.d

parser.tab.h: parser.c

parser.c:parser.y
	$(YACC) -d -o $@ --defines=parser.tab.h $^

scanner.c: scanner.l parser.c
	$(LEX) -o $@ $<

../util/libutil.a:
	make -C ../util/

clean:
	$(RM) $(OBJ_CC1) $(OBJ_BCC) *.o parser.c scanner.c parser.tab.h *~ *.d

fullclean: clean
	$(RM) $(TARGET)

edit:
	emacs -mm *.c *.h *.y *.l &
