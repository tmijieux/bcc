LEX=lex
YACC=bison
CFLAGS=-Wall -Wextra -std=gnu99 -I. -I.. -O0 -ggdb -D_GNU_SOURCE
LDFLAGS=-L. -lutil
CC=cc
TARGET=bcc
SRC_BCC=main.c \
	chain.c \
	option.c \

ifndef NOGC
CFLAGS+= -Dmalloc=gcmalloc -Dfree=gcfree \
	-Drealloc=gcrealloc -Dcalloc=gccalloc
LDFLAGS+=-lgc -lutil -L../util
endif

all: $(TARGET)

OBJ_BCC=$(patsubst %.c,%.o,$(SRC_BCC))

#DEP=$(patsubst %.c,%.d,$(SRC))

-include $(DEP)

bcc: $(OBJ_BCC)
	$(CC) $(CFLAGS) -o $@  $(OBJ_BCC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
#	$(CC) $(CFLAGS) -MM $^ -o $*.d

grammar.tab.h: grammar.c

grammar.c:grammar.y
	$(YACC) -d -o $@ --defines=grammar.tab.h $^

scanner.c: scanner.l grammar.c
	$(LEX) -o $@ $<

libutil.a:  util
	make -C util/
	cp  util/libutil.a libutil.a

clean:
	$(RM) $(OBJ_CC1) $(OBJ_BCC) *.o grammar.c scanner.c grammar.tab.h *~ *.d

fullclean: clean
	$(RM) $(TARGET)

edit:
	emacs -mm *.c *.h *.y *.l &
