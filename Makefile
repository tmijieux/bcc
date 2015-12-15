TARGET=bcc
.PHONY: all clean

all: $(TARGET)

$(TARGET):
	make -C src/
	ln -s src/$@ ./$@ -f

clean:
	make -C src/ clean

fullclean: clean
	$(RM) $(TARGET)
