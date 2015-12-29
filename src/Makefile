all: 
	make -C bcc/
	make -C cc1/
	make -C util/

clean:
	find . -name '*.o' | xargs $(RM)
	find . -name '*.d' | xargs $(RM)
	make -C util/ clean
	make -C bcc/ clean
	make -C cc1/ clean

fullclean: clean
	$(RM) $(TARGET)
	make -C util/ fullclean
	make -C bcc/ fullclean
	make -C cc1/ fullclean

edit: 
	emacs -mm *.c *.h *.y *.l &
