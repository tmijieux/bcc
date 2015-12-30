TARGET=bcc
.PHONY: all clean  bcc

all: $(TARGET)

bcc:
	make -C src/
	ln -s src/bcc/$@ ./$@ -f

clean:
	make -C src/ clean

fullclean: clean
	$(RM) $(TARGET)
	make -C src/ fullclean
