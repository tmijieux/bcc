CFLAGS=-Wall -ggdb -O0 -std=gnu99  -I. 
LDFLAGS= -L.
CC=cc
SRC=	list.c \
	hash_table.c \
	string2.c \
	color.c \
	stack.c \

ifndef NOGC
CFLAGS+=-Dmalloc=gcmalloc -Dfree=gcfree \
	-Drealloc=gcrealloc -Dcalloc=gccalloc
LDFLAGS+=-lgc
SRC+= alloc.c
endif


OBJ=$(patsubst %.c,%.o,$(SRC))

all: libutil.a


libutil.a: $(OBJ)
	rm -rf $@
	ar cr $@ $^

clean:
	$(RM) $(OBJ) *~

