TARGET=bcc
.PHONY=all $(TARGET) clean

all: $(TARGETS)

$(TARGET):
	make -C src/c/
	ln -s src/$@ ./$@ -f

clean:
	make -C src/ clean

fullclean: clean
	$(RM) $(TARGET)
